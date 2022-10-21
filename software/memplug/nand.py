from .device import Device, MemplugException
import struct

def parse_onfi(data):
    onfi = {
        "info": {},
        "vendor": {},
        "geometry": {},
        "electrical": {},
    }

    signature, revision, features, opt_cmds = struct.unpack_from("<4sHHH", data, 0)
    if signature != b"ONFI":
        raise ValueError("invalid ONFI string")
    onfi["info"]["revision"] = revision
    onfi["info"]["features"] = features
    onfi["info"]["opt_cmds"] = opt_cmds

    d = onfi["vendor"]
    (d["manufacturer"],
     d["model"],
     d["jedec_id"],
     d["date_code"]) = struct.unpack_from("<12s20sBH", data, 32)

    d = onfi["geometry"]
    (d["data_per_page"],
     d["spare_per_page"],
     d["data_per_page_partial"],
     d["spare_per_page_partial"],
     d["pages_per_block"],
     d["blocks_per_lun"],
     d["luns_per_device"],
     d["address_cycles"],
     d["bits_per_cell"],
     d["bb_per_lun_max"],
     d["block_endurance1"],
     d["valid_blocks_at_beginning"],
     d["block_endurance2"],
     d["programs_per_page"],
     d["partial_programming_attrs"],
     d["ecc_bits_correctability"],
     d["interleaved_address_bits"],
     d["interleaved_operation_attrs"]) = struct.unpack_from("<IHIHIIBBBHHBHBBBBB", data, 80)

    d = onfi["electrical"]
    (d["io_capacitance"],
     d["timing_modes"],
     d["cache_timing_modes"],
     d["tPROG_us"],
     d["tERASE_us"],
     d["tREAD_us"],
     d["tCCS_us"]) = struct.unpack_from("<BHHHHHH", data, 128)

    return onfi

def print_onfi(onfi):
    """
    Pretty print parsed CFI data for user consumption.
    """
    print("ONFI parameter page")
    print("  ONFI revision number ................. : %d" % onfi["info"]["revision"])
    print("  Features supported ................... : %04X" % onfi["info"]["features"])
    print("  Optional commands supported .......... : %04X" % onfi["info"]["opt_cmds"])

    print("Manufacturer information block")
    print("  Manufacturer ......................... : %s" % onfi["vendor"]["manufacturer"].decode())
    print("  Manufacturer JEDEC ID ................ : %02Xh" % onfi["vendor"]["jedec_id"])
    print("  Device model ......................... : %s" % onfi["vendor"]["model"].decode())

    print("Memory organization block")
    print("  Data bytes per page .................. : %d" % onfi["geometry"]["data_per_page"])
    print("  Spare bytes per page ................. : %d" % onfi["geometry"]["spare_per_page"])
    print("  Data bytes per partial page .......... : %d" % onfi["geometry"]["data_per_page_partial"])
    print("  Spare bytes per partial page ......... : %d" % onfi["geometry"]["spare_per_page_partial"])
    print("  Pages per block ...................... : %d" % onfi["geometry"]["pages_per_block"])
    print("  Blocks per LUN ....................... : %d" % onfi["geometry"]["blocks_per_lun"])
    print("  LUNs per device ...................... : %d" % onfi["geometry"]["luns_per_device"])
    print("  Address cycles, col:row .............. : %d:%d" % (onfi["geometry"]["address_cycles"] >> 4, onfi["geometry"]["address_cycles"] & 0xF))
    print("  Bits per cell ........................ : %d" % onfi["geometry"]["bits_per_cell"])
    print("  Bad blocks per LUN, max .............. : %d" % onfi["geometry"]["bb_per_lun_max"])
    print("  Programs per page .................... : %d" % onfi["geometry"]["programs_per_page"])
    print("  Number of ECC correctability bits .... : %d" % onfi["geometry"]["ecc_bits_correctability"])
    print("  Number of interleaved address bits ... : %d" % onfi["geometry"]["interleaved_address_bits"])

    print("Elecetrical parameters block")
    print("  Timing mode support .................. : %d" % onfi["electrical"]["timing_modes"])
    print("  Program cache timing mode support .... : %d" % onfi["electrical"]["cache_timing_modes"])
    print("  Page program time, max ............... : %d us" % onfi["electrical"]["tPROG_us"])
    print("  Block erase time, max ................ : %d us" % onfi["electrical"]["tERASE_us"])
    print("  Page read time, max .................. : %d us" % onfi["electrical"]["tREAD_us"])

class NANDGeometry(object):
    """
    Describes a NAND device's geometry
    """
    def __init__(self, data_per_page, spare_per_page, pages_per_block, blocks_per_lun):
        self.data_per_page = data_per_page
        self.spare_per_page = spare_per_page
        self.pages_per_block = pages_per_block
        self.blocks_per_lun = blocks_per_lun
    def __str__(self):
        return("%d+%dx%dx%d" % (self.data_per_page, self.spare_per_page, self.pages_per_block, self.blocks_per_lun))

class NANDDevice(Device):
    """
    Implements an (ONFI-compatible) command set wrapper around the USB dongle
    """
    def __init__(self):
        Device.__init__(self, 0x5721)

    def read_id(self):
        """
        Implements the READ ID command

        Returns: ID bytes
        """
        return self._command(0x10, countIn=6)

    def read_param_page(self):
        """
        Implements the PARAMETER PAGE READ command

        Returns: 256 bytes of page data
        """
        return self._command(0x11, countIn=256)

    def read_page(self, address, page_size):
        """
        Implements the PAGE READ command

        address
            Row address of the page to be read
        page_size
            Page size, in bytes

        Returns: page data
        """
        args = struct.pack("<IHH", address, page_size, 1)
        return self._command(0x20, args, countIn=page_size)

    def read_pages(self, address, page_size, count):
        """
        Implements the PAGE READ command

        address
            Row address of the page to be read
        page_size
            Page size, in bytes

        Returns: page data
        """
        args = struct.pack("<IHH", address, page_size, count)
        self._command(0x20, args)
        # each page is read separately
        pages = []
        for i in range(count):
            data = self._handle.bulkRead(1, page_size, self.data_timeout)
            pages.append(data)
        return pages

    def erase_block(self, address):
        """
        Implements the BLOCK ERASE command

        address
            Row address of any page within the block to be erased
        """
        args = struct.pack("<II", address, self.cmd_timeout)
        self._command(0x30, args)

    def program_page(self, address, data):
        """
        Implements the PAGE PROGRAM command

        address
            Row address of the page to be programmed
        data
            Bytes to be programmed
        timeout
            Operation timeout, in ms
        """
        args = struct.pack("<IHHI", address, len(data), 1, self.cmd_timeout)
        self._command(0x40, args, dataOut=data)

    def program_pages(self, address, page_size, data):
        """
        Implements the PAGE PROGRAM command

        address
            Row address of the page to be programmed
        data
            Bytes to be programmed
        timeout
            Operation timeout, in ms
        """
        if len(data) % page_size:
            raise ValueError("provided data length is not multiple of page size")
        args = struct.pack("<IHHI", address, page_size, len(data) // page_size, self.cmd_timeout)
        self._command(0x40, args)
        for i in range(count):
            data = self._handle.bulkWrite(1, data[i*page_size:(i+1)*page_size], self.data_timeout)

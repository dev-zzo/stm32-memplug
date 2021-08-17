import struct
from .device import Device, MemplugException

def parse_cfi(data):
    """
    Parse standard CFI data elements and return them as a dictionary.

    See JESD68 for definitions etc.
    """
    cfi = {}
    qry, pri_algo_id, pri_algo_addr, alt_algo_id, alt_algo_addr = struct.unpack_from("<3sHHHH", data, 0x10)
    if qry != b"QRY":
        raise ValueError("invalid CFI QRY string")
    cfi["id"] = {
        "pri_algo_id": pri_algo_id,
        "pri_algo_addr": pri_algo_addr,
        "alt_algo_id": alt_algo_id,
        "alt_algo_addr": alt_algo_addr,
    }

    _, _, _, _, word_program_time_log2, buffer_program_time_log2, block_erase_time_log2, chip_erase_time_log2, word_program_time_mult, buffer_program_time_mult, block_erase_time_mult, chip_erase_time_mult = struct.unpack_from("<BBBBBBBBBBBB", data, 0x1B)
    cfi["timing"] = {}
    if word_program_time_log2:
        word_program_time = (1 << word_program_time_log2) # us
        word_program_time_max = word_program_time * (1 << word_program_time_mult)
        cfi["timing"]["word_program"] = { "typ": word_program_time, "max": word_program_time_max }
    else:
        cfi["timing"]["word_program"] = None
    if buffer_program_time_log2:
        buffer_program_time = (1 << buffer_program_time_log2) # us
        buffer_program_time_max = buffer_program_time * (1 << buffer_program_time_mult)
        cfi["timing"]["buffer_program"] = { "typ": buffer_program_time, "max": buffer_program_time_max }
    else:
        cfi["timing"]["buffer_program"] = None
    if block_erase_time_log2:
        block_erase_time = (1 << block_erase_time_log2) # ms
        block_erase_time_max = block_erase_time * (1 << block_erase_time_mult)
        cfi["timing"]["block_erase"] = { "typ": block_erase_time, "max": block_erase_time_max }
    else:
        cfi["timing"]["block_erase"] = None
    if chip_erase_time_log2:
        chip_erase_time = (1 << chip_erase_time_log2) # ms
        chip_erase_time_max = chip_erase_time * (1 << chip_erase_time_mult)
        cfi["timing"]["chip_erase"] = { "typ": chip_erase_time, "max": chip_erase_time_max }
    else:
        cfi["timing"]["chip_erase"] = None

    device_size_log2, _, buffer_size_log2, eb_count = struct.unpack_from("<BHHB", data, 0x27)
    eb_regions = [ struct.unpack_from("<HH", data, 0x2D + i*4) for i in range(eb_count) ]
    cfi["geometry"] = {
        "device_size": (1 << device_size_log2),
        "buffer_size": (1 << buffer_size_log2) if buffer_size_log2 else None,
    }
    eb_regions = [ {"count": x[0]+1, "size": x[1]*256} for x in eb_regions ]
    cfi["geometry"]["eb_regions"] = eb_regions

    return cfi

def print_cfi(cfi):
    """
    Pretty print parsed CFI data for user consumption.
    """
    print("CFI Query identification string")
    print("  Primary algorithm ID and address ... : %04X %04X" % (cfi["id"]["pri_algo_id"], cfi["id"]["pri_algo_addr"]))
    print("  Alternative algorithm ID and address : %04X %04X" % (cfi["id"]["alt_algo_id"], cfi["id"]["alt_algo_addr"]))
    print("Operation timings, typ / max")
    if cfi["timing"]["word_program"] is not None:
        print("  Word programming ................... : %dus / %dus" % (cfi["timing"]["word_program"]["typ"], cfi["timing"]["word_program"]["max"]))
    if cfi["timing"]["buffer_program"] is not None:
        print("  Buffer programming ................. : %dus / %dus" % (cfi["timing"]["buffer_program"]["typ"], cfi["timing"]["buffer_program"]["max"]))
    if cfi["timing"]["block_erase"] is not None:
        print("  Block erase ........................ : %dms / %dms" % (cfi["timing"]["block_erase"]["typ"], cfi["timing"]["block_erase"]["max"]))
    if cfi["timing"]["chip_erase"] is not None:
        print("  Chip erase ......................... : %dms / %dms" % (cfi["timing"]["chip_erase"]["typ"], cfi["timing"]["chip_erase"]["max"]))
    print("Device geometry")
    print("  Device size, bytes ................. : %d" % (cfi["geometry"]["device_size"]))
    if cfi["geometry"]["buffer_size"] is not None:
        print("  Buffer size, bytes ................. : %d" % (cfi["geometry"]["buffer_size"]))
    print("Erase block regions")
    for eb in cfi["geometry"]["eb_regions"]:
        print("  Block size, bytes .................. : %d" % (eb["size"]))
        print("  Block count ........................ : %d" % (eb["count"]))

class NORDevice(Device):
    """
    Implements a command set wrapper around the USB dongle with the NOR top board installed.
    """
    USB_PID = 0x5723

    def __init__(self):
        Device.__init__(self, NORDevice.USB_PID)

    def read_id(self):
        """
        Reads the manufacturer and chip ID, and returns them as bytes.
        """
        args = b""
        data = self._command(0x10, args, countIn=8)
        return bytearray([data[0], data[2], data[4], data[6]])

    def read_cfi(self):
        """
        Reads the 128 words of CFI data and returns low-order bytes only.
        """
        args = b""
        return self._command(0x11, args, countIn=128)

    def read_autoselect(self, address, count):
        """
        Reads raw data from the Autoselect mode and returns the words read.
        """
        args = struct.pack("<II", address, count)
        return self._command(0x12, args, countIn=count)

    def read(self, address, count):
        """
        Reads the memory array data.

        address
            Starting address (in bytes) to verify; should be even.
        count
            Byte count to verify; will be rounded down to words so should be even.
        """
        args = struct.pack("<II", address, count)
        return self._command(0x20, args, countIn=count)

    def blank_check(self, address, count):
        """
        Verifies the memory array range to be erased, containing 0xFF only.

        Raises an informative ValueError if the array is not blank.

        address
            Starting address (in bytes) to verify; should be even.
        count
            Byte count to verify; will be rounded down to words so should be even.
        """
        args = struct.pack("<II", address, count)
        try:
            self._command(0x21, args)
        except MemplugException:
            status, address, value = struct.unpack_from("<IIH", self.get_status(), 0)
            raise ValueError("blank check failed at address %08X; value: %04X" % (address, value))

    def erase_block(self, address, timeout):
        """
        Erase the given block/sector.

        Consult erase block region information in CFI for region sizes etc.

        address
            Sector address (in bytes) to be erased.
        """
        args = struct.pack("<II", address, int(timeout))
        self._command(0x30, args, cmd_timeout=timeout+100)

    def erase_chip(self, timeout):
        """
        Erase the whole chip.

        Note this operation typically takes quite some time to complete.
        """
        args = struct.pack("<I", int(timeout))
        self._command(0x31, args, cmd_timeout=timeout+100)

    def program(self, address, data, buffer_size):
        """
        Program the memory array.

        address
            Starting address (in bytes) to program; should be even.
        data
            A bytes/bytearray containing the array data to be programmed.
        buffer_size
            If not zero, the write-buffer programming algorithm will be used with
            the given buffer size; this size should come from the CFI data.
            Otherwise, programming will be done word by word.
        """
        args = struct.pack("<III", address, len(data), buffer_size)
        # setup the programming
        self._command(0x40, args)
        # data will be fed in transactions equal to internal (not NOR Flash) buffer size
        for i in range(0, len(data), 8192):
            self._handle.bulkWrite(1, data[i:i+8192], self.data_timeout)

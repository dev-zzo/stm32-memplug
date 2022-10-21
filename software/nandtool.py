import argparse
import sys
import struct
import time

from memplug import ProgressBar
from memplug.nand import NANDDevice, NANDGeometry, parse_onfi, print_onfi

_id_data_to_name = {
    "2033": "NAND128R3A",
    "2073": "NAND128W3A",
    "2043": "NAND128R4A",
    "2053": "NAND128W4A",
    "2035": "NAND256R3A",
    "2075": "NAND256W3A",
    "2045": "NAND256R4A",
    "2055": "NAND256W4A",
    "2036": "NAND512R3A",
    "2076": "NAND512W3A",
    "2046": "NAND512R4A",
    "2056": "NAND512W4A",
    "2039": "NAND01GR3A",
    "2079": "NAND01GW3A",
    "2049": "NAND01GR4A",
    "2059": "NAND01GW4A",
    
    "01F1001D": "S34ML01G100",
    
    "01DA909544": "S34ML02G100",
    "01DC909554": "S34ML04G100",
    
    "ADF1001D": "H27U1G8F2B",
    "ADF1801D": "HY27UF081G2A",
    "ADC1805D": "HY27UF161G2A",
    "ADDA109544": "HY27UF082G2B",
    "ADCA10D544": "HY27UF162G2B",
    "ADDA909544": "H27U2G8F2CTR",
    
    "ECD3519558": "K9K8G08U0A",
    "ECD5552568": "K9HBG08U1M",
    "ECD755B678": "K9LBG08U0M",
    "ECF1009540": "K9F1G08U0D",
    
    "C2DA909506": "MX30LF2G18AC",
    "C2DC909556": "MX30LF4G18AC",
    
    "98D594327655": "TC58NVG4D2FTA00",
    "98DA90157614": "TC58NVG1S3EBAI4",
    "2C4800268900": "MT29F16G08ABABA",
    
    "EFDA90950400": "W29N02GV",
}

def check_device_id(id_data):
    id_data = "".join(["%02X" % x for x in bytearray(id_data)])
    for i in range(4, 14, 2):
        if _id_data_to_name.get(id_data[:i], None) is not None:
            return id_data[:i]
    return None

def check_device_name(id_data):
    """
    Checks the registry against thte device ID data and returns the device name.
    Inputs:
    - id_data: a bytearray
    """
    id_data = bytearray(id_data)
    id_data = "".join(["%02X" % x for x in id_data])
    try:
        return _id_data_to_name[id_data[:4]]
    except:
        try:
            return _id_data_to_name[id_data[:6]]
        except:
            try:
                return _id_data_to_name[id_data[:8]]
            except:
                try:
                    return _id_data_to_name[id_data[:10]]
                except:
                    try:
                        return _id_data_to_name[id_data[:12]]
                    except:
                        return None

_name_to_geometry = {
    # page data size, page spare size, pages per block, blocks per LUN
    "H27U1G8F2B":       NANDGeometry(2048,  64,  64, 1024),
    "HY27UF082G2B":     NANDGeometry(2048,  64,  64, 2048),
    "K9K8G08U0A":       NANDGeometry(2048,  64,  64, 8192),
    "K9HBG08U1M":       NANDGeometry(2048,  64, 128, 8192),
    "K9LBG08U0M":       NANDGeometry(4096, 128, 128, 8192),
    "K9F1G08U0D":       NANDGeometry(2048,  64,  64, 1024),
    "W29N02GV":         NANDGeometry(2048,  64,  64, 2048),
    "TC58NVG1S3EBAI4":  NANDGeometry(2048,  64,  64, 2048),
}

def geometry_from_id(id_data):
    name = check_device_name(id_data)
    return _name_to_geometry.get(name, None)

def geometry_from_onfi_params(onfi):
    print("Manufacturer: %s" % onfi["vendor"]["manufacturer"].decode())
    print("Device model: %s" % onfi["vendor"]["model"].decode())
    g = onfi["geometry"]
    print("Page size:    %d+%d" % (g["data_per_page"], g["spare_per_page"]))
    print("Pages/block:  %d" % g["pages_per_block"])
    print("Blocks/LUN:   %d" % g["blocks_per_lun"])
    print("Page count:   %d" % (g["pages_per_block"] * g["blocks_per_lun"]))
    return NANDGeometry(g["data_per_page"], g["spare_per_page"], g["pages_per_block"], g["blocks_per_lun"])

def op_read(dev, args):
    if dev.geom is None:
        raise ValueError("device geometry is not known; cannot continue")
    start = args.address
    device_size = dev.geom.pages_per_block * dev.geom.blocks_per_lun * 1 # dev.onfi["geometry"]["luns_per_device"]
    if start >= device_size:
        raise ValueError("start address is outside the device size")
    count = args.count
    if count is None:
        count = device_size - start
    if start + count > device_size:
        raise ValueError("end address is outside the device size")

    page_size = dev.geom.data_per_page
    block_size = dev.geom.pages_per_block
    if not args.no_spares:
        page_size += dev.geom.spare_per_page
    print("Reading memory array ...")
    with open(args.image_path, "wb") as fp:
        p = ProgressBar("pages", unit_size=page_size, granularity=32)
        p.start(count)
        page_count = 0
        while page_count < count:
            p.update(page_count + 1)
            address = start + page_count
            data = dev.read_pages(address, page_size, min(block_size, count - page_count))
            for page in data:
                fp.write(page)
            page_count += block_size
        p.finish()
    print("Operation took: %.3fs" % (time.time() - p.start))

def op_erase(dev, args):
    if dev.geom is None:
        raise ValueError("device geometry is not known; cannot continue")
    start = args.address
    device_size = dev.geom.pages_per_block * dev.geom.blocks_per_lun * 1 # dev.onfi["geometry"]["luns_per_device"]
    if start >= device_size:
        raise ValueError("start address is outside the device size")
    count = args.count
    if count is None:
        count = device_size - start
    if start + count > device_size:
        raise ValueError("end address is outside the device size")
    page_size = dev.geom.data_per_page
    block_size = dev.geom.pages_per_block
    print("Erasing memory array ...")
    p = ProgressBar("pages", unit_size=1, granularity=32)
    p.start(count)
    page_count = 0
    while page_count < count:
        p.update(page_count + 1)
        address = start + page_count
        dev.erase_block(address)
        page_count += block_size
    p.finish()
    print("Operation took: %.3fs" % (time.time() - p.start))

def op_program(dev, args):
    if dev.geom is None:
        raise ValueError("device geometry is not known; cannot continue")
    start = args.address
    device_size = dev.geom.pages_per_block * dev.geom.blocks_per_lun * 1 # dev.onfi["geometry"]["luns_per_device"]
    if start >= device_size:
        raise ValueError("start address is outside the device size")
    count = args.count
    if count is None:
        count = device_size - start
    if start + count > device_size:
        raise ValueError("end address is outside the device size")

    page_size = dev.geom.data_per_page
    block_size = dev.geom.pages_per_block
    if not args.no_spares:
        page_size += dev.geom.spare_per_page
        
    print("Programming memory array ...")
    with open(args.image_path, "rb") as fp:
        p = ProgressBar("pages", unit_size=page_size, granularity=1)
        p.start(count)
        page_count = 0
        while page_count < count:
            p.update(page_count + 1)
            address = start + page_count
            dev.program_page(address, fp.read(page_size))
            page_count += 1
        p.finish()
    print("Operation took: %.3fs" % (time.time() - p.start))

def op_noop(dev, args):
    pass

def from_hex(x):
    return int(x, 16)

def main():
    parser = argparse.ArgumentParser()
    parser.set_defaults(func=op_noop)
    subparsers = parser.add_subparsers(title='subcommands', description='valid subcommands')

    subparser = subparsers.add_parser('read', help='read memory array')
    subparser.add_argument('--address',
        type=from_hex,
        default=0,
        help='start row address, in hex')
    subparser.add_argument('--count',
        type=from_hex,
        help='page count, in hex')
    subparser.add_argument('--no-spares',
        default=False,
        action='store_true',
        help='do not keep spare area bytes')
    subparser.add_argument('image_path',
        metavar='PATH',
        type=str,
        help='output file')
    subparser.set_defaults(func=op_read)

    subparser = subparsers.add_parser('erase', help='erase memory array')
    subparser.add_argument('--address',
        type=from_hex,
        default=0,
        help='start row address, in hex')
    subparser.add_argument('--count',
        type=from_hex,
        help='page count, in hex')
    subparser.set_defaults(func=op_erase)

    subparser = subparsers.add_parser('program', help='program memory array')
    subparser.add_argument('--address',
        type=from_hex,
        default=0,
        help='start row address, in hex')
    subparser.add_argument('--count',
        type=from_hex,
        default=0,
        help='page count, in hex')
    subparser.add_argument('--no-spares',
        default=False,
        action='store_true',
        help='do not program spare area bytes')
    subparser.add_argument('image_path',
        metavar='PATH',
        type=str,
        help='input file')
    subparser.set_defaults(func=op_program)

    args = parser.parse_args()
    dev = NANDDevice()
    try:
        id_data = dev.read_id()
        print("ID: " + id_data.hex())
        geom = geometry_from_id(id_data)
        if geom is None:
            onfi_data = dev.read_param_page()
            try:
                onfi = parse_onfi(onfi_data)
                print_onfi(onfi)
                dev.onfi = onfi
                geom = geometry_from_onfi_params(onfi)
            except ValueError:
                print("Failed to parse ONFI data:")
                print(onfi_data.hex())
                #raise
        else:
            print("Known device: %s; ONFI query skipped" % check_device_name(id_data))
        dev.geom = geom
        args.func(dev, args)
    except ValueError as e:
        print("Operation failed: " + str(e))
        raise
    finally:
        dev.close()

if __name__ == '__main__':
    main()

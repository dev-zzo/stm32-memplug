import argparse
import sys
import struct
import time

from memplug import ProgressBar
from memplug.nand import NANDDevice, NANDGeometry, parse_onfi, print_onfi

def geometry_from_onfi_params(dev):
    data = dev.read_param_page(256)
    params = ONFIParameterPage(data)
    if params.signature != "ONFI":
        return None

    page_size = params.data_bytes_per_page + params.spare_bytes_per_page
    pages = params.pages_per_block * params.blocks_per_lun
    print("Manufacturer: %s" % params.device_manufacturer)
    print("Device model: %s" % params.device_model)
    print("Page size:    %d+%d" % (params.data_bytes_per_page, params.spare_bytes_per_page))
    print("Pages/block:  %d" % params.pages_per_block)
    print("Blocks/LUN:   %d" % params.blocks_per_lun)
    print("Page count:   %d" % pages)
    return NANDGeometry(params.data_bytes_per_page, params.spare_bytes_per_page, params.pages_per_block, params.blocks_per_lun)

def op_read(dev, args):
    start = args.address
    device_size = dev.onfi["geometry"]["pages_per_block"] * dev.onfi["geometry"]["blocks_per_lun"] * dev.onfi["geometry"]["luns_per_device"]
    if start >= device_size:
        raise ValueError("read start is outside the device size")
    count = args.count
    if count is None:
        count = device_size - start
    if start + count > device_size:
        raise ValueError("read end is outside the device size")

    page_size = dev.onfi["geometry"]["data_per_page"]
    block_size = dev.onfi["geometry"]["pages_per_block"]
    if not args.no_spares:
        page_size += dev.onfi["geometry"]["spare_per_page"]
    print("Reading memory array ...")
    with open(args.output_path, "wb") as fp:
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
        help='start row address')
    subparser.add_argument('--count',
        type=from_hex,
        help='page count')
    subparser.add_argument('--no-spares',
        default=False,
        action='store_true',
        help='do not keep spare area bytes')
    subparser.add_argument('-o', '--output-path',
        metavar='PATH',
        type=str,
        required=True,
        help='output file path')
    subparser.set_defaults(func=op_read)

    args = parser.parse_args()
    dev = NANDDevice()
    try:
        id_data = dev.read_id()
        print("ID: " + id_data.hex())
        onfi_data = dev.read_param_page()
        onfi = parse_onfi(onfi_data)
        print_onfi(onfi)
        dev.onfi = onfi
        args.func(dev, args)
    finally:
        dev.close()

if __name__ == '__main__':
    main()

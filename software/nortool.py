"""
This is the NOR Tool, performing operations on NOR chips.
Part of the STM32-MemPlug kit.
"""

import argparse
import sys
import struct
import time

from memplug.nor import NORDevice, parse_cfi, print_cfi

class ProgressBar:
    def __init__(self, units="pages", unit_size=2048, granularity=32):
        self.units = units
        self.unit_size = unit_size
        self.granularity = granularity
        
    def start(self, max_count):
        self.start = time.time()
        self.max_count = max_count

    def update(self, progress):
        if self.granularity < 2 or progress % self.granularity == 1:
            sys.stdout.write("Progress: %d/%d %s (%d%%)" % (progress, self.max_count, self.units, int(100*progress/self.max_count)))
            dt = (time.time() - self.start)
            if dt > 2:
                speed = progress / dt
                sys.stdout.write(" (%.2f/s %.2fKB/s)" % (speed, speed * self.unit_size / 1024))
            sys.stdout.write("\r")

    def finish(self):
        sys.stdout.write("Progress: %d/%d %s (%d%%)" % (self.max_count, self.max_count, self.units, 100))
        dt = time.time() - self.start
        if (dt >= 2):
            speed = self.max_count / dt
            sys.stdout.write(" (%.2f/s %.2fKB/s)" % (speed, speed * self.unit_size / 1024))
        sys.stdout.write("\n")

def wordflip(b):
    c = bytearray()
    for i in range(0, len(b), 2):
        c.append(b[i+1])
        c.append(b[i])
    return c
    
def op_read(dev, args):
    """
    Read the memory array
    """
    start = args.address
    if start >= dev.cfi["geometry"]["device_size"]:
        raise ValueError("read start is outside the device size")
    count = args.count
    if count is None:
        count = dev.cfi["geometry"]["device_size"] - start
    if start + count > dev.cfi["geometry"]["device_size"]:
        raise ValueError("read end is outside the device size")
    # Tansfer size is fixed
    block_size = 1<<16
    block_count = (count + block_size - 1) // block_size

    print("Reading memory array ...")
    with open(args.output_path, "wb") as fp:
        p = ProgressBar("blocks", block_size, 8)
        p.start(block_count)
        for block in range(block_count):
            p.update(block + 1)
            address = start + block * block_size
            read_size = min(block_size, count)
            data = dev.read(address, read_size)
            if args.swap_bytes:
                data = wordflip(data)
            fp.write(data)
            count -= read_size
        p.finish()
    print("Operation took: %.3fs" % (time.time() - p.start))

def op_blank_check(dev, args):
    """
    Perform blank check against memory array, verifying every location is erased
    """
    start = args.address
    if start >= dev.cfi["geometry"]["device_size"]:
        raise ValueError("read start is outside the device size")
    count = args.count
    if count is None:
        count = dev.cfi["geometry"]["device_size"] - start
    if start + count > dev.cfi["geometry"]["device_size"]:
        raise ValueError("read end is outside the device size")

    print("Blank-checking memory array ...")
    start_time = time.time()
    dev.blank_check(start, count)
    print("Operation took: %.3fs" % (time.time() - start_time))

def op_erase_chip(dev, args):
    """
    Erase the whole chip
    """
    timeout = dev.cfi["timing"]["chip_erase"]["max"]
    print("Erasing chip ... might take a while ...")
    start_time = time.time()
    dev.erase_chip(timeout)
    print("Operation took: %.3fs" % (time.time() - start_time))

def op_erase_block(dev, args):
    """
    Erase memory block
    """
    if args.address >= dev.cfi["geometry"]["device_size"]:
        raise ValueError("blocka address is outside the device size")
    timeout = dev.cfi["timing"]["block_erase"]["max"]
    print("Erasing block ... might take a while ...")
    start_time = time.time()
    dev.erase_block(args.address, timeout)
    print("Operation took: %.3fs" % (time.time() - start_time))

def op_program(dev, args):
    """
    Program the memory array
    """
    start = args.address
    if start >= dev.cfi["geometry"]["device_size"]:
        raise ValueError("read start is outside the device size")
    count = args.count
    if count is None:
        count = dev.cfi["geometry"]["device_size"] - start
    if start + count > dev.cfi["geometry"]["device_size"]:
        raise ValueError("read end is outside the device size")
    # Tansfer size is equal to internal buffer size
    block_size = 1<<16
    block_count = (count + block_size - 1) // block_size
    buffer_size = dev.cfi["geometry"]["buffer_size"]
    if buffer_size is None:
        buffer_size = 0

    print("Programming memory array ...")
    with open(args.input_path, "rb") as fp:
        p = ProgressBar("blocks", block_size, 1)
        p.start(block_count)
        fp.seek(args.offset)
        for block in range(block_count):
            p.update(block + 1)
            address = start + block * block_size
            read_size = min(block_size, count)
            data = fp.read(read_size)
            if len(data) != read_size:
                raise ValueError("input file ended before programming is complete")
            if args.swap_bytes:
                data = wordflip(data)
            if data != b"\xFF" * len(data):
                dev.program(address, data, buffer_size)
            # TODO: implement this in firmware to mitigate the slowdown.
            if args.verify:
                data_read = dev.read(address, len(data))
                for i in range(len(data)):
                    if data[i] != data_read[i]:
                        raise ValueError("programming error at address %08X; programmed %02X, read back %02X" % (address + i, data[i], data_read[i]))
            count -= read_size
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
        help='start address')
    subparser.add_argument('--count',
        type=from_hex,
        help='byte count')
    subparser.add_argument('--swap-bytes',
        default=False,
        action='store_true',
        help='swap bytes in half-words')
    subparser.add_argument('-o', '--output-path',
        metavar='PATH',
        type=str,
        required=True,
        help='output file path')
    subparser.set_defaults(func=op_read)

    subparser = subparsers.add_parser('blank-check', help='verify whether memory array is blank')
    subparser.add_argument('--address',
        type=from_hex,
        default=0,
        help='start address')
    subparser.add_argument('--count',
        type=from_hex,
        help='byte count')
    subparser.set_defaults(func=op_blank_check)

    subparser = subparsers.add_parser('erase-chip', help='erase the whole chip')
    subparser.set_defaults(func=op_erase_chip)
    
    subparser = subparsers.add_parser('erase-block', help='erase a block/sector')
    subparser.add_argument('--address',
        type=from_hex,
        default=0,
        help='block/sector address')
    subparser.set_defaults(func=op_erase_block)
    
    subparser = subparsers.add_parser('program', help='program memory array')
    subparser.add_argument('--address',
        type=from_hex,
        default=0,
        help='start address')
    subparser.add_argument('--count',
        type=from_hex,
        help='byte count')
    subparser.add_argument('--swap-bytes',
        default=False,
        action='store_true',
        help='swap bytes in half-words')
    subparser.add_argument('--verify',
        default=False,
        action='store_true',
        help='verify data right after programming')
    subparser.add_argument('--offset',
        type=from_hex,
        default=0,
        help='offset in input file')
    subparser.add_argument('-i', '--input-path',
        metavar='PATH',
        type=str,
        required=True,
        help='input file path')
    subparser.set_defaults(func=op_program)

    args = parser.parse_args()
    dev = NORDevice()
    try:
        print("ID: " + dev.read_id().hex())
        #print("AS: ")
        #print(hexdump(dev.read_autoselect(0, 512)))
        cfi_data = dev.read_cfi()
        cfi = parse_cfi(cfi_data)
        print_cfi(cfi)
        dev.cfi = cfi
        args.func(dev, args)
    finally:
        dev.close()

if __name__ == '__main__':
    main()

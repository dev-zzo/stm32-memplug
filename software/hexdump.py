def str_transform(x):
    return ord(x)
def null_transform(x):
    return x

def hexdump(data, format='s', order='little'):
    """Pretty print a hex dump of data, similar to xxd"""
    lines = []
    offset = 0
    if format == 's':
        halflength = 8 * 3 # "XX "
        linefmt = '%04x  %-'+str(halflength)+'s %-'+str(halflength)+'s %-16s'
        if type(data) is str:
            xf = str_transform
        else:
            xf = null_transform
        while offset < len(data):
            piece = data[offset:offset + 16]
            binary = ''.join([('%02x ' % xf(x)) for x in piece])
            chars = ''.join([(chr(xf(x)) if 0x20 < xf(x) < 0x7f else '.') for x in piece])
            lines.append(linefmt % (offset, binary[:halflength], binary[halflength:], chars))
            offset += len(piece)
            
    elif format == 'b':
        halflength = 8 * 3 # "XX "
        linefmt = '%04x  %-'+str(halflength)+'s %-'+str(halflength)+'s %-16s'
        while offset < len(data):
            piece = data[offset:offset + 16]
            binary = ''.join([('%02x ' % x) for x in piece])
            chars = ''.join([(chr(x) if 0x20 < x < 0x7f else '.') for x in piece])
            lines.append(linefmt % (offset, binary[:halflength], binary[halflength:], chars))
            offset += len(piece)
            
    elif format == 'h':
        halflength = 4 * (4+1) # "XXXX "
        linefmt = '%04x  %-'+str(halflength)+'s %-'+str(halflength)+'s'
        while offset < len(data):
            piece = data[offset:offset + 16]
            while len(piece) % 2:
                piece += b"\0"
            binary = ''.join([('%04x ' % x) for x in [int.from_bytes(piece[y:y+2], order) for y in range(0, len(piece), 2)]])
            lines.append(linefmt % (offset * 2, binary[:halflength], binary[halflength:]))
            offset += len(piece)
            
    elif format == 'w':
        halflength = 2 * (8+1) # "XXXXXXXX "
        linefmt = '%04x  %-'+str(halflength)+'s %-'+str(halflength)+'s'
        while offset < len(data):
            piece = data[offset:offset + 16]
            while len(piece) % 4:
                piece += b"\0"
            binary = ''.join([('%08x ' % x) for x in [int.from_bytes(piece[y:y+4], order) for y in range(0, len(piece), 4)]])
            lines.append(linefmt % (offset * 4, binary[:halflength], binary[halflength:]))
            offset += len(piece)
            
    else:
        raise ValueError("format is not one of 'sbhw'")
    return "\n".join(lines)

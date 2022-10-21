"""
This file contains the base class implementing interactions with the STM32-MemPlug device.
"""

import struct
from usb1 import USBContext, USBErrorPipe

class MemplugException(Exception):
    pass

class Device(object):
    """
    Implements a command set wrapper around the USB dongle
    """
    USB_VID = 0x0483
    
    def __init__(self, pid):
        # TODO: do it right
        self._context = USBContext()
        self._handle = self._context.openByVendorIDAndProductID(Device.USB_VID, pid, skip_on_error=True)
        if self._handle is None:
            raise MemplugException("USB device not found; check lsusb and/or the top board type")
        self._iface = self._handle.claimInterface(0)
        self._handle.setConfiguration(1)
        # 500ms timeouts by default
        self.cmd_timeout = 500
        self.data_timeout = 500
        
    def close(self):
        if self._handle is not None:
            self._handle.releaseInterface(0)
            self._handle.close()
        if self._context is not None:
            self._context.close()

    def _command(self, cmd_id, args=b"", dataOut=None, countIn=None, cmd_timeout=None, data_timeout=None):
        if cmd_timeout is None:
            cmd_timeout = self.cmd_timeout
        if data_timeout is None:
            data_timeout = self.data_timeout
        try:
            self._handle.controlWrite(0x21, cmd_id, 0x0000, 0x0000, args, cmd_timeout)
        except USBErrorPipe:
            raise MemplugException("command failed")
        if dataOut is not None:
            self._handle.bulkWrite(1, dataOut, data_timeout)
        if countIn is not None:
            return self._handle.bulkRead(1, countIn, data_timeout)
        return None

    def get_status(self):
        return self._handle.controlRead(0x21, 0, 0x0000, 0x0000, 64, self.cmd_timeout)
        
    def recover(self):
        self._handle.controlWrite(0x21, 1, 0x0000, 0x0000, b"", self.cmd_timeout)

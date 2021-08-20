import sys
import time
from .device import *
from .nor import *
from .nand import *

__all__ = [
    'MemplugException',
    'NORDevice',
    'NANDDevice',
    'NANDGeometry',
    'ONFIParameterPage',
]

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

from __future__ import absolute_import
from symbol import symbol
import board

class bomb(object):
    def __init__(self, b):
        self.bombs_ = b
        if not self.bombs_:
            self.bombs_ = 0
        self.resetloc()
    def printb(self, boardd):
        for i in self.loc:
            if i:
                boardd.Boarder(i, symbol.B)
    def plantbomb(self, c, locOFh):
        u''' plantbomb
        * - if input is @E then plants a bomb at human's location
        * - returns true if it plants a bomb (even if fail to plant)
        '''
        if c != u' ':
            return False
        if self.bombs() > 0:
            self.decrement()
            self.loc.append(locOFh)
        return True
    def resetloc(self):
        self.loc = []
    def bombs(self, new=None):
        if not new is None:
            self.bombs_ = new
        return self.bombs_
    def decrement(self):
        self.bombs_ -= 1

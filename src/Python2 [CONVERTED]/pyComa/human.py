from __future__ import absolute_import
from symbol import symbol, arrow, symbols, getch

import creature
import bomb
import pickup
import sys
import lvlchange
import board

class human(object):
    def __init__(self, locSt, dirSt):
        self.loc_ = locSt
        self.dir_ = dirSt
        self.dead = False
    def hstraight(self):
        u''' hstraight
        * - moves human
        '''
        for comp, result in [(arrow.U, -board.WIDTH),
                            (arrow.D, +board.WIDTH),
                            (arrow.L, -1),
                            (arrow.R, +1)
                            ]:
            if comp == self.dir():
                self.loc_ += result
                break
        if not self.dir():
            raise ValueError
    def printh(self):
        u''' printh
        * - moves human
        * - returns false if loses
        * - prints location to board
        '''
        self.hstraight()
        dead = False
        #if ( board.size() < static_cast<whole>(*loc_) ) return true;
        dead = board.BOARD_REF.Boarder(self.loc_) != symbol.E and board.BOARD_REF.Boarder(self.loc_) != symbol.P
        if not dead:
            board.BOARD_REF.Boarder(self.loc_, symbol.F)
        return not dead
    def hturn(self, B):
        u''' hturn
        * - waits for input
        * - if E then plants a bomb
        * - else changes direction of human
        '''
        c = u''
        c = getch()
        if not B.plantbomb(c, self.loc_):
            check = symbols.ar(c)
            if check != arrow.BAD: #should be != 'BAD'
                self.dir(check)
        if not self.dir():
            raise ValueError
        if c == u'f':
            lvlchange.chfast()
    def nextlvll(self, crack, crachv):
        u''' nextlvll
        * - returns true if move to next level
        '''
        if self.loc_ == crack or self.loc_ == crack + crachv or self.loc_ == crack - crachv:
            if creature.opening:
                return True
        return False
    def loc(self):
        return self.loc_
    def dir(self, new=None):
        if not new is None:
            self.dir_ = new
        return self.dir_

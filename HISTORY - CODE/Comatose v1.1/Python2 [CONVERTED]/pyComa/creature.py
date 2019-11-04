from __future__ import absolute_import
from symbol import symbol, arrow
import board

opening = False

def check(x):
    assert x > 0
    boader = board.BOARD_REF.Boarder()
    return boader[x] == symbol.BD or boader[x] == symbol.CE or boader[x] == symbol.C or x > len(boader)

class creature(object):
    def __init__(self, location, dirr): #SYMBOLS board
        self.loc = location
        self.direction = dirr
    def turn(self): #what if goes off boader?
        u''' turn
        * - determines if the position that the creature would move into is an edge (true)
        '''
        for comp, result in [(arrow.U, self.loc - board.WIDTH),
                            (arrow.D, self.loc + board.WIDTH),
                            (arrow.L, self.loc - 1),
                            (arrow.R, self.loc + 1),
                            (None, None)
                            ]:
            if comp == self.direction:
                x = result
        if x and check(x):
            return True
        return False
    def onemove(self):
        u'''onemove
        * - if turn then the direction is changed clockwise (negative angle)
        * - if !turn then changes the loc (location) to position would move into
        '''
        if self.turn():
            for comp, result in [(arrow.U, arrow.R),
                                (arrow.D, arrow.L),
                                (arrow.L, arrow.U),
                                (arrow.R, arrow.D)
                                ]:
                if comp == self.direction:
                    self.direction = result
                    break
        else:
            for comp, result in [(arrow.U, -board.WIDTH),
                                (arrow.D, +board.WIDTH),
                                (arrow.L, -1),
                                (arrow.R, +1)
                                ]:
                if comp == self.direction:
                    self.loc += result
                    break
    def moving(self):
        u''' moving
        * - when loc (location) changes
        * - ask if there is a B (bomb)
        * - if B then move to corner (upper left @ position 0)
        * - only one loc change
        '''
        if self.loc:
            dirr = arrow.BAD
            d = self.direction
            n = 0
            while True: #do-while equivalent
                dirr = self.direction
                self.onemove()
                if dirr != self.direction and d != self.direction:
                    continue
                else:
                    break
    def cbomb(self, crack, crachv, locOFb):
        u''' cbomb
        * - ask if there is a B (bomb)
        * - if B then move to corner (upper left @ position 0)
        '''
        for n, i in enumerate(locOFb):
            global opening
            if self.loc == i:
                v = 0
                if crachv == 1:
                    v = board.WIDTH
                elif crachv == board.WIDTH:
                    v = 1
                if (self.loc == crack + v or self.loc == crack + crachv + v or self.loc == crack - crachv + v
                    or self.loc == crack - v or self.loc == crack + crachv - v or self.loc == crack - crachv - v
                    or self.loc == crack + crachv * 2 or self.loc == crack - crachv * 2):
                    opening = True
                del locOFb[n]
                self.loc = 0
                break
    def bombwall(self, crack, crachv, locOFb):
        tmp = self.loc
        self.cbomb(crack, crachv, locOFb)
        t = tmp - self.loc
        if 0 > t:
            t *= -1
        return t

class creatureR(creature):
    def __init__(self, location, dirr):
        super(creatureR, self).__init__(location, dirr) #super(creature, self)
    def onemove(self):
        if self.turn():
            for comp, result in [(arrow.U, arrow.L),
                                (arrow.D, arrow.R),
                                (arrow.L, arrow.D),
                                (arrow.R, arrow.U)
                                ]:
                if comp == self.direction:
                    self.direction = result
                    break
        else:
            for comp, result in [(arrow.U, -board.WIDTH),
                                (arrow.D, +board.WIDTH),
                                (arrow.L, -1),
                                (arrow.R, +1)
                                ]:
                if comp == self.direction:
                    self.loc += result
                    break

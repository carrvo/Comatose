from __future__ import division
from __future__ import absolute_import
from symbol import symbol, arrow
import board
import lvlchange
import sys
import time
from creature import creature, creatureR
import setlvl

class BOSS(board.board):
    def __init__(self, cr, inn):
        super(BOSS, self).__init__(None, False, inn) #super(board, self) #False for vertical
        #crhv? wBOSS? finBOSS?
        self.crBOSS = cr
    def outsideBOSS(self):
        for k in xrange(board.FIN):
            self.Boarder(k, symbol.E)
        for i in xrange(board.WIDTH):
            self.Boarder(i, symbol.BD)
        for i in xrange(board.FIN - 1, board.FIN - board.WIDTH, -1):
            self.Boarder(i, symbol.BD)
        for i in xrange(0, board.FIN, board.WIDTH):
            self.Boarder(i, symbol.BD)
        for i in xrange(board.WIDTH - 1, board.FIN + 1, board.WIDTH):
            self.Boarder(i, symbol.BD)
    def printcrackBOSS(self):
        if not board.creature.opening:
            for cr in self.crBOSS:
                self.Boarder(cr, symbol.CE)
        else:
            for cr in self.crBOSS:
                self.Boarder(cr, symbol.E)
    def printboardBOSS(self, P, H, B, CCRthis):
        self.outsideBOSS()
        self.printcrackBOSS()
        self.F(self)

        B.bombs(P.pickingup(B.bombs(), H.loc()))
        P.printp(self.Boarder())
        B.printb(self)
        self.printcBOSS(CCRthis, B)
        if H.printh():
            self.seeboard(B.bombs())
        else:
            sys.stdout.write(u"Fredrick does not wake up.\n\r")
            return True
        if not lvlchange.fast:
            time.sleep(0.250) #250ms
        time.sleep(0.250) #
        return False
    def nxtlvlBOSS(self, H):
        for cr in self.crBOSS:
            if H.nextlvll(cr, self.crachv):
                return True
        return False
    def cBOSSloc(self, C, _type):
        u''' cBOSSloc
        * - location of creatures (start)
        * - direction of creatures (start)
        '''
        t = int(board.WIDTH / 2)
        u = int(board.HEIGHT / 2)
        m = u * board.WIDTH + t
        C.append(_type(m, arrow.U))
    def printcBOSS(self, CCRthis, B):
        CCthis = self.CCthis
        class DoubleIter(object):
            def __init__(self):
                if len(CCthis) != len(CCRthis):
                    raise ValueError
                self.count = 0
            def __iter__(self):
                while self.count < len(CCthis):
                    yield (self.count, CCthis[self.count], CCRthis[self.count])
                    self.count += 1
        for count, aCC, aCCR in DoubleIter():
            aCC.moving()
            aCCR.moving()

            opennings = False
            opennings = self.openningBOSS(aCC.loc, B)
            if not opennings:
                opennings = self.openningBOSS(aCCR.loc, B)

            for cr in self.crBOSS:
                aCC.cbomb(cr, self.crachv, B.loc)
                aCCR.cbomb(cr, self.crachv, B.loc)
            board.creature.opening = opennings

            if not aCC.loc or not aCCR.loc:
                del CCthis[count]
                del CCRthis[count]

            self.Boarder(aCC.loc, symbol.C)
            self.Boarder(aCCR.loc, symbol.C)

        setlvl.nc += 1
        if setlvl.nc > setlvl.timing:
            setlvl.nc = 0
            if setlvl.TOTAL > len(self.CCthis):
                self.cBOSSloc(self.CCthis, creature)
            if setlvl.TOTAL > len(CCRthis):
                self.cBOSSloc(CCRthis, creatureR)

    def completee(self):
        for cr in self.crBOSS:
            if self.Boarder(cr + self.crachv) != symbol.B or self.Boarder(cr - self.crachv) != symbol.B:
                return False
        return True
    def clandd(self, loc):
        for cr in self.crBOSS:
            if loc == cr + self.crachv or loc == cr - self.crachv:
                return True
        return False
    def both(self, ret, BB, loc, v):
        if ret:
            for cr in self.crBOSS:
                A = cr + self.crachv
                B = cr - self.crachv
                C = self.crBOSS[8] - v
                D = self.crBOSS[7] + v
                for k,ll in enumerate(BB.loc):
                    if ll == A or ll == B or ll == C or ll == D:
                        if ll != loc:
                            del BB.loc[k]
        return ret
    def openningBOSS(self, loc, BB):
        v = 0
        if self.crachv == 1:
            v = board.WIDTH
        elif self.crachv == board.WIDTH:
            v = 1
        cland = False
        complete = True
        complete = self.completee()
        if complete and (self.Boarder(self.crBOSS[8] - v) != symbol.B or self.Boarder(self.crBOSS[7] + v) != symbol.B):
            complete = False
        cland = self.clandd(loc)
        if not cland and (loc == self.crBOSS[8] - v or loc == self.crBOSS[7] + v):
            cland = True
        return self.both(cland and complete, BB, loc, v)
    def levelBOSS(self, P, H, B, CCRthis):
        while not lvlchange.done:
            if not self.printboardBOSS(P, H, B, CCRthis):
                if self.nxtlvlBOSS(H):
                    lvlchange.done = True
            else:
                lvlchange.done = True
                lvlchange.gameover = True
    def calllvlBOSS(self, P, H, B, CCRthis):
        if not lvlchange.gameover:
            lvl = lvlchange.Thread(target=self.levelBOSS, args=(P, H, B, CCRthis))
            lvl.start()
            lvlchange.hmove(H, B)
            lvl.join()
        return lvlchange.gameover

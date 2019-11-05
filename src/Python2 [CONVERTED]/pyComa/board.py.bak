from symbol import symbol, symbols
import human
import insides
import lvlchange
import sys
import time
import creature

WIDTH = 70
HEIGHT = 20
FIN = WIDTH * HEIGHT

BOARD_REF = None

class board(object):
    def __init__(self, cr, crhv, inn):
        global BOARD_REF
        self.crack = cr
        self.F = inn
        self.CCthis = None
        if not isinstance(crhv, bool):
            self.crachv = crhv
        elif crhv:
            self.crachv = 1 #true = horizontal
        else:
            self.crachv = WIDTH #false = vertical
        self.boarder = []
        BOARD_REF = self

    def outside(self):
        for k in range(0, FIN):
            self.Boarder(k, symbol.E)
        for i in range(0, WIDTH):
            self.Boarder(i, symbol.BD)
        for i in range(FIN-WIDTH, FIN-1):
            self.Boarder(i, symbol.BD)
        for i in range(0, FIN, WIDTH):
            self.Boarder(i, symbol.BD)
        for i in range(WIDTH-1, FIN, WIDTH):
            self.Boarder(i, symbol.BD)

    def printcrack(self):
        if not creature.opening:
            self.Boarder(self.crack, symbol.CE)
            self.Boarder(self.crack - self.crachv, symbol.CE)
            self.Boarder(self.crack + self.crachv, symbol.CE)
        else:
            self.Boarder(self.crack, symbol.E)
            self.Boarder(self.crack - self.crachv, symbol.E)
            self.Boarder(self.crack + self.crachv, symbol.E)

    def printboard(self, P, H, B):
        self.outside()
        self.printcrack()
        self.F(self)

        B.bombs(P.pickingup(B.bombs(), H.loc()))
        P.printp(self.boarder)
        B.printb(self)
        self.printc(B.loc)
        if H.printh():
            self.seeboard(B.bombs())
        else:
            sys.stdout.write("Fredrick does not wake up.\n")
            return True

        if not lvlchange.fast:
            time.sleep(0.250) #250ms
        time.sleep(0.250) ##
        return False

    def nxtlvl(self, H):
        return H.nextlvll(self.crack, self.crachv)

    def seeboard(self, bombs):
        tosee = ''
        n = 1
        for i in self.Boarder():
            tosee = ''.join((tosee, i.to()))
            if n == WIDTH:
                tosee = ''.join((tosee, '\n'))
                n = 1
            else:
                n += 1
        tosee = ''.join((tosee, "BOMBS: {}\n\n".format(bombs)))
        sys.stdout.write(tosee)
        sys.stdout.flush()

    def printc(self, locOFb):
        for aCC in self.CCthis:
            aCC.moving()
            aCC.cbomb(self.crack, self.crachv, locOFb)
            if not aCC.loc:
                del aCC
            else:
                self.Boarder(aCC.loc, symbol.C)

    def setCCthis(self, pCCthis):
        self.CCthis = pCCthis
    def makesize(self):
        for _ in range(FIN):
            self.boarder.append(symbols(symbol.E))
    def Boarder(self, place=None, value=None):
        if value:
            self.boarder[place].set(value)
        elif place:
            return self.boarder[place]
        return self.boarder

class WALL(board):
    slow = None
    def __init__(self, cr, crhv, inn):
        super().__init__(cr, crhv, inn) #super(board, self)
        WALL.slow = False

    def printboard(self, P, H, B, locWall):
        self.outside()
        self.printcrack()
        self.F(self)

        B.bombs(P.pickingup(B.bombs(), H.loc()))
        P.printp(self.Boarder())
        B.printb(self)
        self.printWALL(locWall)
        self.printc(B.loc, locWall)
        if H.printh():
            self.seeboard(B.bombs())
            if WALL.slow:
                if not lvlchange.fast:
                    time.sleep(0.250) #250ms
                time.sleep(0.250)
        else:
            sys.stdout.write("Fredrick does not wake up.\n")
            return True
        if not lvlchange.fast:
            time.sleep(0.250)
        time.sleep(0.250) #
        return False

    def printWALL(self, WALL):
        for i in WALL:
            self.Boarder(i, symbol.BD)

    def printc(self, locOFb, locWall):
        for aCC in self.CCthis:
            aCC.moving()
            location = aCC.bombwall(self.crack, self.crachv, locOFb)
            if location:
                locWall.append(location)
                del aCC
            else:
                self.Boarder(aCC.loc, symbol.C)

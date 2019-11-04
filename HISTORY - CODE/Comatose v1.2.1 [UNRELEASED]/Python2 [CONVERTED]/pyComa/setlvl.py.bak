from symbol import symbol, arrow, getch
import board
import lvlchange
import insides
import BOSS
import sys
from threading import Thread
from creature import creature
from bomb import bomb
from human import human
from pickup import pickup

def basic(B):
    lvlchange.done = False
    B.resetloc()
    H = human(1000, arrow.U)
    P = pickup([1010])
    C = []
    C.append(creature(562, arrow.U))
    C.append(creature(984, arrow.D))
    C.append(creature(633, arrow.U))
    board.BOARD_REF.setCCthis(C)
    return lvlchange.calllvl(P, H, B)

def level2(B):
    lvlchange.done = False
    B.resetloc()
    H = human(1000, arrow.U)
    P = pickup([425])
    C = []
    C.append(creature(561, arrow.U))
    C.append(creature(631, arrow.U))
    C.append(creature(701, arrow.U))
    C.append(creature(562, arrow.U))
    C.append(creature(563, arrow.U))
    C.append(creature(632, arrow.U))
    C.append(creature(633, arrow.U))
    C.append(creature(702, arrow.U))
    C.append(creature(703, arrow.U))
    C.append(creature(204, arrow.L))
    board.BOARD_REF.setCCthis(C)
    return lvlchange.calllvl(P, H, B)

def ploc3(locOFp):
    ''' ploc3
    * - location of pickups
    '''
    locOFp.append(board.BOARD_REF.crack + 1)
    locOFp.append(board.BOARD_REF.crack + board.BOARD_REF.crachv + 1)
    locOFp.append(board.BOARD_REF.crack - board.BOARD_REF.crachv + 1)

def cloc3(ctot, C):
    ''' cloc3
    * - location of creatures (start)
    * - direction of creatures (start)
    '''
    for i in range(int(ctot / 2)):
        C.append(creature(283 + i * 2 * board.WIDTH, arrow.D))
    n = 0
    for i in range(int(ctot / 2), ctot):
        C.append(creature(282 + n * 2 * board.WIDTH + board.WIDTH, arrow.D))
        n += 1

def level3(B):
    lvlchange.done = False
    B.resetloc()
    H = human(990, arrow.U)
    ploc = []
    ploc3(ploc)
    P = pickup(ploc)
    C = []
    cnum = 12
    cloc3(cnum, C)
    board.BOARD_REF.setCCthis(C)
    return lvlchange.calllvl(P, H, B)


def ploc4(locOFp):
    ''' ploc4
    * - location of pickups
    '''
    t = int(board.WIDTH / 2 + 5 * board.WIDTH)
    for i in range(1, 5):
        for j in range(1, 5):
            locOFp.append(t + i + j * board.WIDTH)

def cloc4(C): # C must be empty []
    ''' cloc4
    * - location of creatures (start)
    * - direction of creatures (start)
    '''
    if C[-1].loc == 0: #[0]
        Not = [None] * 25
        t = int(board.WIDTH / 2 + 5 * board.WIDTH)
        n2 = 0
        for i in range(5):
            for j in range(5):
                Not[n2] = t + i * board.WIDTH + j + board.WIDTH
                n2 += 1
        # C must be empty []
        k = 0
        for i in range(15):
            for j in range(board.WIDTH - 10):
                t = 3 * board.WIDTH + i * board.WIDTH + 5 + j
                isNot = True
                if Not[k] == t:
                    isNot = False
                    if k != 24: #25
                        k += 1
                if isNot:
                    C.append(creature(t, arrow.U))
        board.WALL.slow = True
        class DynamicStepIter:
            """
            Derived from:
            https://mail.python.org/pipermail/tutor/2012-July/090283.html
            """
            def __init__(self, start, stop, step=1):
                self.start = start
                self.stop = len(stop)
                self.C = stop
                self.step = step
                self.cur = self.start
            def __iter__(self):
                while self.cur < self.stop:
                    yield self.cur
                    self.prev = self.cur
                    self.cur += 1
                    self.stop = len(self.C)
        stepper = DynamicStepIter(1, C, 2)
        it = iter(stepper)
        for v in it:
            del C[v]
            stepper.step += 1
            if stepper.step > 3:
                stepper.step = 1
            if v % board.WIDTH - 10 == 0:
                next(it) # it++
        return False
    return True

def cloc0(C):
    t = int(board.WIDTH / 2 + 5 * board.WIDTH)
    C.append(creature(t + board.WIDTH + 1, arrow.R))
    for n in range(901):
        insides.locOFwall[n] = 0

def lvl4creature(C):
    while not lvlchange.done and cloc4(C):
        pass

def level4(B):
    lvlchange.done = False
    B.resetloc()
    H = human(1025, arrow.U)
    ploc = []
    ploc4(ploc)
    P = pickup(ploc)
    C = [creature(0, arrow.U)] * 901
    board.BOARD_REF.setCCthis(C)
    cloc0(C)
    l4C = Thread(target=lvl4creature, args=(C,))
    l4C.start()
    tmp = lvlchange.calllvlcwall(P, H, B)
    l4C.join()
    return tmp

def ploc5(ploc):
    ''' ploc5
    * - location of pickups
    '''
    k = 0
    it = iter(range(1, board.HEIGHT, 2))
    for i in it:
        if (board.HEIGHT - 4 < i):
            next(it, None)
            k -= 6
        for j in range(1, board.WIDTH, 5):
            ploc.append(i * board.WIDTH + j + k)
        k += 3
        if k > 5:
            k -= 5
        if i > 15:
            k = 0
    for j in range(1, board.WIDTH, 5):
        ploc.append((board.HEIGHT - 1) * board.WIDTH + j + k)

def cloc5(C):
    ''' cloc5
    * - location of creatures (start)
    * - direction of creatures (start)
    '''
    t = int(board.WIDTH / 2 + board.HEIGHT / 2 * board.WIDTH)
    C.append(creature(t - board.WIDTH, arrow.L))
    C.append(creature(t - board.WIDTH, arrow.U))
    C.append(creature(t - board.WIDTH, arrow.R))
    C.append(creature(t, arrow.L))
    C.append(creature(t, arrow.R))
    C.append(creature(t + board.WIDTH, arrow.L))
    C.append(creature(t + board.WIDTH, arrow.D))

def level5(B):
    lvlchange.done = False
    B.resetloc()
    H = human(1025, arrow.U)
    ploc = []
    ploc5(ploc)
    P = pickup(ploc)
    C = []
    cloc5(C)
    board.BOARD_REF.setCCthis(C)
    return lvlchange.calllvl(P, H, B)

nc = 0
timing = 4
TOTAL = 50

def levelB(B):
    lvlchange.done = False
    B.resetloc()
    H = human(890, arrow.U)
    P = pickup([0])
    C = []
    CR = []
    board.BOARD_REF.setCCthis(C)
    return board.BOARD_REF.calllvlBOSS(P, H, B, CR)

def comatose():
    Bombs = bomb(0)
    lvlchange.fast = False
    lvlchange.gameover = False
    lvlchange.beginning()

    if not lvlchange.gameover:
        base = board.board(35, True, insides.setbasic)
        base.makesize()
        board.creature.opening = False
        lvlchange.gameover = basic(Bombs)

    if not lvlchange.gameover:
        lvl2 = board.board(35, True, insides.inside2)
        lvl2.makesize()
        board.creature.opening = False
        lvlchange.gameover = level2(Bombs)

    if not lvlchange.gameover:
        lvl3 = board.board(700, False, insides.inside3)
        lvl3.makesize()
        board.creature.opening = False
        lvlchange.gameover = level3(Bombs)

    if not lvlchange.gameover:
        insides.resetwall()
        lvl4 = board.WALL(699, False, insides.inside4)
        lvl4.makesize()
        board.creature.opening = False
        lvlchange.gameover = level4(Bombs)

    if not lvlchange.gameover:
        lvl5 = board.board(735, False, insides.inside5)
        lvl5.makesize()
        board.creature.opening = False
        lvlchange.gameover = level5(Bombs)

    if not lvlchange.gameover:
        WIDTH = board.WIDTH
        HEIGHT = board.HEIGHT
        board.WIDTH = 65
        board.HEIGHT = 20
        board.FIN = board.WIDTH * board.HEIGHT
        smile = insides.crackBOSS()
        boss = BOSS.BOSS(smile, insides.insideBOSS)
        boss.makesize()
        board.creature.opening = False
        lvlchange.speach()
        getch()
        lvlchange.gameover = levelB(Bombs)
        board.WIDTH = WIDTH
        board.HEIGHT = HEIGHT
        board.FIN = board.WIDTH * board.HEIGHT

    won = False
    if not lvlchange.gameover:
        sys.stdout.write("Fredrick wakes up!!")
        sys.stdout.flush()
        won = True
        getch()
        return False
    if not won:
        sys.stdout.write("To exit press enter. To retry press anything else.")
        sys.stdout.flush()
        c = ''
        c = getch()
        if c == '\r' or c == '\n':
            return False
    return True

if __name__ == '__main__':
    while(comatose()):
        pass

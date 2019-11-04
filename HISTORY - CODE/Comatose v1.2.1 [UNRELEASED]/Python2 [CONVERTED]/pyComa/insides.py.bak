from symbol import symbol
import board

locOFwall = None
nwall = None
def resetwall():
    global locOFwall, nwall
    locOFwall = [None]*901
    nwall = 0

def setbasic(boardd):
    pass

def inside2(boardd):
    for i in range(65):
        boardd.Boarder(284 + i, symbol.BD)

def inside3(boardd):
    for i in range(0, 14 * board.WIDTH, board.WIDTH):
        boardd.Boarder(284 + board.WIDTH + i, symbol.BD)
    boardd.Boarder(284 - 3 * board.WIDTH, symbol.BD)
    for i in range(14 + board.WIDTH, 19 * board.WIDTH, board.WIDTH):
        boardd.Boarder(i, symbol.BD)

def inside4(boardd):
    t = int(board.WIDTH / 2 + 5 * board.WIDTH)
    for i in range(6):
        boardd.Boarder(t + i, symbol.BD)
        boardd.Boarder(t + i * board.WIDTH, symbol.BD)
        boardd.Boarder(t + 5 * board.WIDTH + i, symbol.BD)
    boardd.Boarder(t + 5 + board.WIDTH, symbol.BD)
    boardd.Boarder(t + 4 * board.WIDTH + 5, symbol.BD)
    for i in range(4):
        boardd.Boarder(t + 5 + board.WIDTH + 10 + board.WIDTH * i, symbol.BD)
    for j in range(nwall):
        boardd.Boarder(locOFwall[j], symbol.BD)

def inside5(boardd):
    k = 0
    it = iter(range(1, board.HEIGHT, 2))
    for i in it:
        if board.HEIGHT - 4 < i:
            next(it, None)
            k -= 6
        for j in range(1, board.WIDTH, 5):
            boardd.Boarder(i * board.WIDTH + j + k, symbol.BD)
        k += 3
        if k > 5:
            k -= 5
        if i > 15:
            k = 0

cwall = 0
cwallm = 21

def crackBOSS():
    t = int(board.WIDTH / 2)
    u = int(board.HEIGHT / 2 + 1)
    crack = []
    crack.append(u * board.WIDTH + t)
    r = 0
    n = 1
    for i in range(1, 5):
        if n == 2:
            r += 1
            n = 0
        crack.append(u * board.WIDTH + t + i - r * board.WIDTH)
        crack.append(u * board.WIDTH + t - i - r * board.WIDTH)
        n += 1
    return crack

def insideBOSS(boardd):
    global cwall
    t = int(board.WIDTH / 2)
    u = int(board.HEIGHT / 2 - 3)
    boardd.Boarder(u * board.WIDTH + t - 2, symbol.BD)
    boardd.Boarder(u * board.WIDTH + t + 2, symbol.BD)
    boardd.Boarder((board.HEIGHT - 2) * board.WIDTH + t, symbol.BD)
    boardd.Boarder((board.HEIGHT - 3) * board.WIDTH + t, symbol.BD)
    if cwall != 0:
        boardd.Boarder((board.HEIGHT - 7) * board.WIDTH + t + 1, symbol.BD)
        boardd.Boarder((board.HEIGHT - 7) * board.WIDTH + t - 1, symbol.BD)
    cwall += 1
    if cwall >= cwallm:
        cwall = 0

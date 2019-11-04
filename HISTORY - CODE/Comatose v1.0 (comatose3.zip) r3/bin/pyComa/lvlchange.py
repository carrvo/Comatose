import board
import sys
import time
from threading import Thread
from symbol import getch

fast = False

done = False
gameover = False
skip = False

def printing(lines, ofile=None, end=None):
    d = 0.1 #100ms
    e = 10 * d
    l = 0
    for line in lines:
        for le in line:
            sys.stdout.write(le)
            sys.stdout.flush()
            if ofile:
                ofile.write(le)
            if not skip:
                time.sleep(d)
        if not skip:
            time.sleep(e)
        sys.stdout.write('\n')
        sys.stdout.flush()
        if ofile:
            ofile.write('\n')
    sys.stdout.write('\n')
    sys.stdout.flush()
    if end:
        sys.stdout.write(end)
        sys.stdout.write('\n')
        sys.stdout.flush()
    time.sleep(e)
    if ofile:
        ofile.flush()

def story():
    lines = [
        "Meet Fredrick:",
        "Fredrick has always loved action movies with lots of explosions!",
        "Fredrick also loves video games!",
        "Fredrick has a good life until one day...",
        "while his mother is driving him to school a drunk driver causes an accident.",
        "As a result Fredrick has gone into a coma. Will he ever wake up again?",
        "",
        "Help Fredrick to wake up from his coma!",
        "Complete each level and then defeat CLOWN !"
    ]
    printing(lines)

def legend():
    lines = [
        "LEGEND:",
        "F - Fredrick (you)",
        "C - creature - if you run into one game over",
        "B - bomb - can kill creatures or you",
        "P - package of bombs - run into in order to get bombs",
        "X - wall - if you run into it game over",
        "* - crack in wall - detonate a bomb beside then run into to complete level",
        "",
        "CONTROLS:",
        "w = up",
        "s = down",
        "a = left",
        "d = right",
        "space = lay a bomb (B)",
        "f = speed up/slow down",
        "",
        "Press enter after completing a level to proceed to the next level."
    ]
    with open('LEGEND.txt', mode='wt') as legend:
        printing(lines, ofile=legend,
            end="""You may open LEGEND.txt to view the legend and controls whenever you wish.
            This will NOT pause the game.
            Press enter to start.
            """)

def speach():
    clown = ["CLOWN: Can you beat my SMILE ?"]
    printing(clown)

def introduction():
    getch()
    chskp()

first = True;
def beginning():
    global first, skip
    start = Thread(target=introduction)
    sys.stdout.write("To skip press enter.\n\n")
    start.start()
    story()
    legend()
    if skip and first:
        getch()
    start.join()
    first = False

def calllvl(P, H, B):
    global gameover
    if not gameover:
        lvl = Thread(target=level, args=(P, H, B))
        lvl.start()
        hmove(H, B)
        lvl.join()
    return gameover

def calllvlcwall(P, H, B):
    global gameover
    if not gameover:
        lvl = Thread(target=levelcwall, args=(P, H, B))
        lvl.start()
        hmove(H, B)
        lvl.join()
    return gameover

def hmove(H, B):
    global done
    while not done:
        H.hturn(B)

def level(P, H, B):
    global gameover, done
    while not done:
        if not board.BOARD_REF.printboard(P, H, B):
            if board.BOARD_REF.nxtlvl(H):
                done = True
        else:
            done = True
            gameover = True

WALL = []
def levelcwall(P, H, B):
    global gameover, done
    while not done:
        if not board.BOARD_REF.printboard(P, H, B, WALL):
            if board.BOARD_REF.nxtlvl(H):
                done = True
        else:
            done = True
            gameover = True

def chskp():
    global skip
    skip = not skip
    return skip

def chfast():
    global fast
    fast = not fast
    return fast

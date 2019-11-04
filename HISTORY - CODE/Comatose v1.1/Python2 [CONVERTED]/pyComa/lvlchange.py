from __future__ import with_statement
from __future__ import absolute_import
import board
import sys
import time
from threading import Thread
from symbol import getch
from io import open

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
        sys.stdout.write(u'\n\r')
        sys.stdout.flush()
        if ofile:
            ofile.write(u'\n\r')
    sys.stdout.write(u'\n\r')
    sys.stdout.flush()
    if end:
        sys.stdout.write(end)
        sys.stdout.write(u'\n\r')
        sys.stdout.flush()
    time.sleep(e)
    if ofile:
        ofile.flush()

def story():
    lines = [
        u"Meet Fredrick:",
        u"Fredrick has always loved action movies with lots of explosions!",
        u"Fredrick also loves video games!",
        u"Fredrick has a good life until one day...",
        u"while his mother is driving him to school a drunk driver causes an accident.",
        u"As a result Fredrick has gone into a coma. Will he ever wake up again?",
        u"",
        u"Help Fredrick to wake up from his coma!",
        u"Complete each level and then defeat CLOWN !"
    ]
    printing(lines)

def legend():
    lines = [
        u"LEGEND:",
        u"F - Fredrick (you)",
        u"C - creature - if you run into one game over",
        u"B - bomb - can kill creatures or you",
        u"P - package of bombs - run into in order to get bombs",
        u"X - wall - if you run into it game over",
        u"* - crack in wall - detonate a bomb beside then run into to complete level",
        u"",
        u"CONTROLS:",
        u"w = up",
        u"s = down",
        u"a = left",
        u"d = right",
        u"space = lay a bomb (B)",
        u"f = speed up/slow down",
        u"",
        u"Press enter after completing a level to proceed to the next level."
    ]
    with open(u'LEGEND.txt', mode=u'wt') as legend:
        printing(lines, ofile=legend,
            end=u"""You may open LEGEND.txt to view the legend and controls whenever you wish.
            This will NOT pause the game.
            Press enter to start.
            """)

def speach():
    clown = [u"CLOWN: Can you beat my SMILE ?"]
    printing(clown)

def introduction():
    getch()
    chskp()

first = True;
def beginning():
    global first, skip
    start = Thread(target=introduction)
    sys.stdout.write(u"To skip press enter.\n\n\r")
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

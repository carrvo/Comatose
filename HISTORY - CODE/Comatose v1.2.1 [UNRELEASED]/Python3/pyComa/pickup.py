from symbol import symbol

class pickup(object):
    def __init__(self, ploc):
        self.loc = ploc
    def printp(self, board):
        for k in self.loc:
            #if ( board.size() < static_cast<whole>(ploc_.at(k)) )
            board[k].set(symbol.P)
    def pickingup(self, bombs, locOFh):
        ''' pickingup
        * - human lands on pickup
        returns new bombs count
        '''
        for n, i in enumerate(self.loc):
            if locOFh == i:
                del self.loc[n]
                return bombs + 10

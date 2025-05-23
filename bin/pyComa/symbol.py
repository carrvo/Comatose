from getch import getch

class Enum(object):
    def __init__(self, val_out):
        self.__values__ = []
        self.__out__ = []
        self.__to__ = {}
        self.__from__ = {}
        for val, out in val_out:
            self.__values__.append(val)
            self.__out__.append(out)
            self.__to__.update({val:out})
            self.__from__.update({out:val})
    def to(self, val):
        return self.__to__.get(val)
    def fromm(self, out):
        return self.__from__.get(out)
    def get(self, val):
        if val in self.__values__:
            return val
    def __getattr__(self, val):
        if not val in self.__values__:
            raise AttributeError('value {} does not exist'.format(val))
        return self.get(val)

symbol = Enum([
    ('C', 'C'),
    ('P', 'P'),
    ('BD', 'X'),
    ('E', ' '),
    ('CE', '*'),
    ('B', 'B'),
    ('F', 'F'),
])

arrow = Enum([
    ('U', 'w'),
    ('D', 's'),
    ('R', 'd'),
    ('L', 'a'),
    ('BAD', None) #WARNING
])

class symbols(object):
    def __init__(self, sym):
        self.set(sym)
    def sym(self, symm=None):
        if symbol.get(symm):
            self.sym_ = symm
        return self.sym_
    def to(self):
        return symbol.to(self.sym_)
    def fromm(self, c):
        self.sym_ = symbol.fromm(c)
        return self.sym_
    def set(self, sym):
        if isinstance(sym, symbols):
            self.sym_ = sym.sym_
        elif symbol.get(sym):
            self.sym_ = sym
        else:
            self.fromm(sym)
    @classmethod
    def ar(cls, c):
        return arrow.fromm(c)
    def __eq__(self, other):
        if isinstance(other, symbols):
            return self.sym_ == other.sym_
        else:
            return self.sym_ == other
    def __ne__(self, other):
        return not self == other
'''
    symbol& symbols::operator = (char c)
    {
        return fromm(c);
    }
'''

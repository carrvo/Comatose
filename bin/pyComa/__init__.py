import sys
import os
pathextend = os.path.dirname(os.path.realpath(__file__))
sys.path.insert(1, pathextend)
from setlvl import comatose

__all__ = ['comatose']

#!/bin/python
from __future__ import absolute_import
try:
    from pyComa import comatose
    while(comatose()):
        pass
except Exception as error:
    print(error)
finally:
    print()
    input()

#!/bin/py -3
try:
    from pyComa import comatose
    while(comatose()):
        pass
except Exception as error:
    print(error)
finally:
    print()
    input('Press to exit.')

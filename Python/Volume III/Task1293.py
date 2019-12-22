# Topic: elementary

import sys
import functools

data = map(int, sys.stdin.readline().split())
print(2 * functools.reduce(lambda x, y: x * y, data))

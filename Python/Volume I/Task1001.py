# Topic: elementary

import math
import sys

numbers = []

for line in sys.stdin:
    for number in line.split():
        numbers.append(float(number))

numbers.reverse()

for number in numbers:
    print('%.4f' % math.sqrt(number))

# Topic: elementary

import sys

number = int(sys.stdin.readline())
print('YES' if (12 - number) * 45 <= 4 * 60 else 'NO')

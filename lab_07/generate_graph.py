from random import *
import sys

count = int(sys.argv[1])

with open('data/test2.txt', 'w') as f:
    f.write(str(count) + '\n')
    for i in range(count):
        for j in range(count):
            f.write('0 ' if i == j else str(randint(0, 20)) + (' ' if j < count - 1 else '\n'))

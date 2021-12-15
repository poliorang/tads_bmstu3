from random import *
import sys

count = int(sys.argv[1])

a = [0] * count


for i in range(int(count)):
    buf = randint(-50, 200)
    while buf in a:
        buf = randint(-50, 200)
    a[i] = buf

shuffle(a)

with open('data/test2.txt', 'w') as f:
    for j in range(count):
        f.write(str(a[j]) + (' ' if j < count - 1 else ''))
    f.write('\n')

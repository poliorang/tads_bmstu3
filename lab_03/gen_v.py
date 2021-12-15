from random import *
import sys

r = int(sys.argv[1])
d = int(sys.argv[2])

a = [0] * r

for i in range(int(round(r*(100-d)/100))):
    a[i] = randint(1, 9)

shuffle(a)

with open('vector.txt', 'w') as f:
    for j in range(r):
        f.write(str(a[j]) + (' ' if j < r - 1 else ''))
    f.write('\n')

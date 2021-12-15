from random import randint

while True:
    n = int(input('\nInput count of number: '))
    f = open("out.txt", 'w')

    for i in range(n):
        #f.write(str(randint(-100, 100)) + ' ')
        print(str(randint(-100, 100)) + ' ', end='')

    f.close()
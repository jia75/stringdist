import random
import string

length = 10000
w = open("words.txt", "r")
f = open("random-generated.txt", "a")
for a in range(length):
    n = abs(round(random.gauss(2, 1.5)))
    word = w.readline()[:-1]
    for i in range(n):
        b = random.randrange(0, len(word))
        word = "".join(word[:b]+random.choice(string.ascii_lowercase)+word[(b+1):])
    f.write(word+"\n")
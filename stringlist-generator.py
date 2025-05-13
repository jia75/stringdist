import random
import string

length = int(input("Select amount of strings"))

f = open("random-generated.txt", "a")
for a in range(length):
    n = round(random.gauss(100, 1.5))
    genstr = "".join(random.choices(string.ascii_lowercase, k=n))
    f.write(genstr + "\n")
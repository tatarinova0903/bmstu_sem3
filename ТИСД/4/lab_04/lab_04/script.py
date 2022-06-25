import random
import os
import string

for size in [10, 50, 100, 250, 500, 750, 1000]:
    f = open(str(size) + ".txt", 'w')
    f.write(str(size) + "\n")
    for i in range(0, size):
        word_len = random.randint(1,19)
        word = ""
        for j in range(word_len):
            word += random.choice(string.ascii_letters)
        f.write(word + "\n")
    f.close()

for size in [10, 50, 100, 250, 500, 750, 1000]:
    os.system("./test.exe < " + str(size) + ".txt")
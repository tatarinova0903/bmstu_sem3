from sys import argv

def compare(file_name_1, file_name_2):
    file = open(file_name_1)
    res = ""
    for line in file:
        for c in line:
            if c.isdigit() or c == " " or c == "." or c == "\n":
                res += c
    res = res.strip()
    file = open(file_name_2)
    i = 0
    for line in file:
        for c in line:
            if c.isdigit() or c == ".":
                if i >= len(res) or res[i] != c:
                    return 0
                i += 1
            while i < len(res) and not res[i].isdigit() and res[i] != ".":
                i += 1
    return 1

file_name_1 = argv[1]
file_name_2 = argv[2]

if compare(file_name_1, file_name_2):
    print("1")
else:
    print("0")

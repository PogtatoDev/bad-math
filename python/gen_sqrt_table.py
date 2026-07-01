from math import sqrt

table = open("sqrt_table.txt", "w")
l = [sqrt(i) for i in range(1, 2048)]

table.write("{")
for i in l:
    table.write(str(i))
    table.write(", ")
    table.write("\n")

table.write("}")
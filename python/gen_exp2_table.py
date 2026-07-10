from math import exp2

table = open("exp_table.txt", "w")
l = [exp2(i/32) for i in range(0, 1024 * 32)]

table.write("{")
for i in l:
    table.write(str(i))
    table.write(", ")
    table.write("\n")

table.write("}")
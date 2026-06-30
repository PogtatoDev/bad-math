from math import exp

table = open("exp_table.txt", "w")
l = [exp(i) for i in range(-710, 710)]

table.write("{")
for i in l:
    table.write(str(i))
    table.write(", ")
    table.write("\n")

table.write("}")
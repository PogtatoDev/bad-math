from math import log

table = open("log_table.txt", "w")
l = [log(i) for i in range(1, 1024)]

table.write("{")
for i in l:
    table.write(str(i))
    table.write(", ")
    table.write("\n")

table.write("}")
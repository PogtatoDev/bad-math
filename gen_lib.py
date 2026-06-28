import os

os.remove("include/full_lib.hpp")
headers = os.listdir("./include/")
lib = open("./include/full_lib.hpp", "w")
lib.write("#pragma once\n")

for header in headers:
    if header.endswith(".hpp"):
        lib.write("#include ") 
        lib.write('"')
        lib.write(header)
        lib.write('"\n')

print("generated file full_lib.hpp")
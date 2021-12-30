import glob
import os
def obj_name(path):return path.replace("/","_").replace(".cpp","").replace(".asm","").replace(".","")+".o"
def cpp(path):
    if ".cpp" in path:return True
    return False
def asm(path):
    if ".asm" in path:return True
    return False
cpp_files = []
asm_files = []
for x in os.walk("."):
    folder=x[0]
    for i in x[2]:
        if cpp(folder+"/"+i):
            cpp_files.append(folder+"/"+i)
        elif asm(folder+"/"+i):
            asm_files.append(folder+"/"+i)

obj_list=[]
modified=False
nasm="nasm -f elf"
for x in asm_files:
    obj=obj_name(x)
    if os.path.exists("./build/"+obj):
        if os.path.getmtime(x)>os.path.getmtime("./build/"+obj):
            os.system(f"{nasm} {x} -o ./build/{obj}")
            print(f"{nasm} {x} -o ./build/{obj}")
            modified=True
    else:
        os.system(f"{nasm} {x} -o ./build/{obj}")
        print(f"{nasm} {x} -o ./build/{obj}")
        modified=True
    obj_list.append("./build/"+obj)

clang="clang++  -m32 -ffreestanding -fno-exceptions -fno-rtti"
for x in cpp_files:
    obj=obj_name(x)
    if os.path.exists("./build/"+obj):
        if os.path.getmtime(x)>os.path.getmtime("./build/"+obj):
            os.system(f"{clang} -c {x} -o ./build/{obj}")
            print(f"{clang} -c {x} -o ./build/{obj}")
            modified=True
    else:
        os.system(f"{clang} -c {x} -o ./build/{obj}")
        print(f"{clang} -c {x} -o ./build/{obj}")
        modified=True
    obj_list.append("./build/"+obj)

linker="clang++ -T linker.ld -o iso/boot/toyos -nostdlib -nodefaultlibs -lgcc -m32 "
if modified:
    for x in obj_list:
        linker+=" "+x
    print(linker)
    os.system(linker)

grub="grub-mkrescue iso --output=toy.iso"
os.system(grub)
print(grub)

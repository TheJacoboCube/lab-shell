# This is just nice when there are a ton of errors, you keep compiling, and need a 
# visual separator.
echo -e "\n\e[31m-----------------------------------------------\e[0m\n";

# Actually do the compilation and stick it in bin/shell.o.
gcc -g -o bin/shell.o shell.c;
gdb bin/shell.o;

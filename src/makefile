lc3: lc3.o debug_tools.o test_functions.o
	gcc lc3.o debug_tools.o test_functions.o -o lc3

lc3.o: lc3.c lc3.h
	gcc -c lc3.c

debug_tools.o: debug_tools.c debug_tools.h
	gcc -c debug_tools.c

test_functions.o: test_functions.c test_functions.h
	gcc -c test_functions.c

# Change this if using *nix os
clean:
	del *.o

debug:
	gcc -g lc3.c test_functions.c debug_tools.c -o lc3
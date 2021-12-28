lc3: lc3.o debug_tools.o
	gcc lc3.o debug_tools.o -o lc3

lc3.o: lc3.c
	gcc -c lc3.c

debug_tools.o: debug_tools.c
	gcc -c debug_tools.c

# Change this if using *nix os
clean:
	del *.o
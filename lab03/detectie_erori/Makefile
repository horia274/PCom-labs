all: link send recv 

link:
	make -C link_emulator

send: send.o link_emulator/lib.o parity.o
	gcc -g $^ -o send

recv: recv.o link_emulator/lib.o parity.o
	gcc -g $^ -o recv

parity.o: parity.c parity.h
	gcc -g -c $< -o $@

.c.o: 
	gcc -Wall -g -c $? 

clean:
	rm -f *.o send recv 

all:run

compile:connectTest.c
	gcc -o connectTest connectTest.c #-lbluetooth

run:compile
	./connectTest

clean:
	rm -rf *# *~ connectTest bluetest

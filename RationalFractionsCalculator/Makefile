calc: rational calc.o
	gcc -g -o calc calc.o -L./rational -lrational

calc.o: calc.c
	gcc -g -O0 -c calc.c

.PHONY: rational
rational:
	cd rational && $(MAKE)

clean:
	rm task6 *.o
	
librational.so: rational.o rat_math.o rat_io.o
	gcc -fPIC -shared -o librational.so rational.o rat_math.o rat_io.o

rational.o: rational.c
	gcc -g -O0 -c rational.c

rat_math.o: rat_math.c
	gcc -g -O0 -c rat_math.c
	
rat_io.o: rat_io.c
	gcc -g -O0 -c rat_io.c

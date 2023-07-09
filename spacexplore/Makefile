spacexplore: spacexplore.o
	gcc -o spacexplore spacexplore.o `pkg-config --libs sdl SDL_ttf`

spacexplore.o: spacexplore.c
	gcc -c -Wall -Wextra -Wno-switch spacexplore.c `pkg-config --cflags sdl SDL_ttf`
clean:
	rm spacexplore *.o

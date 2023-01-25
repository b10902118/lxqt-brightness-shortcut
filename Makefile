all:
	gcc brightness.c -o release -O2 `pkg-config --cflags --libs libnotify`
debug:
	gcc -DDEBUG brightness.c -o debug `pkg-config --cflags --libs libnotify` 



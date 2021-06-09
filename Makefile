all:
	gcc main.c -o wav

fullc:
	rm wav gen.wav
clean:
	rm wav *.hexer *.hexer.*

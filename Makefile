all:
	gcc main.c -o wav -lm

fullc:
	rm wav gen.wav
clean:
	rm wav *.hexer *.hexer.*

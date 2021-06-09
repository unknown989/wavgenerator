all:
	gcc main.c -o wav -lm

clean:
	rm wav gen.wav

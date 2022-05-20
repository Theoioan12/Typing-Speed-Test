all: clear build run

build:
	gcc TypingSpeedTest.c GraphicsLib.c -o TypingSpeedTest -lncurses
clear:
	rm TypingSpeedTest
run:
	valgrind -s ./TypingSpeedTest

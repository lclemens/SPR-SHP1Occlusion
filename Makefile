all:
	gcc -O3 driveElli1.c -o elli1.x -lm

run:
	gcc -O3 driveElli1.c -o elli1.x -lm

	./elli1.x params.txt FirstVerboseTest 1

all:
	gcc -O3 driveElli1.c -o elli1.x -lm

run:
	gcc -O3 driveElli1.c -o elli1.x -lm

	./elli1.x params.txt TwoITIMsMovie 1

batch:

	gcc -O3 driveElli1.c -o elli1.x -lm

	chmod a+x batchElli1.sh
	
	./batchElli1.sh 7 v

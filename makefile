all:obst.out tromino.out floyd.out

obst.out:obst.c
	gcc obst.c -o obst.out

tromino.out:tromino.c
	gcc tromino.c -o tromino.out -lm

floyd.out:floyd.c
	gcc floyd.c -o floyd.out

clean:
	rm obst.out tromino.out floyd.out
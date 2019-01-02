othello:main.c check_and_flipover.c init_hash.c
	gcc -o othello main.c check_and_flipover.c init_hash.c
clean:
	rm othello

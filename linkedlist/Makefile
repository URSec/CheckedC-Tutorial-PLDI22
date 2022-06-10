all: ll checked_ll

ll: linkedlist.c
	$(CC) $^ -O3 -o linkedlist

checked_ll: checked_ll.c
	$(CC) $^ -O3 -o checked_ll

clean:
	rm -f linkedlist checked_ll

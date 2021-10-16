CFLAGS := -O3 -Wno-nullability-completeness

SRC := sum2array.c
SRC_CHECKED := sum2array_checked.c

.PHONY: clean

sum2array: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

checked: $(SRC_CHECKED)
	$(CC) $(CFLAGS) $^ -o sum2array_checked

clean:
	rm -f sum2array sum2array_checked *.o *.s *.ll

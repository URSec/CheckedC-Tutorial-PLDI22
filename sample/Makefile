
#
# TODO: Set CC to the 3C clang.
#
CC := $(LLVM_DIR)/bin/clang

CFLAGS := -O3 -Wno-nullability-completeness

SRC := sum2array.c
SRC_CHECKED := sum2array_checked.c

.PHONY: clean

sum2array: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

checked: $(SRC_CHECKED)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f sum2array *.o *.s *.ll

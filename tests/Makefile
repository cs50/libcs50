CC := cc
CFLAGS := -g -I../build/include/ -Wall -Werror

# Link against staitc lib because shared lib requires ldconfig
LDLIBS := -L../build/lib/ -l:libcs50.a

EXEC := get_int get_int_formatted_prompt get_string get_string_formatted_prompt

.PHONY: all
all: $(EXEC)

%: %.c ../src/cs50.c ../src/cs50.h ../Makefile libcs50
	$(CC) $(CFLAGS)  "$@.c" -o "$@" $(LDLIBS)

libcs50:
	# Build all libs (shared and static)
	make -C ../ build/lib/libcs50.so

clean:
	make -C ../ clean
	rm -rf $(EXEC)

CC ?= cc
CFLAGS ?= -std=gnu99 -O2 -Wall -Wextra -Wpedantic
SOURCES = src/utils.c src/hashtable.c src/stack.c src/ai.c

pegsol: $(SOURCES) peg_solitaire.c src/*.h
	$(CC) $(CFLAGS) $(SOURCES) peg_solitaire.c -o $@

.build/test-core: $(SOURCES) tests/test_core.c src/*.h
	mkdir -p .build
	$(CC) $(CFLAGS) $(SOURCES) tests/test_core.c -o $@

test: pegsol .build/test-core
	.build/test-core
	python3 -B tests/test_cli.py

sanitize:
	mkdir -p .build
	$(CC) -std=gnu99 -O1 -g -Wall -Wextra -Wpedantic -fsanitize=address,undefined -fno-omit-frame-pointer $(SOURCES) tests/test_core.c -o .build/test-core-sanitize
	.build/test-core-sanitize
	$(CC) -std=gnu99 -O1 -g -fsanitize=address,undefined $(SOURCES) peg_solitaire.c -o .build/pegsol-sanitize
	PROGRAM=$(CURDIR)/.build/pegsol-sanitize python3 -B tests/test_cli.py

clean:
	rm -f pegsol src/*.o peg_solitaire.o .build/test-core .build/test-core-sanitize .build/pegsol-sanitize

.PHONY: test sanitize clean

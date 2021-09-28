
all: foo

foo: foo.c
	$(CC) foo.c -o foo -Wall -O3

install:
	mkdir $$DESTDIR || :
	cp foo $$DESTDIR

clean:
	rm -f foo.o foo

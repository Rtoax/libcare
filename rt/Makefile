all: foo
	
foo: foo.c
	$(CC) -o $@ $<

clean:
	rm -f foo

install: foo
	mkdir $$DESTDIR || :
	cp foo $$DESTDIR

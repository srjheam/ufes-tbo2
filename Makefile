# Esse Makefile é apenas um wrapper para cumprir com as especificações do trabalho.

MAKE = make

OUTRELEASEPATH = src/build/release/main
OUTDEBUGPATH = src/build/debug/main

all: release

release:
	$(MAKE) -C src/
	cp -f $(OUTRELEASEPATH) ./trab2

debug:
	$(MAKE) -C src/ debug
	cp -f $(OUTDEBUGPATH) ./trab2

clean:
	$(MAKE) -C src/ clean
	rm -f trab2
	rm -f valgrind-out.txt
	rm -f *.mst *.tsp *.tour

valgrind:
	$(MAKE) -C src/ valgrind VALARGS="../$(VALARGS)"
	cp -f src/valgrind-out.txt ./valgrind-out.txt

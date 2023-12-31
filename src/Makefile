# stolen from
#  - ../tsplib/Makefile
#  - https://github.com/srjheam/ufes-csci/blob/dbc4c0b9e87dde27a2be233daf57db55fec9d9b4/csci/tests/Makefile

# Makefile que percorre toda a biblioteca, procurando os códigos fontes .c para compilar

LIBCONTAINERSDIR       = containerslib
LIBCONTAINERS          = containers
LIBCONTAINERSDIRRELEASE = $(LIBCONTAINERSDIR)/build/release
LIBCONTAINERSDIRDEBUG   = $(LIBCONTAINERSDIR)/build/debug

LIBRTTDIR       = rttlib
LIBRTT          = rtt
LIBRTTDIRRELEASE = $(LIBRTTDIR)/build/release
LIBRTTDIRDEBUG   = $(LIBRTTDIR)/build/debug

OUT            = main

BUILDIR = build
DEBUGDIR = $(BUILDIR)/debug
RELEASEDIR = $(BUILDIR)/release

# CCompiler - é o compilador usado
# CFLAGS - são as flags dadas ao compilador durante a compilação
CC = gcc
override CFLAGS += -Wall -Wextra -I $(LIBRTTDIR)/include -I $(LIBCONTAINERSDIR)/include -lm

DEBUGFLAGS = -ggdb3 -O0 -DDEBUG
RELEASEFLAGS = -O3 -DNDEBUG

MAKE = make

VALGRINDOUT = valgrind-out.txt

all : release

release : pre-build-release build-release

debug: pre-build-debug build-debug

# Preparativos para o build; Garante que o diretório build/ existe
pre-build:
	mkdir -p $(BUILDIR)/

pre-build-release: pre-build
	mkdir -p $(RELEASEDIR)/
	$(MAKE) -C $(LIBCONTAINERSDIR)/
	$(MAKE) -C $(LIBRTTDIR)/

pre-build-debug: pre-build
	mkdir -p $(DEBUGDIR)/
	$(MAKE) -C $(LIBCONTAINERSDIR)/ debug
	$(MAKE) -C $(LIBRTTDIR)/ debug

build-release : main.c
	$(CC) -o $(RELEASEDIR)/$(OUT) $< -L $(LIBRTTDIRRELEASE) -l$(LIBRTT) -L $(LIBCONTAINERSDIRRELEASE) -l$(LIBCONTAINERS) $(CFLAGS) $(RELEASEFLAGS)

build-debug : main.c
	$(CC) -o $(DEBUGDIR)/$(OUT) $< -L $(LIBRTTDIRDEBUG) -l$(LIBRTT) -L $(LIBCONTAINERSDIRDEBUG) -l$(LIBCONTAINERS) $(CFLAGS) $(DEBUGFLAGS)

# Rode make clean para remover tudo que é gerado pela build
clean:
	rm -rf $(BUILDIR)/ $(VALGRINDOUT)
	$(MAKE) -C $(LIBCONTAINERSDIR)/ clean
	$(MAKE) -C $(LIBRTTDIR)/ clean
	rm -f *.mst *.tsp *.tour

valgrind: debug
	rm -f $(VALGRINDOUT)

	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --verbose \
			 --log-file=$(VALGRINDOUT) \
			 ./$(DEBUGDIR)/$(OUT) $(VALARGS)

	@echo "Head to $(VALGRINDOUT)"

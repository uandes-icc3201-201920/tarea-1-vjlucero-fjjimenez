# TODO: Crear el Makefile...
CFLAGS = -g
ASCIIDOC=/usr/bin/asciidoc
DOC = Unix_domain_sockets.html
PROGS = client server

all: $(PROGS) $(DOC)

server: server.cpp
client: client.cpp

Unix_domain_sockets.html: Unix_domain_sockets.txt
	if [ -x $(ASCIIDOC) ]; then $(ASCIIDOC) $<; fi

.PHONY: clean

clean:
	rm -f *.o socket $(PROGS)

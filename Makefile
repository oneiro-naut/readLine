IDIR =include
CC=gcc
CFLAGS=-I$(IDIR)

CDIR=src
BDIR=build/debug
ODIR=src
#PREFIX is environment variable, but if it is not set, then set default value
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif
DEPS = $(wildcard $(IDIR)/*.h)

SRC = $(wildcard $(CDIR)/*.c)

readline: $(SRC)
	mkdir -p $(BDIR)
	$(CC) -g -c $^ $(CFLAGS)
	ar rcs $(BDIR)/libreadLine.a *.o
	ar -t $(BDIR)/libreadLine.a
	rm *.o
	$(CC) -g -fPIC -c $^ $(CFLAGS)
	$(CC) -shared -o $(BDIR)/libreadLine.so *.o
	rm *.o

install: $(BDIR)/libreadLine.a $(BDIR)/libreadLine.so
	install -d $(PREFIX)/lib/
	install -m 644 $(BDIR)/libreadLine.so $(PREFIX)/lib/
	install -m 644 $(BDIR)/libreadLine.a $(PREFIX)/lib/
	install -d $(PREFIX)/include/readLine
	install -m 644 $(DEPS) $(PREFIX)/include/readLine
	echo "/usr/local/lib" > /etc/ld.so.conf.d/local.conf
	ldconfig
	
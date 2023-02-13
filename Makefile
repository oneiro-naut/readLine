#PREFIX is environment variable, but if it is not set, then set default value
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

INCDIR =./include
CC=gcc
LD=gcc
INCFLAGS=-I$(INCDIR)
CFLAGS=-std=gnu99 -fPIC

SRCDIR=./src
OBJDIR=./obj
LIBDIR =./lib

LIBS=

SRCS = $(wildcard $(SRCDIR)/*.c)
HEADERS= $(wildcard $(INCDIR)/*.h)
OBJLIST = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
SRCLIST=

readline: $(LIBDIR)/libreadLine.a $(LIBDIR)/libreadLine.so

$(LIBDIR)/libreadLine.a: $(OBJLIST)
	mkdir -p $(LIBDIR)
	ar rcs $@ $^
	ar -t $@

$(LIBDIR)/libreadLine.so: $(OBJLIST)
	mkdir -p $(LIBDIR)
	$(CC) -shared $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -g $(CFLAGS) $(INCFLAGS) -c $^ -o $@

clean:
	rm lib/* obj/*

install: $(LIBDIR)/libreadLine.a $(LIBDIR)/libreadLine.so
	install -d $(PREFIX)/lib/
	install -m 644 $(LIBDIR)/libreadLine.so $(PREFIX)/lib/
	install -m 644 $(LIBDIR)/libreadLine.a $(PREFIX)/lib/
	install -d $(PREFIX)/include/readLine
	install -m 644 $(HEADERS) $(PREFIX)/include/readLine
	echo "/usr/local/lib" > /etc/ld.so.conf.d/local.conf
	ldconfig


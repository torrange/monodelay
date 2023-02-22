#!/usr/bin/make -f

include Makefile.mk

PREFIX  ?= /usr/local
DESTDIR ?=


all: build

build: monodelay.c
	$(CC) $^ $(BUILD_C_FLAGS) $(LINK_FLAGS) -lm $(SHARED) -o monodelay.lv2/monodelay$(LIB_EXT)

clean:
	rm -f monodelay.lv2/monodelay$(LIB_EXT)

install:
	sudo install -d $(DESTDIR)$(PREFIX)/lib/lv2/monodelay.lv2
	sudo install -m 644 monodelay.lv2/*.so  $(DESTDIR)$(PREFIX)/lib/lv2/monodelay.lv2/
	sudo install -m 644 monodelay.lv2/*.ttl $(DESTDIR)$(PREFIX)/lib/lv2/monodelay.lv2/

uninstall:
	sudo rm -rf $(DESTDIR)$(PREFIX)/lib/lv2/monodelay.lv2

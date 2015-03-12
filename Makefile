-include Makefile.local
-include Makefile.include

CFLAGS += -fPIC
CFLAGS += -I.
CFLAGS += $(PYTHON_CFLAGS)
CFLAGS += $(NANOMSG_CFLAGS)
LDFLAGS += $(PYTHON_LDFLAGS)
LDFLAGS += $(NANOMSG_LDFLAGS)


TARGETS  = py2

all:
	echo "Specify target py2 or py3"

py2: nanomsg2module.so

nanomsg2module.so: nanomsg2.c
	$(CC) $(CFLAGS) -shared -o $@ $< $(LDFLAGS)

submodule:
	git submodule init
	git submodule update

third-party: submodule
	cd third-party/nanomsg \
		&& if test ! -f build/lib/libnanomsg.a; then \
				./autogen.sh \
					&& CFLAGS="$$CFLAGS -fPIC" ./configure --enable-static --disable-shared --prefix=`pwd`/build \
					&& make V=1 \
					&& make install; \
		fi;


clean:
	rm -f *.o
	rm -f *.so
	rm -f $(TARGETS)
	
.PHONY: all clean

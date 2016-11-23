CC         = gcc -pipe -m32
 
ifneq (,$(findstring run,$(firstword $(MAKECMDGOALS))))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif
 
BINDIR     = bin
 
CFLAGS     = -c -Wall -std=c++0x -fPIC -w -O3 -funroll-loops -fpermissive
LDFLAGS    =
 
SOURCES    = $(wildcard src/*.c)
OBJECTS    = $(SOURCES:.c=.o)

EXECUTABLE = $(BINDIR)/gnode
LIBRARY    = $(BINDIR)/libgnode.so
GNODE      = gnode.js
 
CFLAGS     += -Iinclude
 
LDFLAGS    += -L/usr/local/lib -Llib

LDFLAGS    += -lpthread

all: exe lib
 
exe: $(SOURCES) $(EXECUTABLE)

lib: $(SOURCES) $(LIBRARY)

$(EXECUTABLE): $(OBJECTS)
	-mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(LIBRARY): $(OBJECTS)
	-mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) -shared
 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
 
node: all
ifeq (,$(wildcard node/bin/node))
	node $(GNODE)
else
	node/bin/node $(GNODE)
endif

run: all
	$(EXECUTABLE) $(RUN_ARGS)
 
clean:
	-rm -f $(OBJECTS) $(EXECUTABLE) $(LIBRARY)


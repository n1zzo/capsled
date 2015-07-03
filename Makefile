CC=gcc -std=c99
UNAME_V := $(shell uname -v)
OUTFILE=capsled

ifeq ($(findstring Ubuntu,$(UNAME_V)),Ubuntu)
	CCFLAGS += -D TARGET_UBUNTU
else ifeq ($(findstring Debian,$(UNAME_V)),Debian)
	CCFLAGS += -D TARGET_DEBIAN
else
	CCFLAGS += -D TARGET_UNKNOWN
endif

all: capsled.c
	$(CC) $(CCFLAGS) -o $(OUTFILE) $^

clean:
	rm -f capsled

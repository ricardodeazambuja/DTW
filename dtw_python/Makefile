CC=gcc
CFLAGS=-fPIC -O3 -lpthread -std=gnu99 -Wall -ffast-math -mtune=native

# http://stackoverflow.com/a/12099167
UNAME_S := $(shell uname -s)

# Linux
ifeq ($(UNAME_S),Linux)
		CFLAGS += -lrt -lm
		LDFLAGS = -Wl,-soname,dtw_python.so

endif

# MacOS
ifeq ($(UNAME_S),Darwin)
		LDFLAGS = -Wl,-install_name,dtw_python.so
endif


# debug:
# 	CFLAGS += -g

all: compile

compile:
	@echo "Creating directories..."
	mkdir -p ./bin
	mkdir -p ./bin/obj
	mkdir -p ./bin/lib
	@echo "Finalising..."
	$(CC) -shared $(LDFLAGS) -o ./bin/lib/dtw_python.so ./src/dtw_python.c $(CFLAGS)
	@echo "Done!"

install:
	@echo "Installing the C library..."
	cp ./bin/lib/dtw_python.so /usr/local/lib/dtw_python.so
	@echo "Installing the Python module..."
	python setup.py install
	@echo "Done!"
	@echo "From Python, import dtw_python to use it."

clean:
	rm -r -f bin
	rm -r -f build

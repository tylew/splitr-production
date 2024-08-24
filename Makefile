CC=gcc
CFLAGS=-Iinclude
DEPS = $(wildcard include/*.h)
OBJ = $(patsubst %,src/%,$(OBJ_NAMES))

OBJ_NAMES = main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: myproject

myproject: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lbluetooth

clean:
	rm -f src/*.o *~ core myproject

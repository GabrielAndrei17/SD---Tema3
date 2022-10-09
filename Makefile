CC=gcc
CFLAGS=-Wextra -g
OBJ=main.o auxarb.o
TARGET=tema3

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f *.o $(TARGET) *~



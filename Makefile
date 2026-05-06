CC =  gcc
CFLAGS = -Wall
TARGET = out

all: $(TARGET)
$(TARGET): matrix.c func.h
	$(CC) $(CFLAGS) matrix.c main.c -o $(TARGET)
src = "matrix.c main.c"

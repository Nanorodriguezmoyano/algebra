CC =  gcc
CFLAGS = -Wall
TARGET = out

all: $(TARGET)
$(TARGET): matrix.c func.h
	$(CC) $(CFLAGS) matrix.c -o $(TARGET)
src = matrix.c

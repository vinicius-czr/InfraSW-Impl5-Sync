CC = gcc
CFLAGS = -Wall -Wextra -g -pthread -I.

TARGET = sync_car
SRC = sync_car.c sync_car-runner.c

all: $(TARGET)

$(TARGET): $(SRC) sync_car.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
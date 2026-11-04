CC = gcc
CFLAGS = -Wall -Wextra -g -pthread -I.

TARGET = sync_car
SRC = sync_car.c sync_car-runner.c

TEST_DIR = testes
TEST_WAIT_BIN = $(TEST_DIR)/test_unitario

all: $(TARGET)

$(TARGET): $(SRC) sync_car.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

test-wait: sync_car.c $(TEST_DIR)/test_unitario.c sync_car.h
	$(CC) $(CFLAGS) -o $(TEST_WAIT_BIN) sync_car.c $(TEST_DIR)/test_unitario.c

clean:
	rm -f $(TARGET) *.o $(TEST_WAIT_BIN)

.PHONY: all clean test-wait
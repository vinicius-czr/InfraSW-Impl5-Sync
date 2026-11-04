CC = gcc
CFLAGS = -Wall -Wextra -g -pthread -I.

TARGET = sync_car
SRC = sync_car.c sync_car-runner.c

TEST_DIR = testes
TEST_WAIT_BIN = $(TEST_DIR)/test_unitario
TEST_LIMITE_BIN = $(TEST_DIR)/test_caso_limite
TEST_ATRASADO_BIN = $(TEST_DIR)/test_atrasado
TEST_VAZIO_BIN = $(TEST_DIR)/test_car_vazio

all: $(TARGET)

$(TARGET): $(SRC) sync_car.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

test-wait: sync_car.c $(TEST_DIR)/test_unitario.c sync_car.h
	$(CC) $(CFLAGS) -o $(TEST_WAIT_BIN) sync_car.c $(TEST_DIR)/test_unitario.c

test-limite: sync_car.c $(TEST_DIR)/test_caso_limite.c sync_car.h
	$(CC) $(CFLAGS) -o $(TEST_LIMITE_BIN) sync_car.c $(TEST_DIR)/test_caso_limite.c

test-atrasado: sync_car.c $(TEST_DIR)/test_atrasado.c sync_car.h
	$(CC) $(CFLAGS) -o $(TEST_ATRASADO_BIN) sync_car.c $(TEST_DIR)/test_atrasado.c

test-vazio: sync_car.c $(TEST_DIR)/test_car_vazio.c sync_car.h
	$(CC) $(CFLAGS) -o $(TEST_VAZIO_BIN) sync_car.c $(TEST_DIR)/test_car_vazio.c

clean:
	rm -f $(TARGET) *.o $(TEST_WAIT_BIN) $(TEST_LIMITE_BIN) $(TEST_ATRASADO_BIN) $(TEST_VAZIO_BIN)

.PHONY: all clean test-wait test-limite test-atrasado test-vazio
# vcrc — Sincronização do Metrô

Implementação das funções de sincronização de embarque de passageiros em vagões de metrô (`station_init`, `station_wait_for_car`, `station_load_car`, `station_on_board`), usando `pthread_mutex` e `pthread_cond`, sem semáforos e sem busy-wait.

## Arquivos

- `sync_car.h` — declaração da `struct station` e das assinaturas das 4 funções.
- `sync_car.c` — implementação da sincronização (único arquivo produzido para o enunciado).
- `sync_car-runner.c` — arquivo de teste fornecido pelo professor (não alterado).
- `Makefile` — compilação e limpeza.
- `evidencias.log` — log de terminal gerado com `script -a`, entregue dentro do `.tar`.

## Como compilar

```bash
make
```

Gera o executável `sync_car` (vincula `sync_car.c` + `sync_car-runner.c`).

## Como executar

```bash
./sync_car
```

Roda o teste oficial do professor: cria 100 passageiros e vários carros com número aleatório de assentos, verificando que todos embarcam corretamente e sem deadlock. Imprime `Looks good!` ao final se tudo passar.

## Limpeza

```bash
make clean
```

Remove o executável `sync_car`.

## Sistema operacional utilizado

Implementado e testado em **WSL (Windows Subsystem for Linux) — Ubuntu**, via VSCode.
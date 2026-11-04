#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "sync_car.h"

void *passenger(void *arg)
{
    struct station *st = (struct station *) arg;
    station_wait_for_car(st);
    station_on_board(st);
    return NULL;
}

void *late_passenger(void *arg)
{
    struct station *st = (struct station *) arg;
    sleep(1); /* chega depois que o primeiro carro já partiu */
    printf("atrasado: chamando station_wait_for_car...\n");
    station_wait_for_car(st);
    printf("atrasado: embarcou, confirmando...\n");
    station_on_board(st);
    return NULL;
}

int main(void)
{
    struct station st;
    station_init(&st);

    pthread_t p1, p2, late;
    pthread_create(&p1, NULL, passenger, &st);
    pthread_create(&p2, NULL, passenger, &st);
    pthread_create(&late, NULL, late_passenger, &st);

    printf("main: 1o carro chega com 2 assentos (so os 2 primeiros devem embarcar)\n");
    station_load_car(&st, 2);
    printf("main: 1o carro partiu. waiting=%d (deve ser 1, o atrasado ainda nao chegou)\n", st.waiting);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    sleep(2); /* garante que o atrasado ja esta esperando antes do 2o carro */

    printf("main: 2o carro chega com 1 assento, para pegar o atrasado\n");
    station_load_car(&st, 1);
    printf("main: 2o carro partiu\n");

    pthread_join(late, NULL);

    printf("main: fim. free_seats=%d waiting=%d to_board=%d\n",
           st.free_seats, st.waiting, st.to_board);
    return 0;
}
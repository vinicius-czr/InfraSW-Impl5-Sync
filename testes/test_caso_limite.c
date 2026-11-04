#include <stdio.h>
#include <pthread.h>
#include "sync_car.h"

void *passenger(void *arg)
{
    struct station *st = (struct station *) arg;
    station_wait_for_car(st);
    printf("passageiro: embarcou, confirmando...\n");
    station_on_board(st);
    return NULL;
}

int main(void)
{
    struct station st;
    station_init(&st);

    pthread_t tid;
    pthread_create(&tid, NULL, passenger, &st);

    printf("main: chamando station_load_car com 1 assento...\n");
    station_load_car(&st, 1);
    printf("main: station_load_car retornou\n");

    pthread_join(tid, NULL);

    printf("main: fim. free_seats=%d waiting=%d to_board=%d\n",
           st.free_seats, st.waiting, st.to_board);
    return 0;
}
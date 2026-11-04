#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "sync_car.h"

void *passenger(void *arg)
{
    struct station *st = (struct station *) arg;
    station_wait_for_car(st);
    station_on_board(st);
    return NULL;
}

int main(void)
{
    struct station st;
    station_init(&st);

    pthread_t p1, p2;
    pthread_create(&p1, NULL, passenger, &st);
    pthread_create(&p2, NULL, passenger, &st);

    int w;
    do {
        pthread_mutex_lock(&st.lock);
        w = st.waiting;
        pthread_mutex_unlock(&st.lock);
        if (w < 2) usleep(1000);
    } while (w < 2);

    printf("main: as 2 threads ja estao esperando (waiting=%d). chamando station_load_car com 0 assentos\n", w);
    station_load_car(&st, 0);
    printf("main: station_load_car(0) retornou imediatamente. waiting=%d\n", st.waiting);

    printf("main: agora chamando station_load_car com 2 assentos, pra liberar os 2 que esperavam\n");
    station_load_car(&st, 2);
    printf("main: 2o carro partiu\n");

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("main: fim. free_seats=%d waiting=%d to_board=%d\n",
           st.free_seats, st.waiting, st.to_board);
    return 0;
}
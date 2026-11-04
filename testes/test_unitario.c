#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "sync_car.h"

void *passenger(void *arg)
{
    struct station *st = (struct station *) arg;
    printf("passageiro: chamando station_wait_for_car...\n");
    station_wait_for_car(st);
    printf("passageiro: station_wait_for_car retornou (assento reservado)\n");
    return NULL;
}

int main(void)
{
    struct station st;
    station_init(&st);

    pthread_t tid;
    pthread_create(&tid, NULL, passenger, &st);

    sleep(1);
    printf("main: 1s se passou, nenhum carro ainda -- passageiro deve seguir bloqueado\n");

    pthread_mutex_lock(&st.lock);
    st.car_present = 1;
    st.free_seats = 1;
    pthread_cond_broadcast(&st.cond);
    pthread_mutex_unlock(&st.lock);

    printf("main: carro 'chegou' com 1 assento, aguardando passageiro desbloquear...\n");
    pthread_join(tid, NULL);

    printf("main: fim do teste. free_seats=%d waiting=%d to_board=%d\n",
           st.free_seats, st.waiting, st.to_board);
    return 0;
}
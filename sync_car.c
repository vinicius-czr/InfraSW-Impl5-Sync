#include "sync_car.h"

void station_init(struct station *station)
{
    pthread_mutex_init(&station->lock, NULL);
    pthread_cond_init(&station->cond, NULL);

    station->car_present = 0;
    station->free_seats = 0;
    station->waiting = 0;
    station->to_board = 0;
}

void station_load_car(struct station *station, int count)
{
    (void) station;
    (void) count;
}

void station_wait_for_car(struct station *station)
{
    pthread_mutex_lock(&station->lock);

    station->waiting++;
    while (!(station->car_present && station->free_seats > 0)) {
        pthread_cond_wait(&station->cond, &station->lock);
    }
    station->waiting--;
    station->free_seats--;
    station->to_board++;

    pthread_cond_broadcast(&station->cond);
    pthread_mutex_unlock(&station->lock);
}

void station_on_board(struct station *station)
{
    (void) station;
}
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
    (void) station;
}

void station_on_board(struct station *station)
{
    (void) station;
}
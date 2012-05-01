#include "atomic_station.h"

namespace Model {

AtomicStation::AtomicStation(int bogieId, Real rockAmount)
    :Station(bogieId, rockAmount)
{
    omp_init_lock(&rockLock);
}

void AtomicStation::incrementRockAmount() {
    //omp_set_lock(&rockLock);
    #pragma omp atomic
    rockAmount++;
    //omp_unset_lock(&rockLock);
}

void AtomicStation::decrementRockAmount() {
    //omp_set_lock(&rockLock);
    #pragma omp atomic
    rockAmount--;
    //omp_unset_lock(&rockLock);
}

AtomicStation::~AtomicStation() {
    omp_destroy_lock(&rockLock);
}

}    // namespace

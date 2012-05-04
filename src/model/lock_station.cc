#include "lock_station.h"

namespace Model {

int LockStation::idPool = 0;

LockStation::LockStation(int bogieId, Real rockAmount)
    :Station(bogieId, rockAmount)
{
    omp_init_lock(&stationLock);

    id = idPool;
    idPool++;
}

int LockStation::getId() {
    return id;
}

LockStation::~LockStation() {
    omp_destroy_lock(&stationLock);
}

} /* namespace Model */

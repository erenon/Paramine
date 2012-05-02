#include "lock_station.h"

namespace Model {

LockStation::LockStation(int bogieId, Real rockAmount)
    :Station(bogieId, rockAmount)
{
    omp_init_lock(&stationLock);
}

LockStation::~LockStation() {
    omp_destroy_lock(&stationLock);
}

} /* namespace Model */

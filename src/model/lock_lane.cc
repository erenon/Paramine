#include "lock_lane.h"

#include <cmath>
#include <omp.h>

namespace Model {

LockLane::LockLane(LockStation& stationLower, LockStation& stationUpper, IDirectionFactory& directionFactory)
    :Lane(stationLower, stationUpper, directionFactory)
{
    omp_init_lock(&laneLock);
}

void LockLane::transport() {
    int threadId = omp_get_thread_num();
    bool direction = this->directionFactory.getThreadsafeDirection(threadId);
    Station& source_tmp = (direction) ? this->stationLower : this->stationUpper;
    Station& target_tmp = (direction) ? this->stationUpper : this->stationLower;

    LockStation& source = dynamic_cast<LockStation&>(source_tmp);
    LockStation& target = dynamic_cast<LockStation&>(target_tmp);

    // calculate power consuming
    Real powerConsumption = log(sqrt(source.getRockAmount() / 2));
    this->consumedPower += powerConsumption;

    bool lockSourceFirst = source.getId() < target.getId();
    LockStation& firstToLock = (lockSourceFirst) ? source : target;
    LockStation& secondToLock = (lockSourceFirst) ? target : source;

    //omp_set_lock(&laneLock);
    omp_set_lock(&firstToLock.stationLock);
    omp_set_lock(&secondToLock.stationLock);

    // transport rock amount
    source.decrementRockAmount();
    target.incrementRockAmount();

    // switch bogies
    int tmpBogieId = source.getBogieId();
    source.setBogieId(target.getBogieId());
    target.setBogieId(tmpBogieId);

    omp_unset_lock(&secondToLock.stationLock);
    omp_unset_lock(&firstToLock.stationLock);
    //omp_unset_lock(&laneLock);
}

LockLane::~LockLane() {
    omp_destroy_lock(&laneLock);
}

}   // namespace

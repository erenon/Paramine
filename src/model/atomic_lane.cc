#include "atomic_lane.h"

#include <cmath>
#include <omp.h>

namespace Model {

AtomicLane::AtomicLane(Station& stationLower, Station& stationUpper, IDirectionFactory& directionFactory)
    :Lane(stationLower, stationUpper, directionFactory)
{}

void AtomicLane::transport() {
    int threadId = omp_get_thread_num();
    bool direction = this->directionFactory.getThreadsafeDirection(threadId);
    Station& source = (direction) ? this->stationLower : this->stationUpper;
    Station& target = (direction) ? this->stationUpper : this->stationLower;

    // calculate power consuming
    Real powerConsumption = log(sqrt(source.getRockAmount() / 2));
    this->consumedPower += powerConsumption;


    // transport rock amount
    // atomic calls below:
    source.decrementRockAmount();
    target.incrementRockAmount();

    // switch bogies
    int tmpBogieId = source.getBogieId();
    source.setBogieId(target.getBogieId());
    target.setBogieId(tmpBogieId);
}

}

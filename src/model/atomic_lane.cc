#include "atomic_lane.h"

#include <cmath>

namespace Model {

AtomicLane::AtomicLane(Station& stationLower, Station& stationUpper, IDirectionFactory& directionFactory)
    :Lane(stationLower, stationUpper, directionFactory)
{}

void AtomicLane::transport() {
    bool direction = this->directionFactory.getDirection();
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

#include "lane.h"

#include <cmath>

namespace Model {

Lane::Lane(Station& stationLower, Station& stationUpper, IDirectionFactory& directionFactory)
    :stationLower(stationLower),
     stationUpper(stationUpper),
     directionFactory(directionFactory)
{
    this->consumedPower = 0;
}

Real Lane::getConsumedPower() {
    return this->consumedPower;
}

void Lane::transport() {
    bool direction = this->directionFactory.getDirection();
    Station& source = (direction) ? this->stationLower : this->stationUpper;
    Station& target = (direction) ? this->stationUpper : this->stationLower;

    // calculate power consuming
    Real powerConsumption = log(sqrt(source.getRockAmount() / 2));
    this->consumedPower += powerConsumption;

    // transport rock amount
    source.decrementRockAmount();
    target.incrementRockAmount();

    // switch bogies
    int tmpBogieId = source.getBogieId();
    source.setBogieId(target.getBogieId());
    target.setBogieId(tmpBogieId);
}

}   // namespace

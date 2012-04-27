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

    // calculate rock amount to transport
    // TODO use more complicated calculation here
    Real transportedAmount = log(sqrt(source.getRockAmount() / 2));

    // transport rock amount
    source.setRockAmount(
        source.getRockAmount() - transportedAmount
    );

    target.setRockAmount(
        target.getRockAmount() + transportedAmount
    );

    // switch bogies
    int tmpBogieId = source.getBogieId();
    source.setBogieId(target.getBogieId());
    target.setBogieId(tmpBogieId);

    // calculate power consuming
    this->consumedPower += transportedAmount;
}

}   // namespace

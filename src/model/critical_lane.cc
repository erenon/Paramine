#include "critical_lane.h"

#include <cmath>

namespace Model {

CriticalLane::CriticalLane(Station& stationLower, Station& stationUpper, IDirectionFactory& directionFactory)
    :Lane(stationLower, stationUpper, directionFactory)
{
}

void CriticalLane::transport() {
    bool direction = this->directionFactory.getDirection();
    Station& source = (direction) ? this->stationLower : this->stationUpper;
    Station& target = (direction) ? this->stationUpper : this->stationLower;

    // calculate power consuming
    Real powerConsumption = log(sqrt(source.getRockAmount() / 2));
    this->consumedPower += powerConsumption;

    #pragma omp critical
    {
        // transport rock amount
        source.setRockAmount(
            source.getRockAmount() - 1
        );

        target.setRockAmount(
            target.getRockAmount() + 1
        );

        // switch bogies
        int tmpBogieId = source.getBogieId();
        source.setBogieId(target.getBogieId());
        target.setBogieId(tmpBogieId);
    }
}

}

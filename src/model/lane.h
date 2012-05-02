#ifndef SRC_MODEL_LANE_H_
#define SRC_MODEL_LANE_H_

#include "constants.h"
#include "station.h"
#include "direction_factory/idirection_factory.h"

namespace Model {

using ::Model::DirectionFactory::IDirectionFactory;

class Lane {
protected:
    Real consumedPower;
    Station& stationLower;
    Station& stationUpper;
    IDirectionFactory& directionFactory;

public:
    Lane(Station& stationLower, Station& stationUpper, IDirectionFactory& directionFactory);
    Real getConsumedPower();
    void transport();
    virtual ~Lane() {}
};

}   // namespace

#endif /* SRC_MODEL_LANE_H_ */

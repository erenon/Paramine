#ifndef SRC_MODEL_LOCK_LANE_H_
#define SRC_MODEL_LOCK_LANE_H_

#include "lane.h"
#include "station.h"
#include "lock_station.h"
#include "direction_factory/idirection_factory.h"

namespace Model {

using ::Model::Lane;
using ::Model::Station;
using ::Model::LockStation;
using ::Model::DirectionFactory::IDirectionFactory;

class LockLane :public Lane {
public:
    omp_lock_t laneLock;

    LockLane(LockStation& stationLower, LockStation& stationUpper, IDirectionFactory& directionFactory);
    void transport();
    ~LockLane();
};

}


#endif /* SRC_MODEL_LOCK_LANE_H_ */

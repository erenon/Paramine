#ifndef SRC_MODEL_ATOMIC_LANE_H_
#define SRC_MODEL_ATOMIC_LANE_H_

#include "lane.h"

namespace Model {

using ::Model::Lane;

class AtomicLane :public Lane {
public:
    AtomicLane(Station& stationLower, Station& stationUpper, IDirectionFactory& directionFactory);
    void transport();
};

}


#endif /* SRC_MODEL_ATOMIC_LANE_H_ */

#ifndef SRC_MODEL_CRITICAL_LANE_H_
#define SRC_MODEL_CRITICAL_LANE_H_

#include "lane.h"

namespace Model {

using ::Model::Lane;

class CriticalLane :public Lane {
public:
    CriticalLane(Station& stationLower, Station& stationUpper, IDirectionFactory& directionFactory);
    void transport();
};

}


#endif /* SRC_MODEL_CRITICAL_LANE_H_ */

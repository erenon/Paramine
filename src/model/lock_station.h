#ifndef SRC_MODEL_LOCK_STATION_H_
#define SRC_MODEL_LOCK_STATION_H_

#include "station.h"

#include <omp.h>

namespace Model {

using ::Model::Station;

class LockStation :public Station {
public:
    omp_lock_t stationLock;

    LockStation(int bogieId, Real rockAmount);
    virtual ~LockStation();
};

}    // namespace


#endif /* SRC_MODEL_LOCK_STATION_H_ */

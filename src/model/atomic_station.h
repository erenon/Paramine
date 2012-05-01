#ifndef SRC_MODEL_ATOMIC_STATION_H_
#define SRC_MODEL_ATOMIC_STATION_H_

#include "station.h"

#include <omp.h>

namespace Model {

using ::Model::Station;

class AtomicStation :public Station {
private:
    omp_lock_t rockLock;
public:
    AtomicStation(int bogieId, Real rockAmount);

    void incrementRockAmount();
    void decrementRockAmount();

    ~AtomicStation();
};

}    // namespace


#endif /* SRC_MODEL_ATOMIC_STATION_H_ */

#ifndef SRC_MODEL_ATOMIC_STATION_H_
#define SRC_MODEL_ATOMIC_STATION_H_

#include "station.h"

namespace Model {

using ::Model::Station;

class AtomicStation :public Station {
public:
    AtomicStation(int bogieId, Real rockAmount);

    void incrementRockAmount();
    void decrementRockAmount();
};

}    // namespace


#endif /* SRC_MODEL_ATOMIC_STATION_H_ */

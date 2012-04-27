#ifndef SRC_MODEL_STATION_H_
#define SRC_MODEL_STATION_H_

#include "constants.h"

namespace Model {

class Station {

private:
    int bogieId;
    Real rockAmount;

public:
    Station(int bogieId, Real rockAmount);

    int getBogieId() const;
    void setBogieId(int bogieId);

    Real getRockAmount() const;
    void setRockAmount(Real rockAmount);
};

}    // namespace


#endif /* SRC_MODEL_STATION_H_ */

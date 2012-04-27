#ifndef SRC_MODEL_MINE_H_
#define SRC_MODEL_MINE_H_

#include <stdexcept>

#include "constants.h"
#include "direction_factory/idirection_factory.h"

using Model::DirectionFactory::IDirectionFactory;

namespace Model {

template <typename tStation, typename tLane>
class Mine {
private:
    int stationCount;
    int laneCount;

    tStation** stations;
    tLane** lanes;

public:
    Mine(int stationCount, int laneCount, Real rockAmount, IDirectionFactory& directionFactory)
        :stationCount(stationCount),
         laneCount(laneCount)
    {
        // pointer array
        this->stations = new tStation*[this->stationCount];
        this->lanes = new tLane*[this->laneCount];

        // elements
        for (int i = 0; i < this->stationCount; i++) {
            this->stations[i] = new tStation(i, rockAmount);
        }

        for (int i = 0; i < this->laneCount; i++) {
            this->lanes[i] = new tLane(
                *(this->stations[i]),
                *(this->stations[(i+1) % this->stationCount]),
                directionFactory
            );
        }
    }

    int getStationCount() {
        return this->stationCount;
    }

    int getLaneCount() {
        return this->laneCount;
    }

    tStation& getStationAt(int index) {
        if (0 <= index && index < this->stationCount) {
            return *(this->stations[index]);
        } else {
            throw new std::out_of_range("Station index is out of range");
        }
    }

    tLane& getLaneAt(int index) {
        if (0 <= index && index < this->laneCount) {
            return *(this->lanes[index]);
        } else {
            throw new std::out_of_range("Lane index is out of range");
        }
    }

    ~Mine() {
        // stations and lanes
        for (int i = 0; i < this->stationCount; i++) {
            delete this->stations[i];
        }

        for (int i = 0; i < this->laneCount; i++) {
            delete this->lanes[i];
        }

        delete[] this->stations;
        delete[] this->lanes;
    }
};

}   // namespace


#endif /* SRC_MODEL_MINE_H_ */

#include "station.h"

namespace Model {

Station::Station(int bogieId, Real rockAmount)
    :bogieId(bogieId), rockAmount(rockAmount)
{}

int Station::getBogieId() const {
    return bogieId;
}

void Station::setBogieId(int bogieId) {
    this->bogieId = bogieId;
}

Real Station::getRockAmount() const {
    return rockAmount;
}

void Station::setRockAmount(Real rockAmount) {
    this->rockAmount = rockAmount;
}

void Station::incrementRockAmount() {
    this->rockAmount++;
}

void Station::decrementRockAmount() {
    this->rockAmount--;
}

}    // namespace

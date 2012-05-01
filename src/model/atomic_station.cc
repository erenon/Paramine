#include "atomic_station.h"

#include <omp.h>

namespace Model {

AtomicStation::AtomicStation(int bogieId, Real rockAmount)
    :Station(bogieId, rockAmount)
{}

void AtomicStation::incrementRockAmount() {
    #pragma omp atomic
    this->rockAmount++;
}

void AtomicStation::decrementRockAmount() {
    #pragma omp atomic
    this->rockAmount--;
}

}    // namespace

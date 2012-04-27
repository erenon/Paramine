#include "solution_result.h"

#include <cstdio>
#include <stdexcept>

namespace Model {

SolutionResult::SolutionResult(int stationCount, int laneCount)
    :stationCount(stationCount),
     laneCount(laneCount),
     computingStarted(-1),
     computingStopped(-1)
{
    this->bogieIds = new int[stationCount];
    this->rockAmounts = new Real[stationCount];

    this->consumedPowers = new Real[laneCount];
}

void SolutionResult::startComputing() {
    this->computingStarted = clock();
}

void SolutionResult::stopComputing() {
    this->computingStopped = clock();
}

double SolutionResult::getComputingTime() {
    if (this->computingStarted != -1 && this->computingStopped != -1) {
        return (this->computingStopped - this->computingStarted) / CLOCKS_PER_SEC;
    } else {
        return -1;
    }
}

void SolutionResult::setStationResultAt(int index, int bogieId, Real rockAmount) {
    if (0 <= index && index < this->stationCount) {
        this->bogieIds[index] = bogieId;
        this->rockAmounts[index] = rockAmount;
    } else {
        throw new std::out_of_range("Station index is out of range");
    }
}

void SolutionResult::setLaneResultAt(int index, Real consumedPower) {
    if (0 <= index && index < this->laneCount) {
        this->consumedPowers[index] = consumedPower;
    } else {
        throw new std::out_of_range("Lane index is out of range");
    }
}

bool SolutionResult::equalsTo(SolutionResult& compared) {
    if (this->stationCount == compared.stationCount
    &&  this->laneCount == compared.laneCount) {

        // check stations
        for (int i = 0; i < this->stationCount; i++) {
            if (this->bogieIds[i] != compared.bogieIds[i]
            ||  this->rockAmounts[i] != compared.rockAmounts[i]) {
                // different stations
                return false;
            }
        }

        // check lanes
        for (int i = 0; i < this->laneCount; i++) {
            if (this->consumedPowers[i] != compared.consumedPowers[i]) {
                // different lanes
                return false;
            }
        }

    } else {
        // different dimensions
        return false;
    }

    return true;
}

void SolutionResult::print() {
    double timeConsumed = this->getComputingTime();
    if (timeConsumed >= 0) {
        printf("Time consumed: %f\n", timeConsumed);
    } else {
        printf("No time information found\n");
    }

    printf("Stations:\n");
    for (int i = 0; i < this->stationCount; i++) {
        printf("#%d: {bogie: %d, rock: %f}\n", i, this->bogieIds[i], this->rockAmounts[i]);
    }

    printf("\nLanes:\n");
    for (int i = 0; i < this->laneCount; i++) {
        printf("#%d: {consume: %f}\n", i, this->consumedPowers[i]);
    }
}

SolutionResult::~SolutionResult() {
    delete[] this->bogieIds;
    delete[] this->rockAmounts;

    delete[] this->consumedPowers;
}

}   // namespace

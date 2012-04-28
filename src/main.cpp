/*
 * main.cpp
 *
 *  Created on: 2012.02.27.
 *      Author: erenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "model/constants.h"
#include "model/mine.hpp"
#include "model/station.h"
#include "model/lane.h"
#include "model/criticalLane.h"
#include "model/direction_factory/always_up.h"
#include "model/solution_result.h"

using Model::Mine;
using Model::Station;
using Model::Lane;
using Model::CriticalLane;
using Model::SolutionResult;

using Model::DirectionFactory::AlwaysUp;

SolutionResult solutionTrivial() {
    AlwaysUp directionFactory;
    Mine<Station, Lane> mine(STATION_COUNT, LANE_COUNT, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, LANE_COUNT);

    result.startComputing();

    for (int i = 0; i < BOGIE_SWITCH_COUNT; i++) {
        mine.getLaneAt(i%LANE_COUNT).transport();
    }

    result.stopComputing();

    for (int i = 0; i < STATION_COUNT; i++) {
        result.setStationResultAt(
            i,
            mine.getStationAt(i).getBogieId(),
            mine.getStationAt(i).getRockAmount()
        );
    }

    for (int i = 0; i < LANE_COUNT; i++) {
        result.setLaneResultAt(
            i,
            mine.getLaneAt(i).getConsumedPower()
        );
    }

    return result;
}

SolutionResult solutionTrivialParallel() {
    AlwaysUp directionFactory;
    Mine<Station, Lane> mine(STATION_COUNT, LANE_COUNT, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, LANE_COUNT);

    result.startComputing();

    int i;
    #pragma omp parallel for default(none) shared(mine) private(i)
    for (i = 0; i < BOGIE_SWITCH_COUNT; i++) {
        mine.getLaneAt(i%LANE_COUNT).transport();
    }

    result.stopComputing();

    for (int i = 0; i < STATION_COUNT; i++) {
        result.setStationResultAt(
            i,
            mine.getStationAt(i).getBogieId(),
            mine.getStationAt(i).getRockAmount()
        );
    }

    for (int i = 0; i < LANE_COUNT; i++) {
        result.setLaneResultAt(
            i,
            mine.getLaneAt(i).getConsumedPower()
        );
    }

    return result;
}

SolutionResult solutionCriticalParallel() {
    AlwaysUp directionFactory;
    Mine<Station, CriticalLane> mine(STATION_COUNT, LANE_COUNT, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, LANE_COUNT);

    result.startComputing();

    int i;
    #pragma omp parallel for default(none) shared(mine) private(i)
    for (i = 0; i < BOGIE_SWITCH_COUNT; i++) {
        mine.getLaneAt(i%LANE_COUNT).transport();
    }

    result.stopComputing();

    for (int i = 0; i < STATION_COUNT; i++) {
        result.setStationResultAt(
            i,
            mine.getStationAt(i).getBogieId(),
            mine.getStationAt(i).getRockAmount()
        );
    }

    for (int i = 0; i < LANE_COUNT; i++) {
        result.setLaneResultAt(
            i,
            mine.getLaneAt(i).getConsumedPower()
        );
    }

    return result;
}

SolutionResult solutionCriticalParallelCircular() {
    AlwaysUp directionFactory;
    int laneCount = LANE_COUNT + 1; // circular topology
    Mine<Station, CriticalLane> mine(STATION_COUNT, laneCount, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, laneCount);

    result.startComputing();

    int i;
    #pragma omp parallel for default(none) shared(mine, laneCount) private(i)
    for (i = 0; i < BOGIE_SWITCH_COUNT; i++) {
        mine.getLaneAt(i%laneCount).transport();
    }

    result.stopComputing();

    for (int i = 0; i < STATION_COUNT; i++) {
        result.setStationResultAt(
            i,
            mine.getStationAt(i).getBogieId(),
            mine.getStationAt(i).getRockAmount()
        );
    }

    for (int i = 0; i < laneCount; i++) {
        result.setLaneResultAt(
            i,
            mine.getLaneAt(i).getConsumedPower()
        );
    }

    return result;
}

void runSolution(SolutionResult(*solution)()) {
    SolutionResult result = solution();
    if (result.isValid()) {
        printf("[PASSED] ");
    } else {
        printf("[FAILED] ");
        fprintf(stdout, "%s\n", result.getValidationError().c_str());
    }
    printf("time: %f sec\n", result.getComputingTime());
}

int main(void) {
    printf("Trivial Solution:\n");
    runSolution(solutionTrivial);
    printf("Trivial Parallel Solution:\n");
    runSolution(solutionTrivialParallel);
    printf("Parallel Solution with critical section:\n");
    runSolution(solutionCriticalParallel);
    printf("Parallel Solution with critical section and circular mine:\n");
    runSolution(solutionCriticalParallelCircular);

	return EXIT_SUCCESS;
}



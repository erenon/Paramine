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
#include "model/atomic_station.h"
#include "model/atomic_lane.h"
#include "model/critical_lane.h"
#include "model/lock_station.h"
#include "model/lock_lane.h"
#include "model/direction_factory/always_up.h"
#include "model/solution_result.h"

using Model::Mine;
using Model::Station;
using Model::Lane;
using Model::AtomicStation;
using Model::AtomicLane;
using Model::CriticalLane;
using Model::LockStation;
using Model::LockLane;
using Model::SolutionResult;

using Model::DirectionFactory::AlwaysUp;

SolutionResult solutionTrivial() {
    DirFac directionFactory;
    Mine<Station, Lane> mine(STATION_COUNT, LANE_COUNT, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, LANE_COUNT);

    result.startComputing();

    for (int i = 0; i < TOTAL_SWITCH_COUNT; i++) {
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
    DirFac directionFactory;
    Mine<Station, Lane> mine(STATION_COUNT, LANE_COUNT, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, LANE_COUNT);

    result.startComputing();

    int i;
    #pragma omp parallel for default(none) shared(mine) private(i)
    for (i = 0; i < TOTAL_SWITCH_COUNT; i++) {
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

SolutionResult solutionAtomicParallel() {
    DirFac directionFactory;
    Mine<AtomicStation, AtomicLane> mine(STATION_COUNT, LANE_COUNT, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, LANE_COUNT);

    result.startComputing();

    int i;
    #pragma omp parallel for default(none) shared(mine) private(i)
    for (i = 0; i < TOTAL_SWITCH_COUNT; i++) {
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
    DirFac directionFactory;
    Mine<Station, CriticalLane> mine(STATION_COUNT, LANE_COUNT, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, LANE_COUNT);

    result.startComputing();

    int i;
    #pragma omp parallel for default(none) shared(mine) private(i)
    for (i = 0; i < TOTAL_SWITCH_COUNT; i++) {
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
    DirFac directionFactory;
    int laneCount = LANE_COUNT + 1; // circular topology
    Mine<Station, CriticalLane> mine(STATION_COUNT, laneCount, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, laneCount);

    result.startComputing();

    int i;
    #pragma omp parallel for default(none) shared(mine, laneCount) private(i)
    for (i = 0; i < TOTAL_SWITCH_COUNT; i++) {
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

SolutionResult solutionLockParallel() {
    DirFac directionFactory;
    Mine<LockStation, LockLane> mine(STATION_COUNT, LANE_COUNT, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, LANE_COUNT);

    result.startComputing();

    int i;
    #pragma omp parallel for default(none) shared(mine) private(i)
    for (i = 0; i < TOTAL_SWITCH_COUNT; i++) {
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

SolutionResult solutionLockParallelCircular() {
    DirFac directionFactory;
    int laneCount = LANE_COUNT + 1; // circular topology
    Mine<LockStation, LockLane> mine(STATION_COUNT, laneCount, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, laneCount);

    result.startComputing();

    int i;
    #pragma omp parallel for default(none) shared(mine, laneCount) private(i)
    for (i = 0; i < TOTAL_SWITCH_COUNT; i++) {
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


SolutionResult solutionCombParallel() {
    DirFac directionFactory;
    Mine<Station, Lane> mine(STATION_COUNT, LANE_COUNT, ROCK_AMOUNT, directionFactory);
    SolutionResult result(STATION_COUNT, LANE_COUNT);

    result.startComputing();

    int i, j;
    int threadId;
    int jumpDelta;
    #pragma omp parallel shared(mine, jumpDelta) private(i, j, threadId)
    {
        threadId = omp_get_thread_num();
        jumpDelta = omp_get_num_threads() * 2;
        for (i = threadId * 2; i < LANE_COUNT; i += jumpDelta) {
            for (j = 0; j < BOGIE_SWITCH_COUNT; j++) {
                mine.getLaneAt(i).transport();
            }
        }

        #pragma omp barrier
        for (i = threadId * 2 + 1; i < LANE_COUNT; i += jumpDelta) {
            for (j = 0; j < BOGIE_SWITCH_COUNT; j++) {
                mine.getLaneAt(i).transport();
            }
        }
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

void runSolution(SolutionResult(*solution)()) {
    SolutionResult result = solution();
    if (result.isValid()) {
        printf("[PASSED]\n");
    } else {
        printf("[FAILED] ");
        fprintf(stdout, "%s\n", result.getValidationError().c_str());
    }
    printf("time: %f sec\n\n", result.getComputingTime());

    result.print();
}

int main(void) {
    printf("Trivial Solution:\n");
    runSolution(solutionTrivial);

    printf("\n+-----------------------------+\n");
    printf("Trivial Parallel Solution:\n");
    runSolution(solutionTrivialParallel);

    printf("\n+-----------------------------+\n");
    printf("Atomic Parallel Solution:\n");
    runSolution(solutionAtomicParallel);

    printf("\n+-----------------------------+\n");
    printf("Parallel Solution with critical section:\n");
    runSolution(solutionCriticalParallel);

    printf("\n+-----------------------------+\n");
    printf("Parallel Solution with critical section and circular mine:\n");
    runSolution(solutionCriticalParallelCircular);

    printf("\n+-----------------------------+\n");
    printf("Parallel Solution with lockable stations:\n");
    runSolution(solutionLockParallel);

    printf("\n+-----------------------------+\n");
    printf("Parallel Solution with lockable stations and circular mine:\n");
    runSolution(solutionLockParallelCircular);

    printf("\n+-----------------------------+\n");
    printf("Parallel Comb Solution:\n");
    runSolution(solutionCombParallel);

	return EXIT_SUCCESS;
}



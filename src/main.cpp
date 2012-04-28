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
#include "model/direction_factory/always_up.h"
#include "model/solution_result.h"

using Model::Mine;
using Model::Station;
using Model::Lane;
using Model::SolutionResult;

using Model::DirectionFactory::AlwaysUp;

#define STATION_COUNT 5
#define LANE_COUNT 4
#define BOGIE_SWITCH_COUNT 50000000
#define ROCK_AMOUNT 500000000

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

int main(void) {
	SolutionResult trivialResult = solutionTrivial();
	printf("[REFERENCE] trivial time: %f sec\n", trivialResult.getComputingTime());
	//trivialResult.print();

	SolutionResult trivialParallelResult = solutionTrivialParallel();
	if (trivialResult.equalsTo(trivialParallelResult)) {
	    printf("[PASSED] trivial parallel time: %f sec\n", trivialParallelResult.getComputingTime());
	} else {
	    printf("[FAILED] trivial parallel time: %f sec\n", trivialParallelResult.getComputingTime());
	}

	return EXIT_SUCCESS;
}



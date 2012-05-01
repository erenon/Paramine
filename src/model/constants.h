#ifndef SRC_MODEL_CONSTANTS_H_
#define SRC_MODEL_CONSTANTS_H_

#include "direction_factory/always_up.h"
#include "direction_factory/random.h"

using Model::DirectionFactory::AlwaysUp;
using Model::DirectionFactory::Random;

// No more threads allowed
#define MAX_THREAD_COUNT 16

typedef float Real;
//typedef AlwaysUp DirFac;
typedef Random DirFac;

#define STATION_COUNT 5
#define LANE_COUNT 4

#define BOGIE_SWITCH_COUNT 10000000
// Faster execution to ease the testing
//#define BOGIE_SWITCH_COUNT 250000

/*
 * Total count of bogie switches in the mine
 */
#define TOTAL_SWITCH_COUNT (BOGIE_SWITCH_COUNT * LANE_COUNT)

/**
 * Initial rock amount on each station
 */
#define ROCK_AMOUNT (BOGIE_SWITCH_COUNT * 10)

#endif /* SRC_MODEL_CONSTANTS_H_ */

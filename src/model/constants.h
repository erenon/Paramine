#ifndef SRC_MODEL_CONSTANTS_H_
#define SRC_MODEL_CONSTANTS_H_

typedef float Real;

#define STATION_COUNT 5
#define LANE_COUNT 4

/*
 * Total switch count in the mine
 * equals to M * LANE_COUNT
 */
#define BOGIE_SWITCH_COUNT 40000000

/**
 * Initial rock amount on each station
 * equals to M * 10
 */
#define ROCK_AMOUNT 100000000

#endif /* SRC_MODEL_CONSTANTS_H_ */

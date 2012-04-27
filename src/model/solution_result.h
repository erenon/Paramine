#ifndef SRC_MODEL_SOLUTION_RESULT_H_
#define SRC_MODEL_SOLUTION_RESULT_H_

#include <ctime>

#include "constants.h"

namespace Model {

class SolutionResult {
private:
    int stationCount;
    int laneCount;

    // station parameters
    int* bogieIds;
    Real* rockAmounts;

    // lane parameters
    Real* consumedPowers;

    // timer attributes
    clock_t computingStarted;
    clock_t computingStopped;

public:
    SolutionResult(int stationCount, int laneCount);

    void startComputing();
    void stopComputing();
    double getComputingTime();

    void setStationResultAt(int index, int bogieId, Real rockAmount);
    void setLaneResultAt(int index, Real consumedPower);

    bool equalsTo(SolutionResult& compared);

    void print();

    ~SolutionResult();
};

}   // namespace

#endif /* SRC_MODEL_SOLUTION_RESULT_H_ */

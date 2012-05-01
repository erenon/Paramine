#include "random.h"

#include <cstdlib>
#include <ctime>

#include "../constants.h"

namespace Model { namespace DirectionFactory {

Random::Random() {
    srand(time(NULL));

    this->threadState = new unsigned int[MAX_THREAD_COUNT];

    for (int i = 0; i < MAX_THREAD_COUNT; i++) {
        this->threadState[i] = time(NULL) + 5*i;
    }
}

bool Random::getDirection() {
    return rand() % 2;
}

bool Random::getThreadsafeDirection(int threadId) {
    return rand_r(&(this->threadState[threadId])) % 2;
}

Random::~Random() {
    delete[] this->threadState;
}

}}  // namespace

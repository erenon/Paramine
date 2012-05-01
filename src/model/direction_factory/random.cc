#include "random.h"

#include <cstdlib>
#include <ctime>

namespace Model { namespace DirectionFactory {

Random::Random() {
    srand(time(NULL));
}

bool Random::getDirection() {
    return rand() % 2;
}

}}  // namespace

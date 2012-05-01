#include "always_up.h"

namespace Model { namespace DirectionFactory {

bool AlwaysUp::getDirection() {
    return true;
}

bool AlwaysUp::getThreadsafeDirection(int threadId) {
    return true;
}

}}  // namespace

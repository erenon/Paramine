#ifndef SRC_MODEL_DIRECTION_FACTORY_ALWAYS_UP_H_
#define SRC_MODEL_DIRECTION_FACTORY_ALWAYS_UP_H_

#include "idirection_factory.h"

namespace Model { namespace DirectionFactory {

class AlwaysUp :public IDirectionFactory {
public:
    bool getDirection();
    bool getThreadsafeDirection(int threadId);
    virtual ~AlwaysUp() {}
};

}}  // namespace


#endif /* SRC_MODEL_DIRECTION_FACTORY_ALWAYS_UP_H_ */

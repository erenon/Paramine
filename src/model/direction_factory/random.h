#ifndef SRC_MODEL_DIRECTION_FACTORY_RANDOM_H_
#define SRC_MODEL_DIRECTION_FACTORY_RANDOM_H_

#include "idirection_factory.h"

namespace Model { namespace DirectionFactory {

class Random :public IDirectionFactory {
public:
    Random();
    bool getDirection();
    virtual ~Random() {}
};

}}  // namespace


#endif /* SRC_MODEL_DIRECTION_FACTORY_RANDOM_H_ */

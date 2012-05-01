#ifndef SRC_MODEL_DIRECTION_FACTORY_IDIRECTION_FACTORY_H_
#define SRC_MODEL_DIRECTION_FACTORY_IDIRECTION_FACTORY_H_

namespace Model { namespace DirectionFactory {

/**
 * Normally this class should be DirectionFactory,
 * whithout the 'I' prefix, but I've had issues
 * becouse of the same namespace name.
 */
class IDirectionFactory {
public:
    virtual bool getDirection() = 0;
    virtual bool getThreadsafeDirection(int threadId) = 0;
    virtual ~IDirectionFactory() {}
};

}}  // namespace

#endif /* SRC_MODEL_DIRECTION_FACTORY_IDIRECTION_FACTORY_H_ */

#ifndef PRISM_MOCK_RUN_LOOP_H_
#define PRISM_MOCK_RUN_LOOP_H_

#include "prism/eventsystem/RunLoop.h"

template <typename Receiver, typename EventTp>
class EventQueue;

template <typename Receiver, typename EventTp>
class MockRunLoop : public RunLoop<Receiver, EventTp> {
public:
    MockRunLoop(EventQueue<Receiver, EventTp> * postedEventQueue, EventQueue<Receiver, EventTp> * nativeEventQueue)
    :   RunLoop<Receiver, EventTp>(postedEventQueue, nativeEventQueue)
    {}

    virtual const int run() override {
        std::pair<Receiver *, EventTp *> pair = this->m_postedEventQueue->getNextEvent();
        if (pair.second->type == EventTp::Quit)
            this->halt(0);
        else
            this->halt(1);
        return this->m_retCode;
    }
};

#endif // PRISM_MOCK_RUN_LOOP_H_

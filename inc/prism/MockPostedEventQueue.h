#ifndef PRISM_MOCK_EVENT_QUEUE_H_
#define PRISM_MOCK_EVENT_QUEUE_H_

#include "prism/eventsystem/PostedEventQueue.h"
#include "prism/Responder.h"
#include "prism/MockEvent.h"

template <typename Receiver, typename EventTp>
class MockPostedEventQueue : public PostedEventQueue<Receiver, EventTp> {
    std::pair<Receiver *, EventTp *> getNextEvent() override {
        static int id = 1;
        std::pair<Receiver *, EventTp *> epair = PostedEventQueue<Receiver, EventTp>::getNextEvent();
        epair.first->setTimestamp(id++);
        return epair;
    }
};

#endif // PRISM_MOCK_EVENT_QUEUE_H_

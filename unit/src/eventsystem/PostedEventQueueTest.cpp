#include "gtest/gtest.h"
using namespace ::testing;
#include "prism/eventsystem/PostedEventQueue.h"
#include "prism/Responder.h"
#include "prism/MockEvent.h"

class PostedEventQueueTest : public Test {
public:
    PostedEventQueue<Responder, MockEvent> q;
};

TEST_F(PostedEventQueueTest, QueueIsEmptyAtCreation) {
    ASSERT_FALSE(q.hasPendingEvents());
}

TEST_F(PostedEventQueueTest, QueueSizeIncreasesByOneWhenEventAdded) {
    Responder obj;
    MockEvent ev;
    q.addEvent(&obj, &ev);
    ASSERT_TRUE(q.hasPendingEvents());
    ASSERT_EQ(1, q.size());
}

TEST_F(PostedEventQueueTest, CanRetrieveFirstEventFromQueue) {
    Responder obj;
    MockEvent ev;
    q.addEvent(&obj, &ev);
    std::pair<Responder *, MockEvent *> event_pair =  std::make_pair(&obj, &ev);

    ASSERT_TRUE(event_pair == q.getNextEvent());
}

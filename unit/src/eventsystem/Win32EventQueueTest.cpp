#include "gtest/gtest.h"
#include "prism/eventsystem/Win32EventQueue.h"
#include "prism/MockWin32EventQueue.h"
#include "prism/Responder.h"
#include "prism/MockEvent.h"
using namespace ::testing;

class Win32EventQueueTest : public Test {
public:
    Win32EventQueue<Responder, MockEvent> q;
    Responder r;
    MockEvent e;
};

TEST_F(Win32EventQueueTest, QueueIsEmptyAtCreation) {
    ASSERT_FALSE(q.hasPendingEvents());
}

TEST_F(Win32EventQueueTest, QueueSizeIncreasesByOneWhenEventAdded) {
    q.addEvent(&r, &e);

    ASSERT_TRUE(q.hasPendingEvents());
    ASSERT_EQ(1, q.size());
}

TEST_F(Win32EventQueueTest, QueueSizeDecreasesByOneWhenRetrievingNextEvent) {
    q.addEvent(&r, &e);
    q.getNextEvent();

    ASSERT_FALSE(q.hasPendingEvents());
    ASSERT_EQ(0, q.size());
}

TEST_F(Win32EventQueueTest, CanReturnFirstEventInQueue) {
    q.addEvent(&r, &e);

    std::pair<Responder *, MockEvent *> epair = q.getNextEvent();

    ASSERT_TRUE(&r == epair.first);
    ASSERT_TRUE(&e == epair.second);
    ASSERT_FALSE(q.hasPendingEvents());
}

TEST_F(Win32EventQueueTest, CanCheckForAndAddNativeWin32MessagesToQueue) {
    MockWin32EventQueue<Responder, MockEvent> mq;
    mq.refresh();

    ASSERT_TRUE(mq.hasPendingEvents());

    while(mq.hasPendingEvents()) {
        std::pair<Responder *, MockEvent *> pair = mq.getNextEvent();
        ASSERT_TRUE(pair.second->native);
        delete pair.first;
        delete pair.second;
    }
}

#include "gtest/gtest.h"
#include "prism/eventsystem/RunLoop.h"
#include "prism/MockRunLoop.h"
#include "prism/eventsystem/PostedEventQueue.h"
#include "prism/eventsystem/Win32EventQueue.h"
#include "prism/MockPostedEventQueue.h"
#include "prism/MockEvent.h"
#include "prism/Responder.h"
#include <iostream>
using namespace ::testing;

class RunLoopTest : public Test {
public:
    EventQueue<Responder, MockEvent> * postedEventQueue;
    EventQueue<Responder, MockEvent> * mockPostedEventQueue;
    EventQueue<Responder, MockEvent> * nativeEventQueue;
    RunLoop<Responder, MockEvent> loop;
    Responder r1;
    Responder r2;
    Responder r3;
    MockEvent e;

    RunLoopTest()
    :   postedEventQueue{new PostedEventQueue<Responder, MockEvent>},
        mockPostedEventQueue{new MockPostedEventQueue<Responder, MockEvent>},
        nativeEventQueue{new Win32EventQueue<Responder, MockEvent>},
        loop{postedEventQueue, nativeEventQueue}
    {}

    ~RunLoopTest() {
        delete postedEventQueue;
        delete mockPostedEventQueue;
        delete nativeEventQueue;
    }
};

TEST_F(RunLoopTest, IsNotRunningWhenCreated) {
    ASSERT_FALSE(loop.isRunning());
}

TEST_F(RunLoopTest, CanStartLoopRunning) {
    loop.run();
    ASSERT_TRUE(loop.isRunning());
}

TEST_F(RunLoopTest, CanStopLoopRunning) {
    loop.run();
    loop.halt();
    ASSERT_FALSE(loop.isRunning());
}

TEST_F(RunLoopTest, CanNotifyReceiverAboutEvent) {
    postedEventQueue->addEvent(&r1, &e);
    loop.run();

    ASSERT_TRUE(r1.eventReceived());
}

TEST_F(RunLoopTest, ProcessesEachEventInOrderPosted) {
    mockPostedEventQueue->addEvent(&r1, &e);
    mockPostedEventQueue->addEvent(&r2, &e);
    mockPostedEventQueue->addEvent(&r3, &e);

    RunLoop<Responder, MockEvent> loop(mockPostedEventQueue, nativeEventQueue);

    loop.run();

    ASSERT_TRUE(r1.eventReceived());
    ASSERT_TRUE(r2.eventReceived());
    ASSERT_TRUE(r3.eventReceived());
    ASSERT_FALSE(mockPostedEventQueue->hasPendingEvents());

    ASSERT_TRUE(r1.timestamp() < r2.timestamp() && r1.timestamp() < r3.timestamp());
    ASSERT_TRUE(r2.timestamp() > r1.timestamp() && r2.timestamp() < r3.timestamp());
    ASSERT_TRUE(r3.timestamp() > r1.timestamp() && r3.timestamp() > r2.timestamp());
}

TEST_F(RunLoopTest, ReturnsZeroWhenLoopTerminatesSuccessfully) {
    e.type = MockEvent::Quit;
    postedEventQueue->addEvent(&r1, &e);
    RunLoop<Responder, MockEvent> * mloop = new MockRunLoop<Responder, MockEvent>(postedEventQueue, nativeEventQueue);

    int successfulReturnCode = mloop->run();
    ASSERT_EQ(0, successfulReturnCode);
    delete mloop;
}

#ifndef PRISM_MOCK_WIN32_EVENT_QUEUE_H_
#define PRISM_MOCK_WIN32_EVENT_QUEUE_H_

#include "prism/eventsystem/Win32EventQueue.h"
#include "prism/MockEvent.h"
#include "prism/Responder.h"

template <typename Receiver, typename EventTp>
class MockWin32EventQueue : public Win32EventQueue<Receiver, EventTp> {
public:
    virtual void refresh() override {
        // We're pretending that Win32 messages are being collected here i.e. GetMessage()
        // and then are converted into Prism Events which are then added to the queue
        MockEvent * e1, * e2;
        e1 = new MockEvent;
        e2 = new MockEvent;
        e1->type = MockEvent::Resize;
        e2->type = MockEvent::Quit;
        e1->native = true;
        e2->native = true;

        Responder * r1, * r2;
        r1 = new Responder;
        r2 = new Responder;

        this->addEvent(r1, e1);
        this->addEvent(r2, e2);
    }
};

#endif // PRISM_MOCK_WIN32_EVENT_QUEUE_H_

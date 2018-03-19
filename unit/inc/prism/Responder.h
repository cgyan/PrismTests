#ifndef PRISM_RESPONDER_H_
#define PRISM_RESPONDER_H_

#include <ctime>

class MockEvent;

class Responder {
private:
    bool m_eventReceived{false};
    int m_id{0};
public:
    void handleEvent(MockEvent *) {
        m_eventReceived = true;
    }
    const bool eventReceived() { return m_eventReceived; }
    void setTimestamp(const int id) { m_id = id; }
    const int timestamp() const { return m_id; }
};


#endif // PRISM_RESPONDER_H_

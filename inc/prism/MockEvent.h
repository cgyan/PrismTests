#ifndef PRISM_MOCK_EVENT_H_
#define PRISM_MOCK_EVENT_H_

class MockEvent {
public:
    enum { Resize, Quit };
    int type;
    bool native{false};
};

#endif // PRISM_MOCK_EVENT_H_

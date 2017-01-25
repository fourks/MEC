#ifndef MECMSGQUEUE_H
#define MECMSGQUEUE_H

#include <memory>

struct MecMsg {
    enum type {
        TOUCH_ON,
        TOUCH_CONTINUE,
        TOUCH_OFF,
        CONTROL,

    } type_;

    union {
        struct {
            int     touchId_;
            float   note_, x_, y_, z_;
        } touch_;
        struct {
            int     controlId_;
            float   value_;
        } control_;
    } data_;
};

class MecMsgQueue_impl;

class MecMsgQueue {
public:
    MecMsgQueue();
    ~MecMsgQueue();
    bool addToQueue(MecMsg&);
    bool nextMsg(MecMsg&);
    bool isEmpty();
    bool isFull();
    int  available();
    int  pending();

private:
    std::unique_ptr<MecMsgQueue_impl> impl_;
};


#endif// MECMSGQUEUE_H

#pragma once

#include "gooey/gooey.hpp"

namespace gooey {

enum EventType {
    EVT_MOUSEDOWN,
    EVT_MOUSEUP,
    EVT_MOUSEMOVE
};

class Event {

public:
    inline EventType type() { return type_; }



private:
    EventType type_;


};


}
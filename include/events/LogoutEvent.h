//
// Created by jeremy on 2022-03-02.
//

#ifndef PROJECT_LOGOUTEVENT_H
#define PROJECT_LOGOUTEVENT_H

#include "events/Event.h"


/**
 * Signals an attempt to log out of the current active user session.
 */
struct LogoutEvent : public Event {
    LogoutEvent() = default;
};

#endif //PROJECT_LOGOUTEVENT_H

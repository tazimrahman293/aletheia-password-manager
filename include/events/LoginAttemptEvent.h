//
// Created by jeremy on 2022-02-27.
//

#ifndef PROJECT_LOGINATTEMPTEVENT_H
#define PROJECT_LOGINATTEMPTEVENT_H

#include <string>

#include "events/Event.h"

struct LoginAttemptEvent : public Event {

    LoginAttemptEvent(int uid, std::string pass) : uid(uid), password(std::move(pass)) { }

    int uid;
    std::string password;
};


#endif //PROJECT_LOGINATTEMPTEVENT_H

//
// Created by jeremy on 2022-02-27.
//

#ifndef PROJECT_LOGINATTEMPTEVENT_H
#define PROJECT_LOGINATTEMPTEVENT_H

#include <string>

#include "events/Event.h"


/**
 * Signals a login attempt.
 */
struct LoginAttemptEvent : public Event {

    LoginAttemptEvent(int uid, std::string pass) : uid(uid), password(std::move(pass)) { }

    // The primary key of the user attempting to log in
    int uid;

    // The plain text password given for the login attempt
    std::string password;
};


#endif //PROJECT_LOGINATTEMPTEVENT_H

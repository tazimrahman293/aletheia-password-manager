//
// Created by jeremy on 2022-03-02.
//

#ifndef PROJECT_ACCOUNTDELETEEVENT_H
#define PROJECT_ACCOUNTDELETEEVENT_H

#include "events/Event.h"
#include "data/Account.h"


/**
 * Signals the intent to delete an account.
 */
struct AccountDeleteEvent : public Event {
    explicit AccountDeleteEvent(int id) : target(id) { }

    // Primary key of the account to be deleted
    int target;
};

#endif //PROJECT_ACCOUNTDELETEEVENT_H

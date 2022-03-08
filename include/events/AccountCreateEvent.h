//
// Created by jeremy on 2022-02-28.
//

#ifndef PROJECT_ACCOUNTCREATEEVENT_H
#define PROJECT_ACCOUNTCREATEEVENT_H

#include "events/Event.h"
#include "data/Account.h"


/**
 * Signals a request to create a new account.
 */
struct AccountCreateEvent : public Event {

    explicit AccountCreateEvent(Account rec) : record(std::move(rec)) { }

    // The account record to be created in the database
    Account record;
};

#endif //PROJECT_ACCOUNTCREATEEVENT_H

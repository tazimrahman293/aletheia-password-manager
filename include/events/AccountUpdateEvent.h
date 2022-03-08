//
// Created by jeremy on 2022-02-28.
//

#ifndef PROJECT_ACCOUNTUPDATEEVENT_H
#define PROJECT_ACCOUNTUPDATEEVENT_H

#include "events/Event.h"
#include "data/Account.h"


/**
 * Signals a request to update an account.
 */
struct AccountUpdateEvent : public Event {

    explicit AccountUpdateEvent(Account rec) : record(std::move(rec)) { }

    // The account record to be updated in the database
    Account record;

};

#endif //PROJECT_ACCOUNTUPDATEEVENT_H

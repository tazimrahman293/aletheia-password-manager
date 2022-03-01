//
// Created by jeremy on 2022-02-28.
//

#ifndef PROJECT_ACCOUNTCREATEEVENT_H
#define PROJECT_ACCOUNTCREATEEVENT_H

#include "events/Event.h"
#include "data/Account.h"

struct AccountCreateEvent : public Event {

    explicit AccountCreateEvent(Account rec) : record(std::move(rec)) { }

    Account record;
};

#endif //PROJECT_ACCOUNTCREATEEVENT_H

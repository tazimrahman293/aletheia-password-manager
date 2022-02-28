//
// Created by jeremy on 2022-02-28.
//

#ifndef PROJECT_ACCOUNTCREATEEVENT_H
#define PROJECT_ACCOUNTCREATEEVENT_H

#include "events/Event.h"
#include "data/AccountRecord.h"

struct AccountCreateEvent : public Event {

    explicit AccountCreateEvent(AccountRecord rec) : record(std::move(rec)) { }

    AccountRecord record;
};

#endif //PROJECT_ACCOUNTCREATEEVENT_H

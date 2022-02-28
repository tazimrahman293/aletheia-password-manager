//
// Created by jeremy on 2022-02-28.
//

#ifndef PROJECT_ACCOUNTUPDATEEVENT_H
#define PROJECT_ACCOUNTUPDATEEVENT_H

#include "events/Event.h"
#include "data/AccountRecord.h"


struct AccountUpdateEvent : public Event {

    explicit AccountUpdateEvent(AccountRecord rec) : record(std::move(rec)) { }

    AccountRecord record;

};

#endif //PROJECT_ACCOUNTUPDATEEVENT_H

//
// Created by jeremy on 2022-02-07.
//

#ifndef USER_H
#define USER_H

#include <string>
#include <utility>

#include <data/UserRecord.h>

class User {

    UserRecord record;

public:
    // using UserType = UserRecord::UserType;

    explicit User(UserRecord record) : record(std::move(record)) { }
    int ID() const { return record.id; }
    std::string Name() const { return record.firstName + " " + record.lastName; }
};

#endif  // USER_H

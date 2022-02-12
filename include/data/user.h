//
// Created by jeremy on 2022-02-07.
//

#ifndef USER_H
#define USER_H

#include <string>
#include <utility>

#include <data/user-record.h>

namespace data {
    class User {

        data::UserRecord record;

    public:
        // using UserType = db::UserRecord::UserType;

        explicit User(data::UserRecord record) : record(std::move(record)) { }
        int ID() const { return record.id; }
        std::string Name() const { return record.firstName + " " + record.lastName; }
    };
}  // namespace data

#endif  // USER_H

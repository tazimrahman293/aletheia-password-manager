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

        data::UserRecord _record;

    public:
        // using UserType = db::UserRecord::UserType;

        explicit User(data::UserRecord record) : _record(std::move(record)) { }
        [[nodiscard]] std::string Name() const { return _record.firstName + " " + _record.lastName; }
        [[nodiscard]] int ID() const { return _record.id; }
    };
}  // namespace data

#endif  // USER_H

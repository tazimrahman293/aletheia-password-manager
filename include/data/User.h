//
// Created by jeremy on 2022-02-07.
//

#ifndef USER_RECORD_H
#define USER_RECORD_H

#include <string>

#include <json.h>

struct User {
    enum class UserType {
        Normal = 1,
        Admin = 2,
        SuperAdmin = 3
    };

    int pk;
    std::string firstName;
    std::string lastName;
    std::string keyHash;
    UserType typeID;

    User() : pk(-1), typeID(UserType::Normal) { }
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(\
        User,\
        pk,\
        firstName,\
        lastName,\
        keyHash,\
        typeID\
        )

#endif  // USER_RECORD_H

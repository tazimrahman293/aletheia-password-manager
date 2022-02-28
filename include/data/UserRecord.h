//
// Created by jeremy on 2022-02-07.
//

#ifndef USER_RECORD_H
#define USER_RECORD_H

#include <string>

struct UserRecord {
    enum class UserType {
        Normal = 1,
        Admin = 2,
        SuperAdmin = 3
    };

    int id;
    std::string firstName;
    std::string lastName;
    std::string keyHash;
    UserType typeID;
};

#endif  // USER_RECORD_H

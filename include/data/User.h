//
// Created by jeremy on 2022-02-07.
//

#ifndef USER_RECORD_H
#define USER_RECORD_H

#include <string>
#include <vector>

#include <json.h>


/**
 * Represents a user of the software (each user has multiple "Accounts" for different sites).
 */
struct User {
    int pk;
    std::string username;
    std::string firstName;
    std::string lastName;
    std::string password;

    std::vector<char> hash;

    User() : pk(-1) { }
};

// Registers the User class for json deserialization
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(\
        User,\
        pk,\
        username,\
        firstName,\
        lastName,\
        password\
        )

#endif  // USER_RECORD_H

//
// Created by jeremy on 2022-02-10.
//

#ifndef PROJECT_ACCOUNT_H
#define PROJECT_ACCOUNT_H

#include <string>

#include <json.h>


struct Account {
    int pk;
    std::string label;
    std::string username;
    std::string keyHash;
    std::string url;
    long created;
    long lastAccessed;
    long lastModified;
    long expiry;
    int userID;

    Account() : pk(-1), created(0), lastAccessed(0), lastModified(0), expiry(0), userID(-1) { }
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(\
        Account,\
        pk,\
        label,\
        username,\
        keyHash,\
        url,\
        created,\
        lastAccessed,\
        lastModified,\
        expiry,\
        userID\
        )

#endif //PROJECT_ACCOUNT_H

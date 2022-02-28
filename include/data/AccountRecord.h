//
// Created by jeremy on 2022-02-10.
//

#ifndef PROJECT_ACCOUNTRECORD_H
#define PROJECT_ACCOUNTRECORD_H

#include <string>

#include "json.h"


struct AccountRecord {
    int id;
    std::string label;
    std::string username;
    std::string keyHash;
    std::string url;
    long created;
    long lastAccessed;
    long lastModified;
    long expiry;
    int userID;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(\
        AccountRecord,\
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

#endif //PROJECT_ACCOUNTRECORD_H

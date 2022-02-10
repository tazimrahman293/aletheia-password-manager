//
// Created by jeremy on 2022-02-10.
//

#ifndef PROJECT_ACCOUNT_RECORD_H
#define PROJECT_ACCOUNT_RECORD_H

#include <ctime>
#include <string>

namespace data {

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

}  // namespace data

#endif //PROJECT_ACCOUNT_RECORD_H

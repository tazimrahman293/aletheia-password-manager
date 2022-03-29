//
// Created by jeremy on 2022-02-10.
//

#ifndef PROJECT_ACCOUNT_H
#define PROJECT_ACCOUNT_H

#include <string>
#include <vector>
#include <json.h>


/**
 * Represents a single account entry (i.e. username + password for a site/service).
 */
struct Account {
    int pk;
    std::string label;
    std::string username;
    std::string password;
    std::string url;
	std::vector<char> hash;
    long created;
    long lastAccessed;
    long lastModified;
    long expiry;
    int userID;

    Account() : pk(-1), created(0), lastAccessed(0), lastModified(0), expiry(0), userID(-1) { }
};

// Registers the Account class for json deserialization
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(\
        Account,\
        pk,\
        label,\
        username,\
        password,\
        url,\
        created,\
        lastAccessed,\
        lastModified,\
        expiry,\
        userID\
        )

#endif //PROJECT_ACCOUNT_H

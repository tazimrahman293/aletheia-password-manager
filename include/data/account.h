//
// Created by jeremy on 2022-02-10.
//

#ifndef PROJECT_ACCOUNT_H
#define PROJECT_ACCOUNT_H

#include <string>
#include <utility>

#include <data/AccountRecord.h>

namespace data {
    class Account {

        data::AccountRecord record;

    public:
        explicit Account(data::AccountRecord record) : record(std::move(record)) { }
        int ID() const { return record.id; }

        std::string Label() const { return record.label; }
        void Label(std::string &label) { record.label = label; }

        std::string Username() const { return record.username; }
        void Username(std::string &username) { record.username = username; }

        std::string KeyHash() const { return record.keyHash; }
        void KeyHash(std::string &hash) { record.keyHash = hash; }

        std::string URL() const { return record.url; }
        void URL(std::string &url) { record.url = url; }

        long DateCreated() const { return record.created; }
        long DateLastAccessed() const { return record.lastAccessed; }
        long DateLastModified() const { return record.lastModified; }

        long DateExpires() const { return record.expiry; }
        void DateExpires(long datetime) { record.expiry = datetime; }

        int UserID() const { return record.userID; }
    };
}  // namespace data

#endif //PROJECT_ACCOUNT_H

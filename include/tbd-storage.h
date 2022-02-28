#ifndef TBD_STORAGE_H
#define TBD_STORAGE_H

// Definitions, classes, and types specific to the storage functions go here

#include <string>
#include <vector>

#include <sqlite3.h>
#include <sqlite_orm.h>

#include <data/user.h>
#include "data/account.h"

/////////////////////////
/* Basic DB Operations */
/////////////////////////

namespace db {

    class Storage {
        class _Storage;
        std::unique_ptr<_Storage> s;

    public:
        explicit Storage(const std::string &dbFilename);
        ~Storage();

        data::User AddUser(data::UserRecord& userData) noexcept;
        // data::User AddUser(const std::string &firstName, const std::string &lastName) noexcept;
        std::unique_ptr<data::User> GetUserByID(int id) noexcept;
        std::vector<data::User> GetAllUsers() noexcept;
        void RemoveUser(int id) noexcept;

        data::Account AddAccount(
                const std::string &label, const std::string &username, const std::string &hash,
                const std::string &url, long expiry, int userID
                ) noexcept;
        std::unique_ptr<data::Account> GetAccountByID(int id) noexcept;
        std::vector<data::Account> GetAllAccountsByUserID(int userID) noexcept;
        void RemoveAccount(int id) noexcept;
    };

}  // namespace db

//////////////////////

#endif  // TBD_STORAGE_H

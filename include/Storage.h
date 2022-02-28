#ifndef TBD_STORAGE_H
#define TBD_STORAGE_H

// Definitions, classes, and types specific to the storage functions go here

#include <string>
#include <vector>

#include <sqlite3.h>
#include <sqlite_orm.h>

#include <data/User.h>
#include "data/Account.h"
#include "events/LoginAttemptEvent.h"

inline auto createDatabase(const std::string &dbFilename) {
    using namespace sqlite_orm;

    return make_storage(
            dbFilename,
            make_table(
                    "users",
                    make_column("ID", &UserRecord::id, autoincrement(), primary_key()),
                    make_column("first_name", &UserRecord::firstName),
                    make_column("last_name", &UserRecord::lastName),
                    make_column("key_hash", &UserRecord::keyHash)
            ),
            make_table(
                    "accounts",
                    make_column("ID", &AccountRecord::id, autoincrement(), primary_key()),
                    make_column("label", &AccountRecord::label),
                    make_column("username", &AccountRecord::username),
                    make_column("key_hash", &AccountRecord::keyHash),
                    make_column("url", &AccountRecord::url),
                    make_column("created", &AccountRecord::created),
                    make_column("last_accessed", &AccountRecord::lastAccessed),
                    make_column("last_modified", &AccountRecord::lastModified),
                    make_column("expiry", &AccountRecord::expiry),
                    make_column("userID", &AccountRecord::userID),
                    foreign_key(&AccountRecord::userID).references(&UserRecord::id)
            )
    );
}

/////////////////////////
/* Basic DB Operations */
/////////////////////////

class Storage {
    class _Storage;
    std::unique_ptr<_Storage> s;

public:
    explicit Storage(const std::string &dbFilename);
    ~Storage();

    void OnLoginAttempt(LoginAttemptEvent *event);

    User AddUser(UserRecord& userData) noexcept;
    // User AddUser(const std::string &firstName, const std::string &lastName) noexcept;
    std::unique_ptr<User> GetUserByID(int id) noexcept;
    std::vector<User> GetAllUsers() noexcept;
    void RemoveUser(int id) noexcept;

    Account AddAccount(
            const std::string &label, const std::string &username, const std::string &hash,
            const std::string &url, long expiry, int userID
            ) noexcept;
    std::unique_ptr<Account> GetAccountByID(int id) noexcept;
    std::vector<Account> GetAllAccountsByUserID(int userID) noexcept;
    void RemoveAccount(int id) noexcept;
};

//////////////////////

#endif  // TBD_STORAGE_H

#ifndef TBD_STORAGE_H
#define TBD_STORAGE_H

// Definitions, classes, and types specific to the storage functions go here

#include <string>
#include <vector>

#include <sqlite3.h>
#include <sqlite_orm.h>

#include <events/LoginAttemptEvent.h>
#include <data/Account.h>
#include <data/User.h>

inline auto createDatabase(const std::string &dbFilename) {
    using namespace sqlite_orm;

    return make_storage(
            dbFilename,
            make_table<User>(
                    "users",
                    make_column("ID", &User::pk, autoincrement(), primary_key()),
                    make_column("first_name", &User::firstName),
                    make_column("last_name", &User::lastName),
                    make_column("key_hash", &User::keyHash)
            ),
            make_table<Account>(
                    "accounts",
                    make_column("ID", &Account::pk, autoincrement(), primary_key()),
                    make_column("label", &Account::label),
                    make_column("username", &Account::username),
                    make_column("key_hash", &Account::keyHash),
                    make_column("url", &Account::url),
                    make_column("created", &Account::created),
                    make_column("last_accessed", &Account::lastAccessed),
                    make_column("last_modified", &Account::lastModified),
                    make_column("expiry", &Account::expiry),
                    make_column("userID", &Account::userID),
                    foreign_key(&Account::userID).references(&User::pk)
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

    template<class T>
    void InsertOrUpdate(T record) noexcept
    {
        const int pk = s->database.insert(record);
        record.pk = pk;
    }
    template<class T>
    std::unique_ptr<T> GetByID(int pk) noexcept;
    template<class T>
    void Remove(int pk) noexcept;

    std::vector<User> GetAllUsers() noexcept;
    std::vector<Account> GetAllAccountsByUserID(int userID) noexcept;

};

//////////////////////

#endif  // TBD_STORAGE_H

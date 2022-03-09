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


/**
 * Sets up the database schema.
 * @param dbFilename the name of the database file to be used
 * @return a storage object for accessing the database
 */
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

// Creates a type alias, otherwise the return type of createDatabase would be illegible
using Database = decltype(createDatabase(""));


class Storage {

    // Internal class for managing the Database type alias and schema
    class _Storage {
    public:
        // Database handler
        Database database;

        explicit _Storage(const std::string &db_filename) :
                database(createDatabase(db_filename)) {
            // Important: must do this or else the in-memory schema here may not align with the
            // persistent schema on disk
            database.sync_schema();
        }
    };

    // Handle for the internal storage class instance
    std::unique_ptr<_Storage> s;

public:

    explicit Storage(const std::string& dbFilename);

    Storage(Storage&) = delete;  // No copying
    void operator=(const Storage&) = delete;  // No assignment
    ~Storage() = default;

    void OnLoginAttempt(LoginAttemptEvent *event);

    /**
     * Performs a database INSERT of a record.
     * @tparam T the record type
     * @param record the record to be inserted
     */
    template<class T>
    void Insert(T& record) noexcept
    {
        const int pk = s->database.insert(record);
        record.pk = pk;
    }

    /**
     * Performs a database UPDATE of a record.
     * @tparam T the record type
     * @param record the record to be updated
     */
    template<class T>
    void Update(T& record) noexcept
    {
        s->database.update(record);
    }

    /**
     * Performs a database REPLACE/UPSERT (if primary key exists, update, otherwise insert).
     * @tparam T the record type
     * @param record the record to be inserted or updated
     */
    template<class T>
    void InsertOrUpdate(T& record) noexcept
    {
        s->database.replace(record);
    }

    /**
     * Performs a database SELECT using the primary key field.
     * @tparam T the record type
     * @param pk the primary key to be queried on
     * @return a single record if a database entry exists with pk, otherwise nullptr
     */
    template<class T>
    std::unique_ptr<T> GetByID(int pk) noexcept
    {
        if (auto record = s->database.get_pointer<T>(pk)) {
            return std::make_unique<T>(*record);
        } else {
            return nullptr;
        }
    }

    /**
     * Performs a database DELETE operation
     * @tparam T the record type
     * @param pk the primary key of the entry to be deleted
     */
    template<class T>
    void Remove(int pk) noexcept
    {
        s->database.remove<T>(pk);
    }

    std::vector<User> GetAllUsers() noexcept;
    std::vector<Account> GetAllAccountsByUserID(int userID) noexcept;

};

//////////////////////

#endif  // TBD_STORAGE_H

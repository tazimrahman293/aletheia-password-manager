// db.cpp
// Contains wrapper function definitions for the use of the database storage for
// the TBD password manager project.
// Authors: Jeremy Rempel

#include <chrono>
#include <ctime>
#include <memory>

#include <tbd-storage.h>
#include <data/user.h>
#include <data/user-record.h>

using namespace data;

namespace db {

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
    using Database = decltype(createDatabase(""));


    class Storage::_Storage {
    public:
        Database database;

        explicit _Storage(const std::string &db_filename) :
                database(createDatabase(db_filename)) {
            database.sync_schema();
        }
    };


    Storage::Storage(const std::string &dbFilename) :
            s(std::make_unique<_Storage>(dbFilename)) {}


    Storage::~Storage() = default;


    User Storage::AddUser(UserRecord& userData) noexcept
    {
        const int id = s->database.insert(userData);
        userData.id = id;

        return User(userData);
    }


    std::unique_ptr<User> Storage::GetUserByID(int id) noexcept
    {
        if (auto user = s->database.get_pointer<UserRecord>(id)) {
            return std::make_unique<User>(*user);
        } else {
            return nullptr;
        }
    }


    std::vector<User> Storage::GetAllUsers() noexcept
    {
        auto records = s->database.get_all<UserRecord>();
        std::vector<User> users;
        for (const auto &record : records) {
            users.emplace_back(User(record));
        }
        return users;
    }


    void Storage::RemoveUser(int id) noexcept
    {
        s->database.remove<UserRecord>(id);
    }

    data::Account Storage::AddAccount(
            const std::string &label, const std::string &username, const std::string &hash,
            const std::string &url, long expiry, int userID
    ) noexcept
    {
        auto now = std::chrono::system_clock::now();
        time_t currentTime = std::chrono::system_clock::to_time_t(now);

        AccountRecord record {
                .id = -1,
                .label = label,
                .username = username,
                .keyHash = hash,
                .url = url,
                .created = currentTime,
                .lastAccessed = currentTime,
                .lastModified = currentTime,
                .expiry = expiry,
                .userID = userID
        };
        const int id = s->database.insert(record);
        record.id = id;

        return Account(record);
    }

    std::unique_ptr<data::Account> Storage::GetAccountByID(int id) noexcept
    {
        if (auto account = s->database.get_pointer<AccountRecord>(id)) {
            return std::make_unique<Account>(*account);
        } else {
            return nullptr;
        }
    }

    std::vector<data::Account> Storage::GetAllAccountsByUserID(int userID) noexcept
    {
        using namespace sqlite_orm;
        auto records = s->database.get_all<AccountRecord>(
                where(c(&AccountRecord::userID) == userID)
                );
        std::vector<Account> accounts;
        for (const auto &record : records) {
            accounts.emplace_back(Account(record));
        }
        return accounts;
    }

    void Storage::RemoveAccount(int id) noexcept
    {
        s->database.remove<AccountRecord>(id);
    }
}  // namespace db


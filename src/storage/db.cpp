// db.cpp
// Contains wrapper function definitions for the use of the database storage for
// the TBD password manager project.
// Authors: Jeremy Rempel

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
                        make_column("id", &UserRecord::id, autoincrement(), primary_key()),
                        make_column("first_name", &UserRecord::firstName),
                        make_column("last_name", &UserRecord::lastName)
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
            _s(std::make_unique<_Storage>(dbFilename)) {}


    Storage::~Storage() = default;


    User Storage::addUser(const std::string &firstName, const std::string &lastName) noexcept
    {
        UserRecord record {
            .id = -1,
            .firstName = firstName,
            .lastName = lastName
        };
        const int id = _s->database.insert(record);
        record.id = id;

        return User(record);
    }


    std::unique_ptr<User> Storage::getUserByID(int id) noexcept
    {
        if (auto user = _s->database.get_pointer<UserRecord>(id)) {
            return std::make_unique<User>(*user);
        } else {
            return nullptr;
        }
    }


    std::vector<User> Storage::getAllUsers() noexcept
    {
        auto records = _s->database.get_all<UserRecord>();
        std::vector<User> users;
        for (const auto &record : records) {
            users.emplace_back(User(record));
        }
        return users;
    }


    void Storage::removeUser(int id) noexcept
    {
        _s->database.remove<UserRecord>(id);
    }

}  // namespace db


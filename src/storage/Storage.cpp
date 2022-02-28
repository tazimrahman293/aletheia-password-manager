// storage.cpp
// Contains top-level function definitions for storing and retrieving persistent data 
// for the TBD password manager project.
// Authors: Jeremy Rempel

#include <memory>
#include <iostream>

#include <aletheia.h>
#include <Storage.h>
#include <data/User.h>
#include <data/UserRecord.h>
#include <network/EventBus.h>

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
        s(std::make_unique<_Storage>(dbFilename))
{
    EventBus *eventBus = EventBus::GetInstance();
    eventBus->Subscribe(this, &Storage::OnLoginAttempt);
}


Storage::~Storage() = default;


void Storage::OnLoginAttempt(LoginAttemptEvent *event)
{
    std::cout << "Login attempt -- ID: " << event->uid << ", Pass: " << event->password << std::endl;
    auto user = GetUserByID(event->uid);
    std::cout << "Found user " << user->Name() << " (" << user->ID() << ")" << std::endl;
}


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

Account Storage::AddAccount(
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

std::unique_ptr<Account> Storage::GetAccountByID(int id) noexcept
{
    if (auto account = s->database.get_pointer<AccountRecord>(id)) {
        return std::make_unique<Account>(*account);
    } else {
        return nullptr;
    }
}

std::vector<Account> Storage::GetAllAccountsByUserID(int userID) noexcept
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

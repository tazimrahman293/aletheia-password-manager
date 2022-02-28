// storage.cpp
// Contains top-level function definitions for storing and retrieving persistent data 
// for the TBD password manager project.
// Authors: Jeremy Rempel

#include <memory>
#include <iostream>

#include <aletheia.h>
#include <Storage.h>
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
    auto user = GetByID<User>(event->uid);
    std::cout << "Found user " << user->firstName << " (" << user->pk << ")" << std::endl;
}


template<class T>
void Storage::InsertOrUpdate(T record) noexcept
{
    const int pk = s->database.insert(record);
    record.pk = pk;
}


template<class T>
std::unique_ptr<T> Storage::GetByID(int pk) noexcept
{
    if (auto record = s->database.get_pointer<T>(pk)) {
        return std::make_unique<T>(*record);
    } else {
        return nullptr;
    }
}


template<class T>
void Storage::Remove(int pk) noexcept
{
    s->database.remove<T>(pk);
}


std::vector<User> Storage::GetAllUsers() noexcept
{
    auto records = s->database.get_all<User>();
    return records;
}


std::vector<Account> Storage::GetAllAccountsByUserID(int userID) noexcept
{
    using namespace sqlite_orm;
    auto records = s->database.get_all<Account>(
            where(c(&Account::userID) == userID)
    );
    return records;
}

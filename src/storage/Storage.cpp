// storage.cpp
// Contains top-level function definitions for storing and retrieving persistent data 
// for the TBD password manager project.
// Authors: Jeremy Rempel

#include <memory>
#include <iostream>

#include <aletheia.h>
#include <Storage.h>
#include <network/EventBus.h>


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

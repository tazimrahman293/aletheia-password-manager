// storage.cpp
// Contains top-level function definitions for storing and retrieving persistent data 
// for the TBD password manager project.
// Authors: Jeremy Rempel

#include <algorithm>
#include <memory>
#include <iostream>
#include <tuple>

#include <aletheia.h>
#include <Storage.h>
#include <network/EventBus.h>


/**
 * Constructor for a new Storage instance. Subscribes the instance to various Events.
 * @param dbFilename the name of the database file to use (will be created if it doesn't exist)
 */
Storage::Storage(const std::string &dbFilename) :
        s(std::make_unique<_Storage>(dbFilename)) { }


/**
 * Get all users in the current database file.
 * @return a vector of User records
 */
std::vector<User> Storage::GetAllUsers() noexcept
{
    auto records = s->database.get_all<User>();
    return records;
}


std::unique_ptr<User> Storage::GetUserByUsername(const std::string &username) noexcept
{
    using namespace sqlite_orm;
    auto records = s->database.select(
            asterisk<User>(),
                    where(c(&User::username) == username)
                    );

    std::unique_ptr<User> user = std::make_unique<User>();

    if (records.empty()) {
        return nullptr;
    }

    auto first = records.at(0);
    user->pk = std::get<0>(first);
    user->username = std::get<1>(first);
    user->firstName = std::get<2>(first);
    user->lastName = std::get<3>(first);
    return user;
}


/**
 * Get all accounts belonging to a particular user.
 * @param userID the primary key of the user to filter by
 * @return a vector of Account records
 */
std::vector<Account> Storage::GetAllAccountsByUserID(int userID) noexcept
{
    using namespace sqlite_orm;
    auto records = s->database.get_all<Account>(
            where(c(&Account::userID) == userID)
    );
    return records;
}

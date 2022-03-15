/**
 * cli.pp
 * Top level module containing implementations of handler functions for each user input
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>



#include "cli/CommandLine.h"
#include "cli/InputParser.h"
#include "network/EventBus.h"
#include "events/LoginAttemptEvent.h"
#include "Storage.h"
#include "network/HTTPServer.h"
#include "events/AccountCreateEvent.h"
#include "events/AccountUpdateEvent.h"
#include "Storage.h"


void CommandLine::HandleCommand() {

    if (InputExists("login") && (UserInputs[1] == "login")){ // Login command
        // jeremy: I foresee a potential problem here with this, what if the user enters "aletheia garbage login"
        // should we not do something about the garbage input and tell the user about it?
        // int userId = std::stoi();
        // std::vector<Account> userAccount = Storage::GetAllAccountsByUserID(userId);

        // jeremy: The pk attribute belongs to one individual Account, not a vector of them
        // if (userAccount->pk == InputArg[2]){
        //     UpdateOutput("Login successful from user");
        // }

        // Storing user inputs
        std::string FirstName = UserInputs[2];
        std::string LastName = UserInputs[3];
        //std::string Input_password = UserInputs[4];

        std::vector<User> ExtractedUserVector = UserDatabase->GetAllUsers(); // Grab database of all users
        // Don't know if that's the correct way of grabbing the storage, but it's the implementation for now

        for (User user: ExtractedUserVector) {
            if ((user.firstName == FirstName) && (user.lastName == LastName)) {  // If password exists and matches user input, login is successful
                // std::cout << "Login successful. Welcome " << *Database_ID->firstName <<" " << *Database_ID->lastName << std::endl;
                std::cout << "Access to structure successful" << std::endl;
                break;
            } else {
                std::cout << "Invalid login input" << std::endl;
            }
        }

        std::cout << "Login command finished being executed" << std::endl;

    }
    // jeremy: should this be else if? probably don't want to both log in and create a new account and edit an account
    // in the same command
    else if (InputExists("--new-account") && (UserInputs[1] == "--new-account")){ // Create account

        std::cout << "Registration command working" << std::endl;
    }

    // jeremy: same comment as above
    else if (InputExists("--edit-account") && (UserInputs[1] == "--edit-account")){
        std::cout << "Updating account command working" << std::endl;
    }
    std::cout << "Command Handler was ran" << std::endl;
}



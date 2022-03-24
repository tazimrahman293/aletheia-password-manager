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
#include "data/User.h"
#include "data/Account.h"


void CommandLine::HandleCommands() {
    if (InputExists("-CLI")) { // Enter into the CLI
        std::cout << "CLI has been entered. Welcome!" << std::endl;
        std::string Input_username;
        std::string command;
        std::string Input_password;
        bool valid_login = false;
        while (true) {
            std::cout << "What would you like to do? Type help for a list of commands." << std::endl;
            //std::cin >> command;
            std::getline(std::cin, command); // Command input for each one
            if (command == "login") {  // Login command

                std::cout << "Executing Login Command" << std::endl;

                std::cout << "Enter your username" << std::endl;
                std::getline(std::cin, Input_username);
                std::cout << "Enter your password" << std::endl;
                std::getline(std::cin, Input_password);

                std::vector<User> allUsers = database->GetAllUsers(); // Grab database of all users registered

                for (User &user : allUsers) {
                    if ((user.username == Input_username) && (user.keyHash == Input_password)) {
                        // std::cout << "Login successful. Welcome " << *Database_ID->firstName <<" " << *Database_ID->lastName << std::endl;
                        valid_login = true;
                        break;
                    }
                    else{ // Checking to make sure database is being accessed
                        std::cout << "Passwords from database " << user.pk << std::endl;
                    }
                }

                if (valid_login == true){
                    std::cout << "Welcome, " << Input_username << std::endl;
                } else{
                    std::cout << "Invalid login attempt" << std::endl;
                }
                //std::cout << "Login command finished being executed" << std::endl;

            } else if (command == "register"){ // Register a new user into the server
                std::cout << "About to register" << std::endl;
                std::cout << "Enter your username" << std::endl;
                std::getline(std::cin, Input_username);
                std::cout << "Enter your password" << std::endl;
                std::getline(std::cin, Input_password);

                std::vector<User> allUsers = database->GetAllUsers();

                bool UsernameExists;
                for (User &user : allUsers){
                    if (user.username == Input_username){
                        UsernameExists = true;
                        break;
                    } else{
                        UsernameExists = false;
                    }
                }

                // Create a new User if the username doesn't exist, else output that the user exists
                if (UsernameExists ==  true){
                    std::cout << "Username exists already!" << std::endl;
                } else{
                    User NewUser;
                    NewUser.username = Input_username;
                    NewUser.keyHash = Input_password;
                    database->Insert(NewUser); // Store user in database

                    std::cout << "Successfully registered " << Input_username << std::endl;
                }

                std::cout << "Register command finished executing" << std::endl;


            } else if (command == "new-account") {  /* Create account */

                if (valid_login == false){
                    std::cout << "Please login before creating a new account" << std::endl;
                } else {
                    std::cout << "Creating new account working" << std::endl;
                }

            } else if (command == "edit-account") {  // Edit account
                if (valid_login == false){
                    std::cout << "Please login before updating an account" << std::endl;
                } else {
                    std::cout << "Updating account command working"
                              << std::endl;
                }

            } else if (command == "quit"){
                std::cout << "Exiting Aletheia Password Manager. Thank you for using." << std::endl;
                break;

            } else if (command == "help") {
                std::cout << "Command list for Aletheia Password Manager: " << std::endl;
                std::cout << "login: Login to the Password Manager\n"
                             "register: Create a new User\n"
                             "new-account: Create new account to add to the database\n"
                             "edit-account: Edit an existing account\n"
                             "quit: Exit Aletheia Password Manager" << std::endl;
            }
            else{
                std::cout << "Invalid command input " << command << std::endl;
            }
        }
    } else{
        std::cout << "Invalid input to enter into CLI" << std::endl;
    }
}



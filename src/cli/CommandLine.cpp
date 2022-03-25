/**
 * cli.pp
 * Top level module containing implementations of handler functions for each user input
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cli/CommandLine.h"
#include "cli/InputParser.h"
#include "Storage.h"
#include "data/User.h"
#include "data/Account.h"


void CommandLine::HandleCommands() {
    if (InputExists("-CLI")) { // Enter into the CLI
        std::cout << "CLI has been entered. Welcome!" << std::endl;
        std::string inputCommand;
        std::string inputUsername;
        std::string inputPassword;
        bool validLogin = false;
        while (true) {
            std::cout << "What would you like to do? Type help for a list of commands." << std::endl;

            std::getline(std::cin, inputCommand); // Command input for each one
            if (inputCommand == "login") {  // Login command
                bool success;

                while (!success) {
                    std::cout << "Username: " << std::flush;
                    std::getline(std::cin, inputUsername);

                    std::cout << "Password: " << std::flush;
                    std::getline(std::cin, inputPassword);

                    auto user = database->GetUserByUsername(inputUsername);

                    if (user != nullptr && user->keyHash == inputPassword) {
                        success = true;
                        std::cout << "Logged in. Welcome " << user->firstName << "." << std::endl;

                    } else {
                        // Non-existing username provided or password is incorrect
                        if (user == nullptr || user->keyHash != inputPassword) {
                            std::cout << "Invalid login attempt" << std::endl;
                        }
                    }
                }

            } else if (inputCommand == "register") { // Register a new user into the server
                std::string password1 = "x", password2 = "y";
                bool usernameExists = true;

                while (usernameExists) {
                    std::cout << "Username: " << std::flush;
                    std::getline(std::cin, inputUsername);

                    auto user = database->GetUserByUsername(inputUsername);
                    if (user == nullptr) {
                        usernameExists = false;
                    } else {
                        std::cout << "Username " << inputUsername << " exists - try again" << std::endl;
                    }
                }

                std::string firstName, lastName;

                while (firstName.empty()) {
                    std::cout << "First name: " << std::flush;
                    std::getline(std::cin, firstName);
                }

                std::cout << "Last name: " << std::flush;
                std::getline(std::cin, lastName);

                while (password1 != password2) {
                    std::cout << "Password: " << std::flush;
                    std::getline(std::cin, password1);

                    std::cout << "Confirm password: " << std::flush;
                    std::getline(std::cin, password2);

                    if (password1 == password2) {
                        inputPassword = password2;
                        break;
                    }

                    std::cout << "Passwords do not match - try again" << std::endl;

                }

                User newUser;
                newUser.username = inputUsername;
                newUser.firstName = firstName;
                newUser.lastName = lastName;
                newUser.keyHash = inputPassword;
                database->Insert(newUser); // Store user in database

                std::cout << "Successfully registered "
                          << inputUsername << "(" << firstName << " " << lastName << ")" << std::endl;

            } else if (inputCommand == "new-account") {  /* Create account */

                if (validLogin == false){
                    std::cout << "Please login before creating a new account" << std::endl;
                } else {
                    std::cout << "Creating new account working" << std::endl;
                }

            } else if (inputCommand == "edit-account") {  // Edit account
                if (validLogin == false){
                    std::cout << "Please login before updating an account" << std::endl;
                } else {
                    std::cout << "Updating account command working"
                              << std::endl;
                }

            } else if (inputCommand == "quit"){
                std::cout << "Exiting Aletheia Password Manager. Thank you for using." << std::endl;
                break;

            } else if (inputCommand == "help") {
                std::cout << "Command list for Aletheia Password Manager: " << std::endl;
                std::cout << "login: Login to the Password Manager\n"
                             "register: Create a new User\n"
                             "new-account: Create new account to add to the database\n"
                             "edit-account: Edit an existing account\n"
                             "quit: Exit Aletheia Password Manager" << std::endl;
            }
            else{
                std::cout << "Invalid command input " << inputCommand << std::endl;
            }
        }
    } else{
        std::cout << "Invalid input to enter into CLI" << std::endl;
    }
}



/**
 * CommandLine.pp
 * Top level module containing implementations of commands for each user input
 */

#include <chrono>
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
    if (InputExists("-CLI") && CountTokens() == 1 && GetTokenAtPosition(0) == "-CLI") { // Enter into the CLI
        std::cout << "CLI has been entered. Welcome!" << std::endl;

        std::string inputCommand;
        std::string inputUsername;
        std::string inputPassword;
        int pk; // Used for looking up accounts the user has

        bool validLogin = false;
        while (true) {
            std::cout << "What would you like to do? Type help for a list of commands." << std::endl;

            std::getline(std::cin, inputCommand); // Command input for each one
            if (inputCommand == "login") {  // Login command
                if (validLogin){
                    std::cout << "You're already logged in!" << std::endl;

                } else {
                    bool success = false;

                    while (!success) {
                        // Username and password inputs
                        std::cout << "Username: " << std::flush;
                        std::getline(std::cin, inputUsername);

                        std::cout << "Password: " << std::flush;
                        std::getline(std::cin, inputPassword);

                        // Grab database of usernames and confirm the login attempt
                        auto user = database->GetUserByUsername(inputUsername);

                        if (user != nullptr && user->keyHash == inputPassword) {
                            success = true;
                            std::cout << "Logged in. Welcome " << user->firstName << "." << std::endl;

                            pk = user->pk; // Used for database search of user accounts

                        } else {
                            // Non-existing username provided or password is incorrect
                            if (user == nullptr ||
                                user->keyHash != inputPassword) {
                                std::cout << "Invalid login attempt" << std::endl;
                            }
                        }
                    }

                    validLogin = true;  // Login attempt is valid, allowing access to other commands
                }

            } else if (inputCommand == "register") { // Register a new user into the server
                std::string password1 = "x", password2 = "y";
                bool usernameExists = true;

                // Username and password inputs
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

                // Personal information input
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
                    std::string accountUsernameInput;
                    std::string accountPasswordInput;
                    std::string URL;
                    std::string label;

                    // Username and password inputs for new account
                    std::cout << "Account Username: " << std::flush;
                    std::getline(std::cin, accountUsernameInput);

                    std::cout << "Account Password: " << std::flush;
                    std::getline(std::cin, accountPasswordInput);

                    std::cout << "Where is this account being used?" << std::flush;
                    std::getline(std::cin, label);

                    std::cout << "Website URL: " << std::flush;
                    std::getline(std::cin, URL);

                    auto User = database->GetUserByUsername(inputUsername); // Search for user to assign userID

                    // Getting current time and converting to long data type in a single line (can be changed if needed)
                    long value_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();

                    Account newAccount;
                    newAccount.username = accountUsernameInput;
                    newAccount.keyHash = accountPasswordInput;
                    newAccount.label = label;
                    newAccount.url = URL;
                    newAccount.userID = User->pk;

                    newAccount.created = value_ms;
                    newAccount.lastAccessed = value_ms;
                    newAccount.lastModified = value_ms;

                    database->Insert(newAccount);
                    std::cout << "Successfully added account " << accountUsernameInput << std::endl;
                }

            } else if (inputCommand == "edit-account") {  // Edit account
                if (validLogin == false){
                    std::cout << "Please login before updating an account" << std::endl;

                } else {
                    std::string modifyInput;
                    std::string accountUsername;
                    std::string newAccountUsername;
                    std::string newAccountPassword;

                    std::string verifyNewAccountUsername;
                    std::string verifyNewAccountPassword;

                    bool foundAccount = false;
                    bool success = false;
                    std::vector<Account> accountDatabase =
                        database->GetAllAccountsByUserID(pk);

                    std::cout << "Current accounts: " << std::endl;

                    for (Account account : accountDatabase) {
                        std::cout << account.username << std::endl;
                    }

                    while (!success) {
                        std::cout << "Which account would you like to modify?" << std::flush;
                        std::getline(std::cin, accountUsername);

                        std::cout << "What would you like to modify?"  << std::flush;
                        std::getline(std::cin, modifyInput);

                        Account modifiedAccount;

                        // Search for account
                        for (Account account : accountDatabase){

                            if (account.username == accountUsername){
                                modifiedAccount = account;
                                foundAccount = true;
                                break;
                            }
                        }

                        // Modify account
                        if (foundAccount) {
                            if (modifyInput == "username") {
                                while (newAccountUsername != verifyNewAccountUsername) {
                                    std::cout << "Enter the new username: " << std::flush;
                                    std::getline(std::cin, newAccountUsername);

                                    std::cout << "Verify the new username: " << std::flush;
                                    std::getline(std::cin, verifyNewAccountUsername);

                                    if (newAccountUsername == verifyNewAccountUsername) {
                                        modifiedAccount.username = newAccountUsername;
                                    }

                                    else {
                                        std::cout << "Usernames do not match" << std::endl;
                                    }
                                }

                            } else if (modifyInput == "password") {
                                while (newAccountPassword != verifyNewAccountPassword) {
                                    std::cout << "Enter the new password: " << std::flush;
                                    std::getline(std::cin, newAccountPassword);

                                    std::cout << "Verify the new password: " << std::flush;
                                    std::getline(std::cin, verifyNewAccountPassword);

                                    if (newAccountPassword == verifyNewAccountPassword) {
                                        modifiedAccount.keyHash = newAccountPassword;
                                    }

                                    else {
                                        std::cout << "Passwords do not match" << std::endl;
                                    }
                                }

                            } else {
                                std::cout << "Cannot modify " << modifyInput << std::endl;
                            }

                            // Updating time last modified and accessed
                            long value_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();
                            modifiedAccount.lastModified = value_ms;
                            modifiedAccount.lastAccessed = value_ms;

                            database->Update(modifiedAccount);
                            std::cout << "Account has been updated!" << std::endl;

                        } else{
                            std::cout << accountUsername << " not found" << std::endl;
                        }

                        success = true;
                    }
                }

            } else if (inputCommand == "view-accounts"){

                if (validLogin == false){
                    std::cout << "Please login before accessing your accounts" << std::endl;

                } else {
                    std::vector<Account> accountDatabase = database->GetAllAccountsByUserID(pk);

                    long value_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();

                    std::cout << "Accounts used by " << inputUsername << ":"<< std::endl;
                    for (Account account : accountDatabase) {
                        std::cout << account.username << std::endl;
                        account.lastAccessed = value_ms;
                    }
                }
            } else if (inputCommand == "quit"){
                std::cout << "Exiting Aletheia Password Manager. Thank you for using." << std::endl;
                break;

            } else if (inputCommand == "help") {
                std::cout << "Command list for Aletheia Password Manager: " << std::endl;
                std::cout << "login: Login to the Password Manager\n"
                             "logout: Logout of the Password Manager\n"
                             "register: Create a new User\n"
                             "new-account: Create new account to add to the database\n"
                             "edit-account: Edit an existing account\n"
                             "view-account: View all current accounts in the database\n"
                             "quit: Exit Aletheia Password Manager" << std::endl;


            } else if (inputCommand == "logout") {
                if (validLogin == true) {
                    validLogin = false;
                    std::cout << "Successfully logged out of " << inputUsername << std::endl;

                } else{
                    std::cout << "You're currently not logged in!" << std::endl;
                }

            } else{
                std::cout << "Invalid command input " << inputCommand << std::endl;
            }
        }
    } else{
        std::cout << "Invalid input to enter into CLI" << std::endl;
    }
}



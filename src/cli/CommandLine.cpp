/**
 * CommandLine.pp
 * Top level module containing implementations of commands for each user input
 */

#include <chrono>
#include <algorithm>
#include <iostream>
#include <string>

#include "cli/CommandLine.h"
#include "cli/InputParser.h"
#include "data/User.h"
#include "data/Account.h"


void CommandLine::Print(const std::string &message)
{
    std::cout << message << std::flush;
}


void CommandLine::PrintLine(const std::string &message)
{
    std::cout << message << std::endl;
}


std::string CommandLine::GetInput(const std::string &prompt)
{
    std::cout << prompt << " " << std::flush;
    std::string input;
    std::getline(std::cin, input);
    return input;
}


void CommandLine::HandleCommands() {
    PrintLine("Welcome to Aletheia password manager!");
    std::string command;

    while (true) {
        PrintLine("What would you like to do? Type help for a list of commands.");
        command = GetInput(">>");

        if (command == "login") {  // Login command
            if (!ctxManager.SetContext(Login)) {
                PrintLine("Cannot use login command from this menu.");
                continue;
            }

            bool success = false;

            std::string username, password;
            while (!success) {
                username = GetInput("Username:");
                password = GetInput("Password:");

                auto user = database->GetUserByUsername(username);

                if (user != nullptr && user->keyHash == password) {
                    // User exists and password is correct
                    success = true;
                    if (!ctxManager.SetContext(Main)) {
                        PrintLine("Unable to log in at this time.");
                        continue;
                    }
                    ctxManager.authenticated = true;
                    PrintLine("Welcome " + user->firstName + ".");

                } else {
                    // Non-existing username provided or password is incorrect
                    PrintLine("Invalid login!");
                }
            }

        } else if (command == "register") { // Register a new user into the server
            if (!ctxManager.SetContext(Register)) {
                PrintLine("Cannot use register command from this menu.");
                continue;
            }

            bool usernameExists = true;

            std::string username;
            while (usernameExists) {
                username = GetInput("Username:");

                auto user = database->GetUserByUsername(username);
                if (user == nullptr) {
                    usernameExists = false;
                } else {
                    PrintLine("User " + username + " exists - try again.");
                }
            }

            std::string firstName, lastName;
            while (firstName.empty()) {
                firstName = GetInput("First name:");
            }
            lastName = GetInput("Last name:");  // Last name is optional

            std::string password1, password2;
            do {
                password1 = GetInput("Password:");
                password2 = GetInput("Confirm password:");

                if (password1 == password2) {
                    if (password2.empty()) {
                        PrintLine("Please enter a non-empty password.");
                        continue;
                    }
                    break;
                }

                PrintLine("Passwords do not match - try again.");

            } while (password1 != password2 || password2.empty());

            User newUser;
            newUser.username = username;
            newUser.firstName = firstName;
            newUser.lastName = lastName;
            newUser.keyHash = password2;
            database->Insert(newUser); // Store user in database

            std::ostringstream registerMessage;
            registerMessage << "Registered new user: " << username << " (" << firstName << " " << lastName << ").";
            PrintLine(registerMessage.str());

        } else if (command == "new-account") {  /* Create account */
            if (ctxManager.GetContext() != Main || !ctxManager.authenticated) {
                PrintLine("Please sign in before creating a new account.");
                continue;
            }
            PrintLine("Creating a new account.");
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

        } else if (command == "edit-account") {  // Edit account
            if (ctxManager.GetContext() != Main || !ctxManager.authenticated){
                PrintLine("Please sign in before updating an account.");
                continue;
            }
            PrintLine("Updating an account.");
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

        } else if (command == "quit"){
            PrintLine("Exiting. Thank you for using Aletheia!");
            // TODO invalidate session?
            break;

        } else if (command == "help") {
            // TODO Determine context and print only the commands that are currently valid
            Print("Command list for Aletheia:\n");
            Print("  login\t\tLog in to the password manager\n");
            Print("  register\tCreate a new user profile\n");
            Print("  new-account\tCreate a new account entry\n");
            Print("  view-account\tView account information\n");
            Print("  edit-account\tEdit an existing account\n");
            PrintLine("  quit\t\tLog out and exit Aletheia\n");
        }
        else{
            PrintLine("Invalid command: " + command);
        }
    }
}



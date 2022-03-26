/**
 * cli.pp
 * Top level module containing implementations of handler functions for each user input
 */

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
    std::string inputCommand;
    std::string inputUsername;
    std::string inputPassword;
    bool validLogin = false;
    while (true) {
        PrintLine("What would you like to do? Type help for a list of commands.");
        inputCommand = GetInput(">>");

        if (inputCommand == "login") {  // Login command
            bool success = false;

            while (!success) {
                inputUsername = GetInput("Username:");
                inputPassword = GetInput("Password:");

                auto user = database->GetUserByUsername(inputUsername);

                if (user != nullptr && user->keyHash == inputPassword) {
                    // User exists and password is correct
                    success = true;
                    PrintLine("Welcome " + user->firstName + ".");

                } else {
                    // Non-existing username provided or password is incorrect
                    PrintLine("Invalid login!");
                }
            }

        } else if (inputCommand == "register") { // Register a new user into the server
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
            newUser.username = inputUsername;
            newUser.firstName = firstName;
            newUser.lastName = lastName;
            newUser.keyHash = password2;
            database->Insert(newUser); // Store user in database

            PrintLine("Registered new user: " + username + " (" + firstName + " " + lastName + ").");

        } else if (inputCommand == "new-account") {  /* Create account */
            if (!validLogin){
                PrintLine("Please sign in before creating a new account.");
            } else {
                PrintLine("Creating a new account.");
            }

        } else if (inputCommand == "edit-account") {  // Edit account
            if (!validLogin){
                PrintLine("Please sign in before updating an account.");
            } else {
                PrintLine("Updating an account.");
            }

        } else if (inputCommand == "quit"){
            PrintLine("Exiting. Thank you for using Aletheia!");
            // TODO invalidate session?
            break;

        } else if (inputCommand == "help") {
            Print("Command list for Aletheia:\n");
            Print("  login\t\tLog in to the password manager\n");
            Print("  register\tCreate a new user profile\n");
            Print("  new-account\tCreate a new account entry\n");
            Print("  edit-account\tEdit an existing account\n");
            PrintLine("  quit\t\tLog out and exit Aletheia\n");
        }
        else{
            PrintLine("Invalid command: " + inputCommand);
        }
    }
}



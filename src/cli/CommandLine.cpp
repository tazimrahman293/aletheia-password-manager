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
#include "aletheia.h"


void CommandLine::Print(const std::string &message)
{
    if (!testMode)
        std::cout << message << std::flush;
    else
        outStream << message;
}


void CommandLine::PrintLine(const std::string &message)
{
    if (!testMode)
        std::cout << message << std::endl;
    else
        outStream << message << "\n";
}


std::string CommandLine::GetInput(const std::string &prompt)
{
    if (!testMode)
        std::cout << prompt << " " << std::flush;
    else
        outStream << prompt << " ";

    std::string input;
    if (testMode)
        std::getline(inStream, input);
    else
        std::getline(std::cin, input);
    return input;
}


void CommandLine::DoRegister(
        const std::string &username,
        const std::string &firstName,
        const std::string &lastName,
        const std::string &password
)
{
    User newUser;
    newUser.username = username;
    newUser.firstName = firstName;
    newUser.lastName = lastName;
    newUser.password = password;

    auto hash = auth->Encrypt(password);
    auto chars = hashToChars(hash);
    newUser.hash = chars;

    database->Insert(newUser);

    ctxManager.authenticated = true;
    ctxManager.activeUserID = newUser.pk;
    ctxManager.SetContext(Main);

    std::ostringstream registerMessage;
    registerMessage << "Registered new user: " << username << " (" << firstName << " " << lastName << ").";
    PrintLine(registerMessage.str());

}


void CommandLine::DoLogin(const std::string &username, const std::string &password)
{
    auto user = database->GetUserByUsername(username);

    if (user != nullptr) {
        auto hash = charsToHash(user->hash);
        auto k = auth->Decrypt(hash);

        if (password == k) {
            // User exists and password is correct
            if (!ctxManager.SetContext(Main)) {
                PrintLine("Unable to log in at this time.");
                return;
            }
            ctxManager.authenticated = true;
            ctxManager.activeUserID = user->pk;
            PrintLine("Welcome " + user->firstName + ".");
            return;
        }

    }

    // Non-existing username provided or password is incorrect
    PrintLine("Invalid login!");
}


void CommandLine::HandleCommands(const std::string &command) {

	PrintLine("");

    if (command == "login") {  // Login command
        if (!ctxManager.SetContext(Login)) {
            PrintLine("Cannot use login command from this menu.");
            return;
        }

        std::string username, password;
        while (!ctxManager.authenticated) {
            username = GetInput("Username:");
            password = GetInput("Password:");
            DoLogin(username, password);
            if (testMode) break;
        }

    } else if (command == "register") {
        if (!ctxManager.SetContext(Register)) {
            PrintLine("Cannot use register command from this menu.");
            return;
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
            if (testMode) break;
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

            if (testMode) break;

        } while (password1 != password2 || password2.empty());

        DoRegister(username, firstName, lastName, password2);

    } else if (command == "new-account") {  /* Create account */
        if (ctxManager.GetContext() != Main || !ctxManager.authenticated) {
            PrintLine("Please sign in before creating a new account.");
            return;
        }
        PrintLine("Creating a new account...");

        std::string label = GetInput("Account Label:");
        std::string accountUsername = GetInput("Username:");
        std::string accountPassword = GetInput("Password:");
        std::string URL = GetInput("URL:");

        auto user = database->GetByID<User>(ctxManager.activeUserID); // Search for user to assign userID

        // Getting current time and converting to long data type in a single line (can be changed if needed)
        long value_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();

		auto hash = auth->Encrypt(accountPassword);
	    auto encryptedPassword = hashToChars(hash);

        Account newAccount;
        newAccount.username = accountUsername;
        newAccount.hash = encryptedPassword;
        newAccount.label = label;
        newAccount.url = URL;
        newAccount.userID = user->pk;

        newAccount.created = value_ms;
        newAccount.lastAccessed = value_ms;
        newAccount.lastModified = value_ms;

        database->Insert(newAccount);
        PrintLine("Successfully added new account: " + label);

    } else if (command == "edit-account") {  // Edit account
        if (ctxManager.GetContext() != Main || !ctxManager.authenticated){
            PrintLine("Please sign in before updating an account.");
            return;
        }
        PrintLine("Updating an account.");

        std::string fieldToModify;
        std::string accountToModify;

        bool foundAccount = false;
        bool success = false;
        std::vector<Account> accountDatabase = database->GetAllAccountsByUserID(ctxManager.activeUserID);

        PrintLine("Current accounts:");

        for (Account &account : accountDatabase) {
            PrintLine(account.label);
        }

        while (!success) {
            accountToModify = GetInput("Enter an account label to modify:");

            PrintLine("Available fields:\n label\n username\n password\n url\n expiry");
            fieldToModify = GetInput("What field would you like to modify?");

            Account modifiedAccount;

            // Search for account
            for (Account &account : accountDatabase){

                if (account.label == accountToModify){
                    modifiedAccount = account;
                    foundAccount = true;
                    break;
                }
            }

            // Modify account
            if (foundAccount) {
                if (fieldToModify == "username") {
                    modifiedAccount.username = GetInput("New username:");

                } else if (fieldToModify == "password") {
                    std::string password1 = "x", password2 = "y";
                    while (password1 != password2) {
                        password1 = GetInput("New password:");
                        password2 = GetInput("Confirm new password:");
                        if (password1 == password2) {
                            auto hash = auth->Encrypt(password1);
                            auto encryptedPassword = hashToChars(hash);
                            modifiedAccount.hash = encryptedPassword;
                        } else {
                            PrintLine("Passwords do not match - try again.");
                        }
                        if (testMode) break;
                    }

                } else if (fieldToModify == "url") {
                    modifiedAccount.url = GetInput("New URL:");

                } else if (fieldToModify == "label") {
                    modifiedAccount.label = GetInput("New label:");

                } else if (fieldToModify == "expiry") {
                    PrintLine("NOT IMPLEMENTED YET");

                } else {
                    PrintLine("Invalid field entered - try again.");

                }

                // Updating time last modified and accessed
                long value_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::time_point_cast<std::chrono::milliseconds>(
                                std::chrono::high_resolution_clock::now()
                                ).time_since_epoch()
                                ).count();
                modifiedAccount.lastModified = value_ms;
                modifiedAccount.lastAccessed = value_ms;

                database->Update(modifiedAccount);
                PrintLine("Account successfully updated!");

            } else{
                std::ostringstream notFound;
                notFound << "Account " << accountToModify << " not found - please try again.";
                PrintLine(notFound.str());

            }

            success = true;

            if (testMode) break;
        }

    } else if (command == "view-accounts") {
        if (ctxManager.GetContext() != Main || !ctxManager.authenticated) {
            PrintLine("Please sign in before viewing accounts.");
            return;
        }
        std::vector<Account> userAccounts = database->GetAllAccountsByUserID(ctxManager.activeUserID);

		if (userAccounts.empty()) {
			PrintLine("No accounts! Type 'add-account' to add a new account.");
		} else {
			long value_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
	                std::chrono::time_point_cast<std::chrono::milliseconds>(
	                        std::chrono::high_resolution_clock::now()
	                        ).time_since_epoch()
	                        ).count();

			PrintLine("Your accounts:");

	        for (Account &account : userAccounts) {
				auto hash = charsToHash(account.hash);
			    auto decryptedPassword = auth->Decrypt(hash);
	            std::ostringstream accountLine;
	            accountLine << account.label << " - " << account.username << " (" << account.url << ") " << ": " << decryptedPassword;
	            PrintLine(accountLine.str());
	            account.lastAccessed = value_ms;
	        }
		}

    } else if (command == "quit") {
        PrintLine("Logged out.");
        ctxManager.authenticated = false;
        ctxManager.activeUserID = 0;
        ctxManager.quitting = true;
        return;

    } else if (command == "new-password") {
		std::string lengthStr = GetInput("How long would you like the password to be?");
		int length = std::stoi(lengthStr);
        std::string newPassword = rpg.NewPassword(length);
		PrintLine("New Password Generated: " + newPassword);

    } else if (command == "help") {
		PrintHelp();

    } else {
        PrintLine("Invalid command: " + command);
		PrintHelp();
    }
}


void CommandLine::PrintHelp()
{
	// TODO Determine context and print only the commands that are currently valid
	Print("Command list for Aletheia:\n");
	Print("  login\t\tLog in to the password manager\n");
	Print("  register\tCreate a new user profile\n");
	Print("  new-account\tCreate a new account entry\n");
	Print("  view-accounts\tView account information\n");
	Print("  edit-account\tEdit an existing account\n");
	Print("  new-password\tGenerate and view a random password\n");
	PrintLine("  quit\t\tLog out and exit Aletheia\n");
}

/**
 * cli.pp
 * Top level module containing implementations of handler functions for each user input
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>



#include "include/cli.h"
#include "network/EventBus.h"
#include "events/LoginAttemptEvent.h"
#include "network/HTTPServer.h"
#include "events/AccountCreateEvent.h"
#include "events/AccountUpdateEvent.h"
#include "include/Storage.h"
#include "include/cli/InputParser.h"


cli :: cli(int &argc, char **argv){
    std::vector<std::string> InputArg(argv +1, argv + argc);
    InputParser input(argc, argv);
}

bool CommandExists()
void cli :: HandleCommand() {
    //EventBus *bus = EventBus::GetInstance(); // Acquire EventBus to communicate

    if (input.IfCommandExists("/login")){ // Login command
        //bus ->Subscribe(this, &cli::HandleLogin); // Hardcoded for now to test login command
        int UserId = stoi(InputArg[1]);
        std::vector<Account> UserAccount = Storage::GetAllAccountsByUserID(UserId);

        if (UserAccount->pk == InputArg[2]){
            updateOutput("Login successful from user");
        }

        clearOutput();
        updateOutput("Login working????? ");
        printOutput();
    }

    if (input.IfCommandExists("/new-account")){
        //bus->Subscribe(this, &cli::HandleRegistration);
        updateOutput("Registration working????? ");
        printOutput();
    }

    if (input.IfCommandExists("/edit-account")){
        //bus->Subscribe(this, &cli::HandleUpdatingAccount);
        updateOutput("Updating account working????? ");
        printOutput();
    }
}

void cli::HandleLogin(LoginAttemptEvent *event){
    std::cout << "Attempting to login " << std::endl;
}

void cli::HandleRegistration(AccountCreateEvent *event) {
}

void cli::HandleUpdatingAccount(AccountUpdateEvent *event) {

}

std::string cli::GetInput() const {
    return input;
}

std::string cli::GetCommand() const{
    return command;
}

void cli::updateOutput(const std::string& Output) {
    output += Output;
}

std::string cli::GetOutput() {
    return output;
}
void clearOutput(){
    output = "";
}
void cli::printOutput() {
    std::cout << output << std::endl;
}


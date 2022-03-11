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
#include "network/HTTPServer.h"
#include "events/AccountCreateEvent.h"
#include "events/AccountUpdateEvent.h"
#include "Storage.h"


void CommandLine::HandleCommand() {

    if (CommandExists("login")){ // Login command
        // jeremy: I foresee a potential problem here with this, what if the user enters "aletheia garbage login"
        // should we not do something about the garbage input and tell the user about it?
        // int userId = std::stoi();
        // std::vector<Account> userAccount = Storage::GetAllAccountsByUserID(userId);

        // jeremy: The pk attribute belongs to one individual Account, not a vector of them
        // if (userAccount->pk == InputArg[2]){
        //     UpdateOutput("Login successful from user");
        // }

        // jeremy: look into C++ streams, they're much nicer for what you're doing here
        ClearOutput();
        UpdateOutput("Login working????? ");
        PrintOutput();
    }
    // jeremy: should this be else if? probably don't want to both log in and create a new account and edit an account
    // in the same command
    if (CommandExists("--new-account")){
        UpdateOutput("Registration working????? ");
        PrintOutput();
    }

    // jeremy: same comment as above
    if (CommandExists("--edit-account")){
        UpdateOutput("Updating account working????? ");
        PrintOutput();
    }
}

// jeremy: as I said above, look into C++ streams, they're much nicer for doing what you're trying to do here
// also, are you ever going to be needing another class to update the output? because if not you can just directly
// update the output variable since it belongs to this class
void CommandLine::UpdateOutput(const std::string& Output) {
    output += Output;
}

// jeremy: same comments as above
void CommandLine::ClearOutput(){
    output = "";
}

// jeremy: same comments as above
void CommandLine::PrintOutput() {
    std::cout << output << std::endl;
}


// main.cpp
// Contains the main entrypoint for the TBD password manager project.
// Authors: <insert here>

#include <iostream>

#include <tbd.h>
#include <tbd-crypto.h>
#include <tbd-storage.h>

#include <data/user.h>
#include <data/user-record.h>

using namespace data;

/**
 * Manages passwords
 */
int main(int argc, char *argv[])
{
    using std::cout, std::cerr, std::endl;

    db::Storage database("db.sqlite3");

    std::vector<std::string> args(argv, argv+argc);
    switch (argc) {
        case 0:
            cerr << "what" << endl;
        case 1:
            cerr << "No arguments provided!" << endl;
            return -1;
        case 2:
            if (args[1] == "help") {
                cout << "Usage:\n";
                cout << "\ttbd add <first-name> <last-Name>\n";
                cout << "\ttbd [get|remove] <ID>\n";
                cout << "\ttbd help\n";
                cout << endl;
            } else if (args[1] == "getall") {
                std::vector<User> allUsers = database.GetAllUsers();
                cout << "Users:\n";
                for (auto &user : allUsers) {
                    cout << "\t" << user.Name() << " (ID: " << user.ID() << ")\n";
                }
                cout << endl;
            } else {
                cerr << "Unknown arg list" << endl;
                return -1;
            }
            return 0;
        case 3:
            if (args[1] == "get") {
                std::unique_ptr<User> pUser = database.GetUserByID(std::stoi(args[2]));
                if (pUser != nullptr)
                    cout << "Retrieved user " << pUser->Name() << " with ID " << pUser->ID() << " from the db." << endl;
                else
                    cout << "User with ID " << args[2] << " does not exist in the db." << endl;
            } else if (args[1] == "remove") {
                database.RemoveUser(std::stoi(args[2]));
                cout << "Removed use with ID " << args[2] << " from the db." << endl;
            } else {
                cerr << "Invalid subcommand: " << args[1] << endl;
                return -1;
            }
            return 0;
        case 4:
            if (args[1] == "add") {
                User u = database.AddUser(args[2], args[3]);
                cout << "Added user " << u.Name() << " with ID " << u.ID() << endl;
            } else {
                cerr << "Invalid subcommand: " << args[1] << endl;
                return -1;
            }
            return 0;
        default:
            cout << "Usage:\n";
            cout << "\ttbd add <first-name> <last-Name>\n";
            cout << "\ttbd [get|remove] <ID>\n";
            cout << "\ttbd getall\n";
            cout << "\ttbd help\n";
            cout << endl;
            return -1;
    }

}

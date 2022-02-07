// main.cpp
// Contains the main entrypoint for the TBD password manager project.
// Authors: <insert here>

#include <stdio.h>

#include <tbd.h>
#include <tbd-crypto.h>
#include <tbd-storage.h>

/**
 * Manages passwords
 */
int main(int argc, char *argv[])
{
    puts("Hello, world!\n");

    sqlite3 *db;

    sqlite3Open("db.sqlite3", &db);

    std::vector<std::string> tcols, mcols;

    tcols.push_back("key PRIMARY KEY");
    tcols.push_back("value");

    mcols.push_back("ok PRIMARY KEY");
    mcols.push_back("go UNIQUE NOT NULL");
    
    createTable(db, "test", tcols);
    createTable(db, "make", mcols);

    return 0;
}


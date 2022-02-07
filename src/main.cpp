// main.cpp
// Contains the main entrypoint for the TBD password manager project.
// Authors: <insert here>

#include <tbd.h>
#include <tbd-crypto.h>
#include <tbd-storage.h>

/**
 * Manages passwords
 */
int main(int argc, char *argv[])
{
    puts("Hello, world!");

    db::Storage database("db.sqlite3");

    database.addUser("Jeremy", "Rempel");

    return 0;
}

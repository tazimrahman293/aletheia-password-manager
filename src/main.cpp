// main.cpp
// Contains the main entrypoint for the TBD password manager project.
// Authors: <insert here>

#include <tbd.h>
#include <tbd-crypto.h>
#include <tbd-storage.h>

inline auto initStorage(const std::string &db_filename)
{
    using namespace sqlite_orm;
    return make_storage(
            db_filename,
            make_table("users",
                       make_column("id", &User::id, primary_key(), autoincrement()),
                       make_column("first_name", &User::firstName),
                       make_column("last_name", &User::lastName),
                       make_column("type_id", &User::typeID)));
}
using Storage = decltype(initStorage(""));

/**
 * Manages passwords
 */
int main(int argc, char *argv[])
{
    puts("Hello, world!");

    Storage storage = initStorage("db.sqlite3");
    return 0;
}


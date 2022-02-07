#ifndef TBD_STORAGE_H
#define TBD_STORAGE_H

// Definitions, classes, and types specific to the storage functions go here

#include <string>

#include <sqlite3.h>
#include <sqlite_orm.h>

/////////////////////////
/* Basic DB Operations */
/////////////////////////

inline auto create_database(const std::string &db_filename) {
    using namespace sqlite_orm;
    return make_storage(
            db_filename,
            make_table(
                    "users",
                    make_column("id", &User::id, autoincrement(), primary_key()),
                    make_column("first_name", &User::firstName),
                    make_column("last_name", &User::lastName)
            )
    );
}
using Database = decltype(create_database(""));

class Storage {
    class _Storage;
    std::unique_ptr<_Storage> _s;

public:
    explicit Storage(const std::string &db_filename);
    ~Storage();
    // Add more db functionalities here
};

//////////////////////

#endif  // TBD_STORAGE_H

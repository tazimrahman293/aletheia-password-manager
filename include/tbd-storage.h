#ifndef TBD_STORAGE_H
#define TBD_STORAGE_H

// Definitions, classes, and types specific to the storage functions go here

#include <string>

#include <sqlite3.h>
#include <sqlite_orm.h>

#include <data/user.h>

/////////////////////////
/* Basic DB Operations */
/////////////////////////

namespace db {

    class Storage {
        class _Storage;
        std::unique_ptr<_Storage> _s;

    public:
        explicit Storage(const std::string &dbFilename);
        ~Storage();
        // Add more db functionalities here
        data::User addUser(const std::string &firstName, const std::string &lastName) noexcept;
    };

}  // namespace db

//////////////////////

#endif  // TBD_STORAGE_H

#ifndef TBD_STORAGE_H
#define TBD_STORAGE_H

// Definitions, classes, and types specific to the storage functions go here

#include <string>
#include <vector>

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

        data::User AddUser(const std::string &firstName, const std::string &lastName) noexcept;
        std::unique_ptr<data::User> GetUserByID(int id) noexcept;
        std::vector<data::User> GetAllUsers() noexcept;
        void RemoveUser(int id) noexcept;
    };

}  // namespace db

//////////////////////

#endif  // TBD_STORAGE_H

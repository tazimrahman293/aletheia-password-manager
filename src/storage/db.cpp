// db.cpp
// Contains wrapper function definitions for the use of the database storage for
// the TBD password manager project.
// Authors: Jeremy Rempel

#include <memory>

#include <tbd.h>
#include <tbd-storage.h>

class Storage::_Storage {
public:
    Database db;
    explicit _Storage(const std::string &db_filename) :
            db(create_database(db_filename))
    {
        db.sync_schema();
    }
};

Storage::Storage(const std::string &db_filename) :
        _s(std::make_unique<_Storage>(db_filename))
{ }

Storage::~Storage() = default;

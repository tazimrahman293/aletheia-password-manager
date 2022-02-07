#ifndef TBD_H
#define TBD_H

// Common definitions, classes, or types that are shared between many areas go here

#include <string>

class User {
    enum UserType {
        NORMAL,
        ADMIN,
        SUPERADMIN
    };
public:
    int id;
    std::string firstName;
    std::string lastName;
    UserType typeID;
};

#endif  // TBD_H

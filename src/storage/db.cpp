// db.cpp
// Contains wrapper function definitions for the use of the database storage for
// the TBD password manager project.
// Authors: Jeremy Rempel

#include <stdio.h>

#include <sqlite3.h>

#include <tbd.h>
#include <tbd-storage.h>


/////////////////////
/* SQLite3 Wrappers */
/////////////////////


/**
 * Wraps the sqlite3_open() function with error-handling.
 */
int sqlite3Open(const char *filename, sqlite3 **pp_db)
{
    if (sqlite3_open(filename, pp_db) != 0) {
        fprintf(stderr, "Unable to open database: %s\n", sqlite3_errmsg(*pp_db));
        sqlite3_close(*pp_db);
        return -1;
    }
    return 0;
}


/**
 * Wraps the sqlite3_exec() function with error-handling.
 */
int sqlite3Exec(sqlite3 *db, const char *sql, 
                int (*callback)(void *, int, char **, char **), void *cb_arg,
                char **errmsg) {
    if (sqlite3_exec(db, sql, callback, cb_arg, errmsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", *errmsg);
        sqlite3_free(*errmsg);
        return -1;
    }
    return 0;
}


/**
 * Wraps the sqlite3_close() function with error-handling.
 */
int sqlite3Close(sqlite3 *p_db)
{
    if (sqlite3_close(p_db) != SQLITE_OK) {
        fprintf(stderr, "Unable to close database: %s\n", sqlite3_errmsg(p_db));
        return -1;
    }
    return 0;
}


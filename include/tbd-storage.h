#ifndef TBD_STORAGE_H
#define TBD_STORAGE_H

// Definitions, classes, and types specific to the storage functions go here

#include <sqlite3.h>

//////////////////////
/* SQLite3 Wrappers */
//////////////////////

int sqlite3Open(const char *filename, sqlite3 **pp_db);
int sqlite3Exec(sqlite3 *db, const char *sql,
                int (*callback)(void *, int, char **, char **), void *cb_arg,
                char **errmsg);
int sqlite3Close(sqlite3 *p_db);

//////////////////////

#endif  // TBD_STORAGE_H

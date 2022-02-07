#ifndef TBD_STORAGE_H
#define TBD_STORAGE_H

// Definitions, classes, and types specific to the storage functions go here

#include <cstdio>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>

#include <sqlite3.h>

#define TBD_CONFLICT "DO NOTHING"

/////////////////////////
/* Basic DB Operations */
/////////////////////////

int createTable(sqlite3 *db, std::string table_name, std::vector<std::string> cols);

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

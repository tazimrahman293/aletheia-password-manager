// storage.cpp
// Contains top-level function definitions for storing and retrieving persistent data 
// for the TBD password manager project.
// Authors: Jeremy Rempel

#include <sqlite3.h>

#include <tbd.h>
#include <tbd-storage.h>

// int sql_cb(void *arg, int num_cols, char **col_data, char **col_names) {
//     printf("Num Cols: %d\tCol data[0]: %s\tCol names[0]: %s\n", num_cols, 
//            col_data[0], col_names[0]);
// 
//     return 0;
// }
// 
// sqlite3 *db;
// 
// char *err = 0;
// int rc;
// 
// rc = sqlite3_open("db.sqlite3", &db);
// if (rc != 0) {
//     fprintf(stderr, "Unable to open database: %s\n", sqlite3_errmsg(db));
//     sqlite3_close(db);
//     return 1;
// } else {
//     puts("Able to open database: db.sqlite3");
// }
// 
// rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS test(k PRIMARY KEY, v);", sql_cb, 0, &err);
// if (rc != SQLITE_OK) {
//     fprintf(stderr, "SQL error: %s\n", err);
//     sqlite3_free(err);
// } else {
//     puts("OK!");
// }
// 
// sqlite3_close(db);


// db.cpp
// Contains wrapper function definitions for the use of the database storage for
// the TBD password manager project.
// Authors: Jeremy Rempel

#include <sstream>

#include <tbd.h>
#include <tbd-storage.h>

using str = std::string;

template<class T>
using vec = std::vector<T>;

template<class K, class V>
using umap = std::unordered_map<K,V>;

///////////////////////
/* Utility Functions */
///////////////////////

str joinVector(vec<str> data, str delim)
{
    str result = "";
    for (vec<str>::iterator it = data.begin(); it != data.end(); ++it) {
        result += *it;
        if (it+1 != data.end())
            result += delim;
    }
    return result;
}

/////////////////////////
/* Basic DB Operations */
/////////////////////////

/**
 * Creates a new table in an existing database file.
 * @param sqlite3 *db The database connection object instance
 * @param string table_name The name to assign this new table
 * @param vector<string> cols A vector of strings with column definitions
 * @return SQLITE_OK if the operation succeeds, or the appropriate error code
 *   (see https://www.sqlite.org/rescode.html for a list)
 */
int createTable(sqlite3 *db, str table_name, vec<str> col_names)
{
    std::stringstream s_sql;
    str sql, cols;
    char *err;

    cols = joinVector(col_names, ",");

    s_sql << "CREATE TABLE IF NOT EXISTS " << table_name;
    s_sql << " (" << cols << ")" << std::ends;
    sql = s_sql.str();

    return sqlite3Exec(db, sql.c_str(), NULL, NULL, &err);
}


/**
 * Inserts a new row into an existing table.
 * @param sqlite3 *db The database connection object instance
 * @param string table_name The name of the table to insert into
 * @param unordered_map<string,string> row_data A key-value map of column names and 
 *   data values to insert at those columns
 * @return SQLITE_OK if the operation succeeds, or the appropriate error code
 *   (see https://www.sqlite.org/rescode.html for a list)
 */
int insertRow(sqlite3 *db, str table_name, umap<str,str> row_data)
{
    std::stringstream s_sql;
    str sql, cols, data;
    vec<str> col_vec, data_vec;
    char *err;

    for (umap<str,str>::iterator it = row_data.begin(); it != row_data.end(); ++it) {
        col_vec.push_back(it->first);
        data_vec.push_back(it->second);
    }
    cols = joinVector(col_vec, ",");
    data = joinVector(data_vec, ",");

    s_sql << "INSERT INTO " << table_name;
    s_sql << " (" << cols << ") VALUES";
    s_sql << " (" << data << ")";
    s_sql << " ON CONFLICT " << TBD_CONFLICT << std::ends;
    sql = s_sql.str();

    return sqlite3Exec(db, sql.c_str(), NULL, NULL, &err);
}


//////////////////////
/* SQLite3 Wrappers */
//////////////////////

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
    int rc;
    if ((rc = sqlite3_exec(db, sql, callback, cb_arg, errmsg)) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", *errmsg);
        sqlite3_free(*errmsg);
        return rc;
    }
    return SQLITE_OK;
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


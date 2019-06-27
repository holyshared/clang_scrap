#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sqlite3.h>
#include <stdbool.h>
#include <unistd.h>
#include "db.h"


static int file_exists(const char* path) {
    struct stat st;

    if (stat(path, &st) == -1) {
        return false;
    }

    return (st.st_mode & S_IFMT) == S_IFREG;
}

int db_create(sqlite3 **db, const char *name) {
    if (file_exists(name)) {
        unlink(name);
    }

    if (SQLITE_OK != sqlite3_open(name, db)) {
        return DB_ERROR;
    }

    return DB_OK;
}


int db_setup(sqlite3 *db) {
    char *errmsg = NULL;
    const char *sql = "create table users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT)";

    if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg)) {
        return DB_ERROR;
    }

    return DB_OK;
}

int db_cleanup(sqlite3 *db) {
    if (SQLITE_OK != sqlite3_close(db)) {
        return DB_ERROR;
    }

    return DB_OK;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "../string/ext_string.h"
#include "user.h"
#include "db.h"

#define DB_FILE "./example.db"


int main(void) {
    int ret = 0;
    sqlite3 *db = NULL;

    if (DB_ERROR == db_create(&db, DB_FILE)) {
        printf("Create database file failed\n");
        return EXIT_FAILURE;
    }

    if (DB_ERROR == db_setup(db)) {
        printf("Setup database file failed\n");
        return EXIT_FAILURE;
    }

    struct user users[5] = {
        {"A1", "a@email.com"},
        {"B2", "b@email.com"},
        {"C3", "c@email.com"},
        {"D4", "d@email.com"},
        {"E5", "e@email.com"}
    };

    ret = insert_users(db, users, 5);
    if (SQLITE_OK == ret) {
        printf("done: users added\n");
    }

    const char *names[] = { "A1", "B2" };
    size_t len = sizeof(names)/sizeof(names[0]);

    ret = find_users_by_names(db, names, len);
    if (SQLITE_OK == ret) {
        printf("done: find users\n");
    }

    if (DB_ERROR == db_cleanup(db)) {
        printf("Setup database file failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

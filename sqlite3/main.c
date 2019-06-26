#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "../string/ext_string.h"
#include "user.h"

#define DB_FILE "./example.db"

int main(void) {
    sqlite3 *db = NULL;
    char *errmsg = NULL;

    int ret = sqlite3_open(DB_FILE, &db);

    if (SQLITE_OK == ret) {
        printf("File %s opened\n", DB_FILE);
    }

    ret = sqlite3_exec(db, "create table users (name string, email string)", NULL, NULL, &errmsg);
    if (SQLITE_OK == ret) {
        printf("Create users table\n");
    }

    // memo
    ret = sqlite3_exec(db, "create table groups (name", NULL, NULL, &errmsg);
    if (SQLITE_ERROR == ret) {
        printf("Create groups table error\n");
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

    ret = sqlite3_close(db);

    if (SQLITE_OK == ret) {
        printf("File %s closed\n", DB_FILE);
    }
}

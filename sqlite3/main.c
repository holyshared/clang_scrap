#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define DB_FILE "./example.db"

struct user {
    char name[256];
    char email[256];
};

int insert_users(sqlite3 *db) {
    sqlite3_stmt *stmt = NULL;
    const char *pzTest;

    const char *sql = "insert into users (name, email) values (?, ?)";

    int ret = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &pzTest);

    struct user users[5] = {
        {"A", "a@email.com"},
        {"B", "b@email.com"},
        {"C", "c@email.com"},
        {"D", "d@email.com"},
        {"E", "e@email.com"}
    };

    for (int i = 0; i < 5; i++) {
        ret = sqlite3_bind_text(stmt, 1, users[i].name, strlen(users[i].name), SQLITE_TRANSIENT);
        if (ret == SQLITE_OK) {
            printf("name paramater binded\n");
        }

        ret = sqlite3_bind_text(stmt, 2, users[i].email, strlen(users[i].email), SQLITE_TRANSIENT);
        if (ret == SQLITE_OK) {
            printf("email paramater binded\n");
        }

        ret = sqlite3_step(stmt);
        if (ret == SQLITE_DONE) {
            printf("add record to users\n");
        }

        ret = sqlite3_reset(stmt);
        if (ret == SQLITE_OK) {
            printf("add record to users\n");
        }
    }

    ret = sqlite3_finalize(stmt);
    if (ret == SQLITE_OK) {
        printf("clean up stmt\n");
    }

    return ret;
}


int find_users(sqlite3 *db) {
    printf("find_users------------------------\n");

    sqlite3_stmt *stmt = NULL;

    const char *names[2] = { "A", "B" };
    char conditions[] = "";

    printf("build conditions------------------------\n");

    for (int i = 0; i < 1; i++) {
        char placeholder_with[] = "?, ";
        printf("strcat conditions------------------------\n");
        strcat(conditions, placeholder_with);
        printf("strcat conditions end------------------------\n");
    }
    char placeholder[] = "?";
    strcat(conditions, placeholder);

    printf("conditions: %s\n", conditions);

    const char *pzTest;
    char sql[200] = { "select * from users where name in (\0" };

    strcat(sql, conditions);
    strcat(sql, ")");


    int ret = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &pzTest);

    if (ret != SQLITE_OK) {
        printf("%s\n", sql);
        return SQLITE_ERROR;
    }

    for (int j = 0; j < 2; j++) {
        ret = sqlite3_bind_text(stmt, j + 1, names[j], strlen(names[j]), SQLITE_TRANSIENT);
        if (ret != SQLITE_OK) {
            return sqlite3_finalize(stmt);
        }
    }

    while ((ret = sqlite3_step(stmt)) && ret == SQLITE_ROW) {
        const unsigned char *r_name = sqlite3_column_text(stmt, 0);
        int r_name_bytes = sqlite3_column_bytes(stmt, 0);

        const unsigned char *r_email = sqlite3_column_text(stmt, 1);
        int r_email_bytes = sqlite3_column_bytes(stmt, 1);

        printf("%d %d\n", r_name_bytes, r_email_bytes);
        printf("%s %s\n", r_name, r_email);
    }

    if (ret != SQLITE_DONE) {
        printf("query error\n");
    }

    return sqlite3_finalize(stmt);
}


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

    ret = sqlite3_exec(db, "create table groups (name", NULL, NULL, &errmsg);
    if (SQLITE_ERROR == ret) {
        printf("Create groups table error\n");
    }

    ret = insert_users(db);
    if (SQLITE_OK == ret) {
        printf("users added\n");
    }

    ret = find_users(db);
    if (SQLITE_OK == ret) {
        printf("find users\n");
    }

    ret = sqlite3_close(db);

    if (SQLITE_OK == ret) {
        printf("File %s closed\n", DB_FILE);
    }
}

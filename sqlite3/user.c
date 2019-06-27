#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "../string/ext_string.h"
#include "user.h"


int insert_users(sqlite3 *db, struct user users[], size_t u_len) {
    sqlite3_stmt *stmt = NULL;
    const char *pzTest;
    const char *sql = "insert into users (name, email) values (?, ?)";

    int ret = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &pzTest);
    if (ret != SQLITE_OK) {
        printf("sql error: %s\n", sql);
        return SQLITE_ERROR;
    }

    int result = SQLITE_OK;

    for (int i = 0; i < u_len; i++) {
        ret = sqlite3_bind_text(stmt, 1, users[i].name, strlen(users[i].name), SQLITE_TRANSIENT);
        if (ret != SQLITE_OK) {
            printf("name paramater bind error\n");
            result = SQLITE_ERROR;
            break;
        }

        ret = sqlite3_bind_text(stmt, 2, users[i].email, strlen(users[i].email), SQLITE_TRANSIENT);
        if (ret != SQLITE_OK) {
            printf("email paramater bind error\n");
            result = SQLITE_ERROR;
            break;
        }

        ret = sqlite3_step(stmt);
        if (ret != SQLITE_DONE) {
            printf("record insert error\n");
            result = SQLITE_ERROR;
            break;
        }

        ret = sqlite3_reset(stmt);
        if (ret != SQLITE_OK) {
            result = SQLITE_ERROR;
            break;
        }
    }

    ret = sqlite3_finalize(stmt);
    if (ret == SQLITE_OK) {
        printf("clean up stmt\n");
    }

    return result;
}



int find_users_by_names(sqlite3 *db, const char *names[], size_t len) {
    sqlite3_stmt *stmt = NULL;

    const char *pzTest;
    char sql[200] = "";

    strcat(sql, "select * from users where name in (");
    str_repeat_join(sql, "?", ", ", len);
    strcat(sql, ")");

    int ret = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &pzTest);

    if (ret != SQLITE_OK) {
        printf("sql error: %s\n", sql);
        return SQLITE_ERROR;
    }

    for (int j = 0; j < len; j++) {
        ret = sqlite3_bind_text(stmt, j + 1, names[j], strlen(names[j]), SQLITE_TRANSIENT);
        if (ret != SQLITE_OK) {
            return sqlite3_finalize(stmt);
        }
    }

    while ((ret = sqlite3_step(stmt)) && ret == SQLITE_ROW) {
        const int r_id = sqlite3_column_int(stmt, 0);
        int r_id_bytes = sqlite3_column_bytes(stmt, 0);

        const unsigned char *r_name = sqlite3_column_text(stmt, 1);
        int r_name_bytes = sqlite3_column_bytes(stmt, 1);

        const unsigned char *r_email = sqlite3_column_text(stmt, 2);
        int r_email_bytes = sqlite3_column_bytes(stmt, 2);

        printf("%d %d %d\n", r_id_bytes, r_name_bytes, r_email_bytes);
        printf("%d %s %s\n", r_id, r_name, r_email);
    }

    if (ret != SQLITE_DONE) {
        printf("query error\n");
    }

    return sqlite3_finalize(stmt);
}

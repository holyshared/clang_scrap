struct user {
    char name[256];
    char email[256];
};

int insert_users(sqlite3 *db, struct user users[], size_t u_len);
int find_users_by_names(sqlite3 *db, const char *names[], size_t len);

#include <sqlite3.h>

#define DB_OK 1
#define DB_ERROR -1

int db_create(sqlite3 **db, const char *name);
int db_setup(sqlite3 *db);
int db_cleanup(sqlite3 *db);

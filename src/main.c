#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crud_functions.h"


sqlite3 *db;
int rc;

int main(int argc, char *argv[]) {
    char db_path[256];
    snprintf(db_path, sizeof(db_path), "%s/.tasks.db", getenv("HOME"));

    rc = sqlite3_open(db_path, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    char date_str[100];
    get_current_date(date_str, sizeof(date_str));

    create_task_table(db, rc);


    char task_name[100], new_task_name[100], priority[100], create_date[100];
    char input[10];

    if (argc == 1 || strcmp(argv[1], "-h") == 0) {
        printf("Welcome to Task Manager\n");
        print_help();
    }

    else if (argc == 4 && strcmp(argv[1], "-i") == 0) {
        // task name and priority
        insert_task(db, rc,argv[2], argv[3], date_str);
    }

    else if (argv[1] != NULL && strcmp(argv[1], "-v") == 0) {
        visualize_tasks(db, rc);
    }

    else if (argv[1] != NULL && strcmp(argv[1], "-u") == 0) {
        fetch_task_name(db, rc, argv[2], argv[3]);
    }

    else if (argv[1] != NULL && strcmp(argv[1], "-p") == 0) {
        fetch_task_priority(db, rc, argv[2], argv[3]);
    }

    else if (argv[1] != NULL && strcmp(argv[1], "-d") == 0) {
        delete_task(db, rc, argv[2]);
    }

    else {
        printf("Invalid arguments\n");
        print_help();
    }
}

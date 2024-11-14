//
// Created by boreges on 14/11/24.
//

#ifndef CRUD_FUNCTIONS_H
#define CRUD_FUNCTIONS_H
#include <sqlite3.h>
#include <time.h>

void create_task_table(sqlite3 *db, int rc);
void insert_task(sqlite3 *db, int rc, const char *task_name, const char *priority, const char *create_date);
void visualize_tasks(sqlite3 *db, int rc);
void fetch_task_name(sqlite3 *db, int rc, char *task_name, char *new_task_name);
void fetch_task_priority(sqlite3 *db, int rc, const char *task_name, const char *new_task_priority);
void delete_task(sqlite3 *db, int rc, const char *task_name);
void get_current_date(char *date_str, size_t max_size);
void clear_screen();
void print_help();

#endif //CRUD_FUNCTIONS_H

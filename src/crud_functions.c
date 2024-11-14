//
// Created by boreges on 14/11/24.
//

#include "crud_functions.h"

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void create_task_table(sqlite3 *db, int rc)
{
  const char *task_table = "CREATE TABLE IF NOT EXISTS tasks ("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "task_name TEXT UNIQUE NOT NULL,"
                           "priority TEXT NOT NULL,"
                           "create_date TEXT NOT NULL);";


  rc = sqlite3_exec(db, task_table, 0, 0, 0);

  if (rc != SQLITE_OK)
  {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  }
}

void insert_task(sqlite3 *db, int rc, const char *task_name, const char *priority, const char *create_date)
{

    char sql_create_task[100];

    sprintf(sql_create_task, "INSERT INTO tasks (task_name, priority, create_date)"
                            "VALUES ('%s', '%s', '%s');", task_name, priority, create_date);

  rc = sqlite3_exec(db, sql_create_task, 0, 0, 0);

  if (rc != SQLITE_OK)
  {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  }
}


void visualize_tasks(sqlite3 *db, int rc)
{
    sqlite3_stmt *stmt;
  const char *sql_visualize_tasks = "SELECT * FROM tasks";

    rc = sqlite3_prepare_v2(db, sql_visualize_tasks, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
    printf("Task Name| Priority| Create Date\n\n");
    while(rc = sqlite3_step(stmt) == SQLITE_ROW)
    {
        printf("%s| %s| %s\n", sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3));
    }

    sqlite3_finalize(stmt);

}


void fetch_task_name(sqlite3 *db, int rc, char *task_name, char *new_task_name)
{
  char sql_fetch_task[100];
  sprintf(sql_fetch_task, "UPDATE tasks SET task_name = '%s' WHERE task_name == '%s';", new_task_name, task_name);


  rc = sqlite3_exec(db, sql_fetch_task, 0, 0, 0);

  if (rc != SQLITE_OK)
  {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  }
}

void fetch_task_priority(sqlite3 *db, int rc, const char *task_name, const char *new_task_priority)
{
    char sql_fetch_task[100];

    sprintf(sql_fetch_task, "UPDATE tasks SET priority = '%s' WHERE task_name == '%s';", new_task_priority, task_name);


    rc = sqlite3_exec(db, sql_fetch_task, 0, 0, 0);

  if (rc != SQLITE_OK)
  {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  }
}

void delete_task(sqlite3 *db, int rc, const char *task_name)
{
    char sql_delete_task[100];
    sprintf(sql_delete_task, "DELETE FROM tasks WHERE task_name = '%s';", task_name);

    rc = sqlite3_exec(db, sql_delete_task, 0, 0, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
}


void get_current_date(char *date_str, size_t max_size) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    snprintf(date_str, max_size, "%02d/%02d/%04d", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_help() {
    printf("Usage: task_manager [OPTION] [ARGS...]\n");
    printf("Options:\n");
    printf("  -h                Show this help message\n");
    printf("  -i <task> <prio>  Add a new task with name <task> and priority <prio>\n");
    printf("  -v                View all tasks\n");
    printf("  -u <old> <new>    Update task name from <old> to <new>\n");
    printf("  -p <task> <prio>  Update task priority for <task> to <prio>\n");
    printf("  -d <task>         Delete task with name <task>\n");

}
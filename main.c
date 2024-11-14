#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


sqlite3 *db;
int rc;

void create_task_table()
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

void insert_task(const char *task_name, const char *priority, const char *create_date)
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


void visualize_tasks()
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


void fetch_task_name(char *task_name, char *new_task_name)
{
  char sql_fetch_task[100];
  sprintf(sql_fetch_task, "UPDATE tasks SET task_name = '%s' WHERE task_name == '%s';", new_task_name, task_name);


  rc = sqlite3_exec(db, sql_fetch_task, 0, 0, 0);

  if (rc != SQLITE_OK)
  {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  } 
}

void fetch_task_priority(const char *task_name, const char *new_task_priority)
{
    char sql_fetch_task[100];

    sprintf(sql_fetch_task, "UPDATE tasks SET priority = '%s' WHERE task_name == '%s';", new_task_priority, task_name);


    rc = sqlite3_exec(db, sql_fetch_task, 0, 0, 0);

  if (rc != SQLITE_OK)
  {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  }
}

void delete_task(const char *task_name)
{
    char sql_delete_task[100];
    sprintf(sql_delete_task, "DELETE FROM tasks WHERE task_name = '%s';", task_name);

    rc = sqlite3_exec(db, sql_delete_task, 0, 0, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
}

void print_menu() {
    printf("1. Create Task\n");
    printf("2. View Tasks\n");
    printf("3. Update Task Name\n");
    printf("4. Update Task Priority\n");
    printf("5. Delete Task\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
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
    printf("  -i <task> <prio>     Add a new task with name <task> and priority <prio>\n");
    printf("  -v                View all tasks\n");
    printf("  -u <old> <new>    Update task name from <old> to <new>\n");
    printf("  -p <task> <prio>  Update task priority for <task> to <prio>\n");
    printf("  -d <task>         Delete task with name <task>\n");

}

int main(int argc, char *argv[]) {
    rc = sqlite3_open("tasks.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    char date_str[100];
    get_current_date(date_str, sizeof(date_str));

    create_task_table();


    char task_name[100], new_task_name[100], priority[100], create_date[100];
    char input[10];

    if (argc == 1 || strcmp(argv[1], "-h") == 0) {
        printf("Welcome to Task Manager\n");
        print_help();
    }

    else if (argc == 4 && strcmp(argv[1], "-i") == 0) {
        // task name and priority
        insert_task(argv[2], argv[3], date_str);
    }

    else if (argv[1] != NULL && strcmp(argv[1], "-v") == 0) {
        visualize_tasks();
    }

    else if (argv[1] != NULL && strcmp(argv[1], "-u") == 0) {
        fetch_task_name(argv[2], argv[3]);
    }

    else if (argv[1] != NULL && strcmp(argv[1], "-p") == 0) {
        fetch_task_priority(argv[2], argv[3]);
    }

    else if (argv[1] != NULL && strcmp(argv[1], "-d") == 0) {
        delete_task(argv[2]);
    }

    else {
        printf("Invalid arguments\n");
        print_help();
    }
}
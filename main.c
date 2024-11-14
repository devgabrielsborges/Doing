#include <stdio.h>
#include <sqlite3.h>


sqlite3 *db;
int rc;

void create_task_table()
{
  const char *task_table = "CREATE TABLE IF NOT EXISTS tasks ("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "task_name TEXT NOT NULL,"
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
                            "VALUES (%s, %s, %s);", task_name, priority, create_date);

  rc = sqlite3_exec(db, sql_create_task, 0, 0, 0);

  if (rc != SQLITE_OK)
  {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  } 
}


void visualize_tasks()
{
  const char *sql_visualize_tasks = "SELECT * FROM tasks";


  rc = sqlite3_exec(db, sql_visualize_tasks, 0, 0, 0);

  if (rc != SQLITE_OK)
  {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  } 
}


void fetch_task_name(char *task_name, char *new_task_name)
{
  char sql_fetch_task[100];
  sprintf(sql_fetch_task, "UPDATE tasks SET task_name = %s WHERE task_name == %s", new_task_name, task_name);


  rc = sqlite3_exec(db, sql_fetch_task, 0, 0, 0);

  if (rc != SQLITE_OK)
  {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  } 
}

void fetch_task_priority(const char *task_priority, const char *new_task_priority)
{
    char sql_fetch_task[100];

    sprintf(sql_fetch_task, "UPDATE tasks SET priority = %s WHERE priority == %s", task_priority, new_task_priority);


  rc = sqlite3_exec(db, sql_fetch_task, 0, 0, 0);

  if (rc != SQLITE_OK)
  {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
  } 
}

void delete_task(const char *task_name)
{
    char sql_delete_task[100];
    sprintf(sql_delete_task, "DELETE FROM tasks WHERE name = %s", task_name);
}

int main(int argc, char *argv)
{
  rc = sqlite3_open("tasks.db", &db);

  if (rc) 
  {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
  }
    create_task_table();

    visualize_tasks();


    insert_task("Emprestimo", "High", "13/11/2024");


    visualize_tasks();

}

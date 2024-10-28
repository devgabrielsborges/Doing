#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// TODO: Implement the deleteTask function
// TODO: Debug view tasks function

typedef struct {
    int id;
    char name[50];
    char status[10];
    char timestamp[12];
} task;

int getMenuCondition();
int generateTaskID(FILE *tasks);
int createTask(FILE *tasks);
int updateTask(FILE *tasks, int task_id);
int deleteTask(FILE *tasks, int task_id);
void viewTasks(FILE *tasks);
void clearScreen();

int main(void) {
    FILE *tasks = fopen("tasks.doing", "a+b");
    if (tasks == NULL) {
        perror("Failed to open tasks file");
        return 1;
    }

    int *target_id;

    printf("Welcome to Doing!\n\n");

    while (1) {
        switch (getMenuCondition()) {
            case 1:
                createTask(tasks);
                break;
            case 2:
                printf("Enter the task ID to update:\n");
                scanf("%d", &target_id);

                updateTask(tasks, target_id);
                break;
            case 3:
                printf("Enter the task ID to update:\n");
                scanf("%d", &target_id);

                deleteTask(tasks, target_id);
                break;
            case 4:
                viewTasks(tasks);
                break;
            default:
                printf("Exiting...\n");
                fclose(tasks);
                clearScreen();
                return 0;
        }
    }
}

int getMenuCondition() {
    int condition;

    printf("[1] Create task  [2] Update task  [3] Delete task  [4] View tasks  [5] Exit\n");
    scanf("%d", &condition);

    while (getchar() != '\n');  // Clear the input buffer

    return condition;
}

int generateTaskID(FILE *tasks)
{
    task user_task;
    int max_id = 0;

    rewind(tasks);

    while(fread(&user_task, sizeof(task), 1, tasks) == 1) {
        if (user_task.id > max_id) {
            max_id = user_task.id;
        }
    }

    return max_id + 1; // Return the next ID
}

int createTask(FILE *tasks) {
    task user_task;

    user_task.id = generateTaskID(tasks);
    // Getting the task name
    printf("Task name:\n");
    fgets(user_task.name, sizeof(user_task.name), stdin);
    user_task.name[strcspn(user_task.name, "\n")] = '\0';

    // Defining the task status and timestamp
    strcpy(user_task.status, "To do");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(user_task.timestamp, sizeof(user_task.timestamp), "%02d/%02d/%04d", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);
    printf("Task '%s' created on: %s\n", user_task.name, user_task.timestamp);

    // Writing the task to the file
    fseek(tasks, 0, SEEK_END);  // Move the file pointer to the end of the file
    fwrite(&user_task, sizeof(task), 1, tasks); // Write the task to file
    fflush(tasks); // Flush the buffer

    return 0;
}


void viewTasks(FILE *tasks) {
    task user_task;
    rewind(tasks);  // Move the file pointer to the beginning of the file

    printf("Tasks:\n\n");
    printf("ID | Name | Status | Date\n");
    while (fread(&user_task, sizeof(task), 1, tasks) == 1) {  // Read the tasks from the file
        printf(" %d | %s | %s | %s\n", user_task.id, user_task.name, user_task.status, user_task.timestamp);
    }
    printf("\n");
}

int updateTask(FILE *tasks, int task_id)
{
    task user_task;
    int found = 0;

    rewind(tasks);

    // Search for the task
    while (fread(&user_task, sizeof(task), 1, tasks) == 1)
    {
        if (user_task.id == task_id)
        {
            found = 1;

            printf("Enter the new task name: (leave empty to keep current)\n");
            fgets(user_task.name, sizeof(user_task.name), stdin);
            if (strcmp(user_task.name, "\n"))
            {
                strcpy(user_task.name, "");
            }
            else
            {
                user_task.name[strcspn(user_task.name, "\n")] = '\0';
            }

            printf("Enter new status (To do, In progress, Done):\n");
            fgets(user_task.status, sizeof(user_task.status), stdin);
            user_task.status[strcspn(user_task.status, "\n")] = '\0';

            // Mover o ponteiro para a posição anterior e atualizar a tarefa
            fseek(tasks, -sizeof(task), SEEK_CUR);
            fwrite(&user_task, sizeof(task), 1, tasks);
            fflush(tasks);
            printf("Task updated successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("Task not found!\n");
    }

    return found;
}


int deleteTask(FILE *tasks, int task_id)
{

}

void clearScreen() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // (Linux/Mac)
    #endif
}

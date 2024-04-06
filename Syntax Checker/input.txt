#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 10

typedef enum {
    LOW,
    MEDIUM,
    HIGH
} Priority;

typedef struct {
    char description[100];
    Priority priority;
    char dueDate[20];
    int completed;
} Task;

void displayMenu() {
    printf("\n\n\t\tTO-DO LIST\n");
    printf("\t\t==================================\n\n");
    printf("\t1. Add Task\n");
    printf("\t2. View Tasks\n");
    printf("\t3. Mark Task as Completed\n");
    printf("\t4. Exit\n\n");
    printf("\tEnter your choice: ");
}

void addTask(Task tasks[], int *numTasks) {
    if (*numTasks >= MAX_TASKS) {
        printf("\n\tMaximum number of tasks reached!\n");
        return;
    }
    
    printf("\n\tEnter task description: ");
    getchar(); // Clear input buffer
    fgets(tasks[*numTasks].description, sizeof(tasks[*numTasks].description), stdin);
    tasks[*numTasks].description[strcspn(tasks[*numTasks].description, "\n")] = '\0'; // Remove newline character
    
    printf("\tEnter task priority (0 - Low, 1 - Medium, 2 - High): ");
    scanf("%d", (int *)&tasks[*numTasks].priority);
    
    printf("\tEnter due date (YYYY-MM-DD): ");
    scanf("%s", tasks[*numTasks].dueDate);
    
    tasks[*numTasks].completed = 0; // Task is initially not completed
    (*numTasks)++;
    printf("\n\tTask added successfully!\n");
}

void viewTasks(Task tasks[], int numTasks) {
    if (numTasks == 0) {
        printf("\n\tNo tasks available!\n");
        return;
    }
    
    printf("\n\tTO-DO LIST\n");
    printf("\t==================================\n\n");
    
    for (int i = 0; i < numTasks; i++) {
        printf("\t%d. %s (Priority: %s, Due: %s) %s\n", 
            i + 1, tasks[i].description, 
            tasks[i].priority == LOW ? "Low" : (tasks[i].priority == MEDIUM ? "Medium" : "High"),
            tasks[i].dueDate,
            tasks[i].completed ? "(Completed)" : "");
    }
}

void markCompleted(Task tasks[], int numTasks) {
    if (numTasks == 0) {
        printf("\n\tNo tasks available!\n");
        return;
    }
    
    int taskNumber;
    printf("\n\tEnter task number to mark as completed: ");
    scanf("%d", &taskNumber);
    
    if (taskNumber < 1 || taskNumber > numTasks) {
        printf("\n\tInvalid task number!\n");
        return;
    }
    
    tasks[taskNumber - 1].completed = 1;
    printf("\n\tTask marked as completed!\n");
}

int main() {
    Task tasks[MAX_TASKS];
    int numTasks = 0;
    int choice;
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addTask(tasks, &numTasks);
                break;
            case 2:
                viewTasks(tasks, numTasks);
                break;
            case 3:
                markCompleted(tasks, numTasks);
                break;
            case 4:
                printf("\n\tExiting program...\n\n");
                break;
            default:
                printf("\n\tInvalid choice! Please try again.\n");
                break;
        }
    } while (choice != 4);
    
    return 0;
}

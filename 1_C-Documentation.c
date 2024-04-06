#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <unistd.h> // for usleep function (Unix/Linux)

// Define color constants
#define BLACK           0
#define BLUE            1
#define GREEN           2
#define CYAN            3
#define RED             4
#define MAGENTA         5
#define BROWN           6
#define LIGHTGRAY       7
#define DARKGRAY        8
#define LIGHTBLUE       9
#define LIGHTGREEN      10
#define LIGHTCYAN       11
#define LIGHTRED        12
#define LIGHTMAGENTA    13
#define YELLOW          14
#define WHITE           15

// Structure to represent a topic
typedef struct {
    char *name;
    char *description;
    void (*displayFunction)();
} Topic;

// Function prototypes
void showHelp();
void showTopic(char *topicName);
void unknownCommand();
void showAllTopics();
void searchTopic(char *searchTerm);
void showVariables();
void showOperators();
void showControlFlow();
void showFunctions();
void showPointers();
void showArrays();
void showStructures();
void showMemoryAllocation();
void showFileIO();
void showRecursion();
void showDynamicArrays();
void displayTextWithDelay(char *text, int delay);
void setColor(int textColor, int bgColor);

// Array of available topics
Topic topics[] = {
    {"variables", "Information about variables", showVariables},
    {"operators", "Information about operators", showOperators},
    {"controlflow", "Information about control flow", showControlFlow},
    {"functions", "Information about functions", showFunctions},
    {"pointers", "Information about pointers", showPointers},
    {"arrays", "Information about arrays", showArrays},
    {"structures", "Information about structures", showStructures},
    {"memoryallocation", "Information about memory allocation", showMemoryAllocation},
    {"fileio", "Information about file I/O", showFileIO},
    {"recursion", "Information about recursion", showRecursion},
    {"dynamicarrays", "Information about dynamic arrays", showDynamicArrays}
};

int numTopics = sizeof(topics) / sizeof(Topic);

int main() {
    char command[50];

    // Set console text color and background
    setColor(LIGHTGRAY, BLACK);

    printf("\nWelcome to Interactive C Documentation!\n\n");
    displayTextWithDelay("Initializing...", 100);

    printf("\n\n");

    while (1) {
        printf("Enter a command (type 'help' for available commands): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; // Remove newline character

        if (strcmp(command, "help") == 0) {
            showHelp();
        } else if (strncmp(command, "topic", 5) == 0) {
            char topic[50];
            sscanf(command, "%*s %s", topic);
            showTopic(topic);
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting...\n");
            break;
        } else if (strcmp(command, "list") == 0) {
            showAllTopics();
        } else if (strncmp(command, "search", 6) == 0) {
            char searchTerm[50];
            sscanf(command, "%*s %s", searchTerm);
            searchTopic(searchTerm);
        } else {
            unknownCommand();
        }
    }

    return 0;
}

// Function to display help information
void showHelp() {
    setColor(LIGHTGREEN, BLACK);
    printf("\nAvailable commands:\n");
    setColor(LIGHTGRAY, BLACK);
    printf("help\t\t- Display available commands\n");
    printf("topic [name]\t- Display information about a specific topic\n");
    printf("list\t\t- List all available topics\n");
    printf("search [term]\t- Search for topics containing the specified term\n");
    printf("exit\t\t- Exit the program\n\n");
}

// Function to display information about a specific topic
void showTopic(char *topicName) {
    int found = 0;
    for (int i = 0; i < numTopics; i++) {
        if (strcmp(topics[i].name, topicName) == 0) {
            setColor(LIGHTCYAN, BLACK);
            printf("\n%s:\n%s\n", topics[i].name, topics[i].description);
            if (topics[i].displayFunction != NULL) {
                // Display function with animation
                printf("\nLoading %s...\n", topicName);
                displayTextWithDelay(topics[i].description, 50);
                topics[i].displayFunction();
            } else {
                printf("No further information available for this topic.\n");
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        setColor(LIGHTRED, BLACK);
        printf("\nTopic '%s' not found.\n", topicName);
    }
    setColor(LIGHTGRAY, BLACK);
}

// Function to handle unknown commands
void unknownCommand() {
    setColor(LIGHTRED, BLACK);
    printf("Unknown command. Type 'help' for available commands.\n");
    setColor(LIGHTGRAY, BLACK);
}

// Function to display all available topics
void showAllTopics() {
    setColor(LIGHTCYAN, BLACK);
    printf("\nAvailable Topics:\n");
    setColor(LIGHTGRAY, BLACK);
    for (int i = 0; i < numTopics; i++) {
        printf("%s\n", topics[i].name);
    }
}

// Function to search for topics containing the specified term
void searchTopic(char *searchTerm) {
    int found = 0;
    setColor(LIGHTCYAN, BLACK);
    printf("\nTopics containing '%s':\n", searchTerm);
    setColor(LIGHTGRAY, BLACK);
    for (int i = 0; i < numTopics; i++) {
        if (strstr(topics[i].name, searchTerm) || strstr(topics[i].description, searchTerm)) {
            printf("%s\n", topics[i].name);
            found = 1;
        }
    }
    if (!found) {
        setColor(LIGHTRED, BLACK);
        printf("No topics found containing '%s'.\n", searchTerm);
        setColor(LIGHTGRAY, BLACK);
    }
}

// Display function for "variables" topic
void showVariables() {
    setColor(LIGHTCYAN, BLACK);
    printf("Variables in C:\n");
    printf("A variable is a named memory location used to store data.\n");
    printf("Example:\n");
    printf("int age = 25; // Declares an integer variable 'age' and assigns it the value 25\n");
    setColor(LIGHTGRAY, BLACK);
}

// Display function for "operators" topic
void showOperators() {
    setColor(LIGHTCYAN, BLACK);
    printf("Operators in C:\n");
    printf("Operators perform operations on operands.\n");
    printf("Examples:\n");
    printf("int result = 5 + 3; // Addition operator\n");
    printf("int result = 10 / 2; // Division operator\n");
    setColor(LIGHTGRAY, BLACK);
}

// Display function for "controlflow" topic
void showControlFlow() {
    setColor(LIGHTCYAN, BLACK);
    printf("Control Flow in C:\n");
    printf("Control flow statements allow you to control the flow of execution in a program.\n");
    printf("Examples:\n");
    printf("if (condition) {\n");
    printf("\t// Code block executed if condition is true\n");
    printf("} else {\n");
    printf("\t// Code block executed if condition is false\n");
    printf("}\n");
    setColor(LIGHTGRAY, BLACK);
}

// Display function for "functions" topic
void showFunctions() {
    setColor(LIGHTCYAN, BLACK);
    printf("Functions in C:\n");
    printf("Functions are blocks of code that perform a specific task.\n");
    printf("Example:\n");
    printf("int add(int a, int b) {\n");
    printf("\treturn a + b;\n");
    printf("}\n");
    printf("int main() {\n");
    printf("\tint result = add(3, 4); // Calls the add function\n");
    printf("\treturn 0;\n");
    printf("}\n");
    setColor(LIGHTGRAY, BLACK);
}

// Display function for "pointers" topic
void showPointers() {
    setColor(LIGHTCYAN, BLACK);
    printf("Pointers in C:\n");
    printf("Pointers are variables that store memory addresses.\n");
    printf("Example:\n");
    printf("int *ptr; // Declares a pointer to an integer\n");
    printf("int num = 10;\n");
    printf("ptr = &num; // Assigns the address of num to ptr\n");
    printf("printf(\"Value at ptr: %d\\n\", *ptr); // Prints the value pointed to by ptr\n");
    setColor(LIGHTGRAY, BLACK);
}

// Display function for "arrays" topic
void showArrays() {
    setColor(LIGHTCYAN, BLACK);
    printf("Arrays in C:\n");
    printf("Arrays are collections of elements of the same data type.\n");
    printf("Example:\n");
    printf("int arr[5]; // Declares an integer array with 5 elements\n");
    printf("for (int i = 0; i < 5; i++) {\n");
    printf("\tarr[i] = i * 2; // Assigns values to array elements\n");
    printf("}\n");
    setColor(LIGHTGRAY, BLACK);
}

// Display function for "structures" topic
void showStructures() {
    setColor(LIGHTCYAN, BLACK);
    printf("Structures in C:\n");
    printf("Structures allow you to group different data types under a single name.\n");
    printf("Example:\n");
    printf("struct Person {\n");
    printf("\tchar name[50];\n");
    printf("\tint age;\n");
    printf("};\n");
    printf("struct Person p1; // Declares a variable of type Person\n");
    printf("strcpy(p1.name, \"John\"); // Assigns a value to the name member\n");
    printf("p1.age = 30; // Assigns a value to the age member\n");
    setColor(LIGHTGRAY, BLACK);
}

// Display function for "memoryallocation" topic
void showMemoryAllocation() {
    setColor(LIGHTCYAN, BLACK);
    printf("Memory Allocation in C:\n");
    printf("Dynamic memory allocation allows programs to allocate memory at runtime.\n");
    printf("Example using malloc:\n");
    printf("int *ptr = (int*)malloc(sizeof(int)); // Allocates memory for an integer\n");
    printf("if (ptr != NULL) {\n");
    printf("\t*ptr = 10; // Assigns a value to the memory location\n");
    printf("\tfree(ptr); // Frees the allocated memory\n");
    printf("}\n");
    setColor(LIGHTGRAY, BLACK);
}

// Display function for "fileio" topic
void showFileIO() {
    setColor(LIGHTCYAN, BLACK);
    printf("File I/O in C:\n");
    printf("File I/O operations allow reading from and writing to files.\n");
    printf("Example of reading from a file:\n");
    printf("FILE *file = fopen(\"example.txt\", \"r\"); // Opens a file for reading\n");
    printf("if (file != NULL) {\n");
    printf("\tchar buffer[100];\n");
    printf("\tfgets(buffer, 100, file); // Reads a line from the file into buffer\n");
    printf("\tprintf(\"Read from file: %s\", buffer); // Prints the content read from file\n");
    printf("\tfclose(file); // Closes the file\n");
    printf("}\n");
    setColor(LIGHTGRAY, BLACK);
}

// Display function for "recursion" topic
void showRecursion() {
    setColor(LIGHTCYAN, BLACK);
    printf("Recursion in C:\n");
    printf("Recursion is a technique where a function calls itself.\n");
    printf("Example of factorial using recursion:\n");
    printf("int factorial(int n) {\n");
    printf("\tif (n <= 1)\n");
    printf("\t\treturn 1;\n");
    printf("\telse\n");
    printf("\t\treturn n * factorial(n - 1);\n");
    printf("}\n");
    printf("int main() {\n");
    printf("\tint result = factorial(5); // Calculates factorial of 5\n");
    printf("\treturn 0;\n");
    printf("}\n");
    setColor(LIGHTGRAY, BLACK);
}

// Display function for "dynamicarrays" topic
void showDynamicArrays() {
    setColor(LIGHTCYAN, BLACK);
    printf("Dynamic Arrays in C:\n");
    printf("Dynamic arrays are arrays whose size can be changed during runtime.\n");
    printf("Example of dynamic array using realloc:\n");
    printf("int *arr = (int*)malloc(5 * sizeof(int)); // Allocates memory for 5 integers\n");
    printf("if (arr != NULL) {\n");
    printf("\t// Use the dynamic array\n");
    printf("\t// Reallocate memory for 10 integers\n");
    printf("\tarr = (int*)realloc(arr, 10 * sizeof(int));\n");
    printf("}\n");
    setColor(LIGHTGRAY, BLACK);
}

// Function to display text with a delay for animation effect
void displayTextWithDelay(char *text, int delay) {
    int i = 0;
    while (text[i] != '\0') {
        putchar(text[i]);
        fflush(stdout);
        usleep(delay * 1000); // Delay in milliseconds
        i++;
    }
}

// Function to set text color and background
void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

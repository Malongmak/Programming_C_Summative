#include <stdio.h>
#include <string.h>

#define MAX_NAMES 100
#define MAX_NAME_LENGTH 100

// function prototype
void sortNames(char names[][MAX_NAME_LENGTH], int count, int (*cmp)(const char *, const char *));
int countNames(char names[][MAX_NAME_LENGTH], int max);
int compareAsc(const char *a, const char *b);
int compareDesc(const char *a, const char *b);

//function pointers for sorting and counting
typedef void (*SortFunctionPointer)(char names[][MAX_NAME_LENGTH], int, int (*)(const char *, const char *));
typedef int (*CountFunctionPointer)(char names[][MAX_NAME_LENGTH], int);

// function pointers array
SortFunctionPointer sortFunctions[] = { sortNames };
CountFunctionPointer countFunctions[] = { countNames };

int main() {
    char names[MAX_NAMES][MAX_NAME_LENGTH];
    int numNames = 0;
    char order[10];
    int choice;

    // User input names
    printf("Enter up to %d names (type 'END' to stop):\n", MAX_NAMES);
    while (numNames < MAX_NAMES) {
        printf("Name %d: ", numNames + 1);
        fgets(names[numNames], MAX_NAME_LENGTH, stdin);
        names[numNames][strcspn(names[numNames], "\n")] = '\0';
        if (strcmp(names[numNames], "END") == 0) break;
        numNames++;
    }

    // User
    printf("Choose an option:\n1. Sort Names\n2. Count Names\n");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter sorting order (asc or desc): ");
        fgets(order, sizeof(order), stdin);
        order[strcspn(order, "\n")] = '\0';

        int (*cmp)(const char *, const char *);
        if (strcmp(order, "asc") == 0) {
            cmp = compareAsc;
        } else if (strcmp(order, "desc") == 0) {
            cmp = compareDesc;
        } else {
            printf("Invalid order.\n");
            return 1;
        }

        // Sort names
        sortFunctions[0](names, numNames, cmp);
        printf("Sorted names:\n");
        for (int i = 0; i < numNames; i++) {
            printf("%s\n", names[i]);
        }
    } else if (choice == 2) {
        int count = countFunctions[0](names, MAX_NAMES);
        printf("Number of names: %d\n", count);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

// Function to sort names
void sortNames(char names[][MAX_NAME_LENGTH], int count, int (*cmp)(const char *, const char *)) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (cmp(names[i], names[j]) > 0) {
                char temp[MAX_NAME_LENGTH];
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }
}

// Function to count names
int countNames(char names[][MAX_NAME_LENGTH], int max) {
    int count = 0;
    for (int i = 0; i < max; i++) {
        if (strlen(names[i]) > 0) {
            count++;
        }
    }
    return count;
}
// Comparison function for ascending order
int compareAsc(const char *a, const char *b) {
    return strcmp(a, b);
}

// Comparison function for descending order
int compareDesc(const char *a, const char *b) {
    return strcmp(b, a);
}
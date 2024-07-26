#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 100
#define MAX_STUDENTS 100

// Structure to represent a student
typedef struct {
    char full_name[MAX_NAME_LENGTH];
    int grade_c;
    int grade_mad; // Mobile Application Development
    int grade_com; // Communications
} Student;

// Function to write student data to a file
void write_to_file(Student students[], int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s %d %d %d\n", students[i].full_name, students[i].grade_c, students[i].grade_mad, students[i].grade_com);
    }

    fclose(file);
}

int main() {
    int n;

    // Get the number of students
    printf("Enter the number of students (5 < n < 100): ");
    scanf("%d", &n);

    if (n <= 5 || n >= 100) {
        printf("Number of students must be between 5 and 100.\n");
        return 1;
    }

    Student *students = (Student *)malloc(n * sizeof(Student));
    if (students == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Input data for each student
    for (int i = 0; i < n; i++) {
        printf("Enter full name of student %d: ", i + 1);
        scanf(" %[^\n]", students[i].full_name); // Read full line

        printf("Enter grade for Programming in C: ");
        scanf("%d", &students[i].grade_c);

        printf("Enter grade for Mobile Application Development: ");
        scanf("%d", &students[i].grade_mad);

        printf("Enter grade for Communications: ");
        scanf("%d", &students[i].grade_com);
    }

    // Write data to file
    write_to_file(students, n, "students_data.txt");

    free(students);
    printf("Data has been written to students_data.txt\n");
    return 0;
}

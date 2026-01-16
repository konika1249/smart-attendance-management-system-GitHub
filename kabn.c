
#include <stdio.h>
#include <string.h>
#include <time.h>

#define DAYS 7

typedef struct {
    int roll;
    char name[50];
    int attendance[DAYS];
    int presentCount;
    float percentage;
} Student;

/* Generate 7 dates */
void generateDates(char dates[DAYS][15]) {
    int d, m, y;
    printf("\nEnter START DATE (DD-MM-YYYY): ");
    scanf("%d-%d-%d", &d, &m, &y);

    struct tm start = {0};
    start.tm_mday = d;
    start.tm_mon = m - 1;
    start.tm_year = y - 1900;

    for (int i = 0; i < DAYS; i++) {
        struct tm temp = start;
        temp.tm_mday += i;
        mktime(&temp);
        strftime(dates[i], 15, "%d-%m-%Y", &temp);
    }
}

/* Add students attendance */
void addAllStudents() {
    FILE *fp = fopen("attendance_data.txt", "ab");
    Student s;
    char dates[DAYS][15];
    int n;

    if (fp == NULL) {
        printf("\n File opening error!\n");
        return;
    }

    generateDates(dates);

    printf("\nEnter total number of students: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        printf("\n----- Student %d -----\n", i + 1);

        printf("Enter Roll: ");
        scanf("%d", &s.roll);
        getchar();

        printf("Enter Name: ");
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = '\0';

        s.presentCount = 0;

        printf("\nEnter Attendance (1 = Present, 0 = Absent)\n");
        for (int j = 0; j < DAYS; j++) {
            printf("%s : ", dates[j]);
            scanf("%d", &s.attendance[j]);
            if (s.attendance[j] == 1)
                s.presentCount++;
        }

        s.percentage = (s.presentCount * 100.0) / DAYS;

        fwrite(&s, sizeof(Student), 1, fp);
    }

    fclose(fp);
    printf("\n Attendance Saved Successfully!\n");
}

/* Search student by Roll */
void searchByRoll() {
    FILE *fp = fopen("attendance_data.txt", "rb");
    Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("\n No data found!\n");
        return;
    }

    printf("\nEnter Roll to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            printf("\n Student Found\n");
            printf("Name: %s\n", s.name);
            printf("Roll: %d\n", s.roll);
            printf("Present Days: %d / %d\n", s.presentCount, DAYS);
            printf("Attendance Percentage: %.2f%%\n", s.percentage);

            if (s.percentage < 75)
                printf(" WARNING: Attendance Below 75%%\n");
            break;
        }
    }

    if (!found)
        printf("\n Student Not Found!\n");

    fclose(fp);
}

/* Delete student attendance by Roll */
void deleteByRoll() {
    FILE *fp = fopen("attendance_data.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");

    Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("\n No data found!\n");
        return;
    }

    printf("\nEnter Roll to DELETE: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;      // skip this record
            continue;
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("attendance_data.txt");
    rename("temp.txt", "attendance_data.txt");

    if (found)
        printf("\n️ Attendance Data Deleted Successfully!\n");
    else
        printf("\n Student Not Found!\n");
}

int main() {
    int choice;

    /* Add attendance first */
    addAllStudents();

    /* Menu */
    do {
        printf("\n===== MENU =====\n");
        printf("1. Search Student by Roll\n");
        printf("2. Delete Student Attendance\n");
        printf("3. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            searchByRoll();
        else if (choice == 2)
            deleteByRoll();
        else if (choice == 3)
            printf("\nExiting Program...\n");
        else
            printf("\n Invalid Choice!\n");

    } while (choice != 3);

    return 0;
}

#include <stdio.h>

int main() {
    int N;
    int marks, sum;
    float average;
    int subjectFail;

    printf("Enter number of students: ");
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {

        sum = 0;
        subjectFail = 0;

        printf("\nStudent %d\n", i);

        // Inner loop for 5 subjects
        for (int j = 1; j <= 5; j++) {

            printf("Enter marks for subject %d: ", j);
            scanf("%d", &marks);

            sum = sum + marks;

            // Check subject deficiency
            if (marks < 33) {
                subjectFail = 1;
            }
        }

        // Calculate average
        average = sum / 5.0;

        // Classification
        if (subjectFail == 1) {
            printf("Result: Fail - Subject Deficiency\n");
        }
        else if (average >= 80) {
            printf("Result: Distinction\n");
        }
        else if (average >= 60) {
            printf("Result: Pass\n");
        }
        else {
            printf("Result: Fail\n");
        }

        printf("Average = %.2f\n", average);
    }

    return 0;
}
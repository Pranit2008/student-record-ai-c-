/*
 * ============================================================================
 * Project Title : AI-Assisted Student Record and Result Management System
 * Course Name   : Programming in C (PRC1001)
 * Program       : B.Tech Computer Science and Engineering (Semester I)
 * Institution   : University of Petroleum and Energy Studies (UPES), Dehradun
 * Student Name  : Pranit Singh
 * SAP ID        : 590032340
 * Due Date      : 20 November 2026
 *
 * Description   : A comprehensive console-based, menu-driven C application for
 *                 managing student academic records, computing semester-based
 *                 CGPA, generating cohort-level year-wise averages, sorting
 *                 records by SAP ID and Name, and providing rule-based
 *                 personalized Academic Advisor recommendations.
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define TOTAL_SEMESTERS 8

/* Structure to store complete individual student details */
struct Student {
    long int sap_id;
    char roll_no[20];
    char name[50];
    char phone[15];
    char email[50];
    int year;                    /* 1, 2, 3, or 4 */
    int semester;                /* 1 to 8 */
    float sgpa[TOTAL_SEMESTERS]; /* SGPA for all 8 semesters (0.0 if upcoming) */
    float cgpa;
};

/* Global database array and record counter */
struct Student students[MAX_STUDENTS];
int student_count = 0;

/* Function Declarations */
void loadSampleStudents();

/* Pre-load 5 diverse student records representing all 4 academic years */
void loadSampleStudents() {
    int i;

    /* Student 1: 1st Year - Pranit Singh (Excellent Performance tier) */
    students[0].sap_id = 590032340;
    strcpy(students[0].roll_no, "R214226001");
    strcpy(students[0].name, "Pranit Singh");
    strcpy(students[0].phone, "9876543210");
    strcpy(students[0].email, "pran200811@gmail.com");
    students[0].year = 1;
    students[0].semester = 1;
    float s0[8] = {9.20f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    for (i = 0; i < 8; i++) students[0].sgpa[i] = s0[i];
    students[0].cgpa = 9.20f;

    /* Student 2: 2nd Year - Aarav Sharma (Good Performance tier) */
    students[1].sap_id = 50010202;
    strcpy(students[1].roll_no, "R214225002");
    strcpy(students[1].name, "Aarav Sharma");
    strcpy(students[1].phone, "9812345670");
    strcpy(students[1].email, "aarav.sharma@stu.upes.ac.in");
    students[1].year = 2;
    students[1].semester = 3;
    float s1[8] = {7.80f, 8.10f, 8.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    for (i = 0; i < 8; i++) students[1].sgpa[i] = s1[i];
    students[1].cgpa = 8.05f;

    /* Student 3: 3rd Year - Riya Patel (Needs Improvement tier) */
    students[2].sap_id = 50010208;
    strcpy(students[2].roll_no, "R214224008");
    strcpy(students[2].name, "Riya Patel");
    strcpy(students[2].phone, "9765432109");
    strcpy(students[2].email, "riya.patel@stu.upes.ac.in");
    students[2].year = 3;
    students[2].semester = 5;
    float s2[8] = {6.40f, 6.10f, 5.80f, 6.30f, 6.15f, 0.0f, 0.0f, 0.0f};
    for (i = 0; i < 8; i++) students[2].sgpa[i] = s2[i];
    students[2].cgpa = 6.15f;

    /* Student 4: 2nd Year - Kabir Mehra (Requires Immediate Attention tier) */
    students[3].sap_id = 50010201;
    strcpy(students[3].roll_no, "R214225001");
    strcpy(students[3].name, "Kabir Mehra");
    strcpy(students[3].phone, "9654321098");
    strcpy(students[3].email, "kabir.mehra@stu.upes.ac.in");
    students[3].year = 2;
    students[3].semester = 4;
    float s3[8] = {5.20f, 4.80f, 5.00f, 4.90f, 0.0f, 0.0f, 0.0f, 0.0f};
    for (i = 0; i < 8; i++) students[3].sgpa[i] = s3[i];
    students[3].cgpa = 4.97f;

    /* Student 5: 4th Year - Ananya Joshi (Excellent Performance tier) */
    students[4].sap_id = 50010204;
    strcpy(students[4].roll_no, "R214223004");
    strcpy(students[4].name, "Ananya Joshi");
    strcpy(students[4].phone, "9543210987");
    strcpy(students[4].email, "ananya.joshi@stu.upes.ac.in");
    students[4].year = 4;
    students[4].semester = 7;
    float s4[8] = {8.60f, 8.80f, 9.10f, 8.70f, 8.90f, 9.20f, 9.00f, 0.0f};
    for (i = 0; i < 8; i++) students[4].sgpa[i] = s4[i];
    students[4].cgpa = 8.90f;

    student_count = 5;
}

int main() {
    int choice;

    /* Pre-load 5 student records */
    loadSampleStudents();

    printf("=================================================================\n");
    printf("   AI-ASSISTED STUDENT RECORD AND RESULT MANAGEMENT SYSTEM\n");
    printf("             UPES Dehradun - B.Tech CSE (PRC1001)\n");
    printf("=================================================================\n");
    printf("System initialized with %d student records.\n", student_count);

    do {
        printf("\n------------------------- MAIN MENU -------------------------\n");
        printf("1. Add Student Details\n");
        printf("2. Search and Display a Student Record\n");
        printf("3. Calculate CGPA of Each Student\n");
        printf("4. Calculate Average CGPA of Students by Year\n");
        printf("5. Display Records of All Students\n");
        printf("6. Delete an Individual Student Record\n");
        printf("7. Display All Records in Increasing Order of SAP ID\n");
        printf("8. Display All Records in Increasing Order of Name\n");
        printf("9. AI-Assisted Academic Advisor\n");
        printf("0. Exit\n");
        printf("-------------------------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            break;
        }

        switch (choice) {
            case 0:
                printf("\nExiting program. Thank you!\n");
                break;
            default:
                printf("\nFeature will be implemented in upcoming modules.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Incident{
    char title[200];
    char description[1000];
    char reportedBy[100];
    char category[100];
    char severity[20];
    char status[20];
    char datetime[40]; 
};
void incident_severity(FILE *fp){
    struct Incident newIncident;
    printf("severity opetions: \n");
    printf("1. Low\n");
    printf("2. Medium\n");
    printf("3. High\n");
    printf("4. Critical\n");
    printf("Enter severity number: ");
    int severity;
    scanf("%d", &severity);
    getchar(); // Clear the newline character from the input buffer
    if(severity < 1 || severity > 4) {
        printf("Invalid severity number. Please try again.\n");
        incident_severity(fp); // Call the function again for valid input
    }
    else {
        switch(severity) {
            case 1:
                fprintf(fp,"Severity set to Low.\n");
                break;
            case 2:
                fprintf(fp,"Severity set to Medium.\n");
                break;
            case 3:
                fprintf(fp,"Severity set to High.\n");
                break;
            case 4:
                fprintf(fp,"Severity set to Critical.\n");
                break;
        }
    }
}

void status(FILE *fp){
    int status_choice;
    printf("status options: \n");
    printf("1. Open\n");
    printf("2. In Progress\n");
    printf("3. Resolved\n");
    printf("4. Closed\n");
    printf("Enter status number: ");
    scanf("%d", &status_choice);
    getchar(); // Clear the newline character from the input buffer
    if(status_choice < 1 || status_choice > 4) {
        printf("Invalid status number. Please try again.\n");
        status(fp); // Call the function again for valid input
    }
    else{
        if(status_choice == 4) {
            fprintf(fp,"Incident closed.\n");
        }
        else if(status_choice == 3) {
            fprintf(fp,"Incident resolved.\n"); 
        }
        else if(status_choice == 2) {
            fprintf(fp,"Incident is in progress.\n");
        }
        else {
            fprintf(fp,"Incident is open.\n");
        }
    }
}

void incident_severity_and_status(struct Incident *incident) {
    int severity_choice, status_choice;

    printf("severity options:\n");
    printf("1. Low\n2. Medium\n3. High\n4. Critical\n");
    printf("Enter severity number: ");
    scanf("%d", &severity_choice);

    if (severity_choice == 1)
        strcpy(incident->severity, "Low");
    else if (severity_choice == 2)
        strcpy(incident->severity, "Medium");
    else if (severity_choice == 3)
        strcpy(incident->severity, "High");
    else if (severity_choice == 4)
        strcpy(incident->severity, "Critical");
    else
        strcpy(incident->severity, "Unknown");

    printf("status options:\n");
    printf("1. Open\n2. In Progress\n3. Resolved\n4. Closed\n");
    printf("Enter status number: ");
    scanf("%d", &status_choice);

    if (status_choice == 1)
        strcpy(incident->status, "Open");
    else if (status_choice == 2)
        strcpy(incident->status, "In Progress");
    else if (status_choice == 3)
        strcpy(incident->status, "Resolved");
    else if (status_choice == 4)
        strcpy(incident->status, "Closed");
    else
        strcpy(incident->status, "Unknown");
}

void addIncident()
{
    struct Incident newIncident;
    FILE *fp;
    fp = fopen("incidents.txt", "a");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    printf("Enter title: ");
    scanf("%[^\n]", newIncident.title);
    printf("Enter description: ");
    scanf(" %[^\n]", newIncident.description);
    getchar();
    time_t now=time(NULL);
    struct tm *t = localtime(&now);
    strftime(newIncident.datetime, sizeof(newIncident.datetime), "%Y-%m-%d %H:%M:%S", t);
    printf("Enter reported by: ");
    scanf("%[^\n]", newIncident.reportedBy);
    printf("Enter category: ");
    scanf(" %[^\n]", newIncident.category); // Clear the newline character from the input buffer

    fprintf(fp, "Date & time: %s\n", newIncident.datetime);
    fprintf(fp, "Title: %s\n", newIncident.title);
    fprintf(fp, "Description: %s\n", newIncident.description);
    fprintf(fp, "Reported By: %s\n", newIncident.reportedBy);
    fprintf(fp, "Category: %s\n", newIncident.category);
    incident_severity_and_status(&newIncident);
    fprintf(fp, "Severity: %s\n", newIncident.severity);
    fprintf(fp, "Status: %s\n", newIncident.status);
    fprintf(fp,"\n");

    fclose(fp);
    printf("Incident added successfully!\n");

    printf("\n");
    printf("Incident details:\n\n");
    printf("Date & time: %s\n",newIncident.datetime);
    printf("Title: %s\n", newIncident.title);
    printf("Description: %s\n", newIncident.description);
    printf("Reported By: %s\n", newIncident.reportedBy);
    printf("Category: %s\n", newIncident.category);
    printf("Severity: %s\n",newIncident.severity);
    printf("Status: %s\n", newIncident.status);

}

void viewIncidents()
{
    FILE *fp;
    char line[100];
    fp=fopen("incidents.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    printf("\nIncident Report:\n");
    while(fgets(line, sizeof(line), fp)!= NULL)
    {
        printf("%s", line);
    }
    fclose(fp);
    printf("\n");

}
void search_keywords()
{
    char keyword[50];
    printf("\nEnter keyword to search: ");
    scanf("%s",keyword);
    FILE *fp;
    fp=fopen("incidents.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    char line[100];
    int found = 0,linenumber = 0;
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        linenumber++;
        if(strstr(line,keyword)!=NULL)
        {
            printf("Line-%d : %s",linenumber,line);
            found = 1;
        }
    }
    fclose(fp);
}

int main()
{
    while(1) 
    {
        printf("\nIncident Report Management System\n");
        printf("1. Add Incident\n");
        printf("2. View Incidents\n");
        printf("3. Search a keyword\n");
        printf("4. Exit\n");
        int choice;
        printf("enter your choice:");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer
        switch(choice)
        {
            case 1:
                addIncident();
                break;
            case 2:
                viewIncidents();
                break;
            case 3:
                search_keywords();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
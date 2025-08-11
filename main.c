#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Incident{
    char id[10]; // Unique ID for the incident
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
                fprintf(fp,"severity: critical\n");
                break; 
            case 2:
                fprintf(fp,"severity: high\n");
                break;
            case 3:
                fprintf(fp,"severity: medium\n");
                break;
            case 4:
                fprintf(fp,"severity: low\n");
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


int getseverity(const char *severity)
{
    if(strcmp(severity,"Critical")==0)
    return 1;
    else if(strcmp(severity,"High")==0)
    return 2;
    else if(strcmp(severity,"Medium")==0)
    return 3;
    else if(strcmp(severity,"Low")==0)
    return 4;
    else
    return 5;
}

int get_next_id() {
    FILE *fp = fopen("incidents.txt", "r");
    if (fp == NULL) return 1; // First incident
    char line[500];
    int last_id = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "ID:", 3) == 0) {
            int id;
            sscanf(line, "ID: %d", &id);
            if (id > last_id) last_id = id;
        }
    }
    fclose(fp);
    return last_id + 1;
}

int id_exists_in_file(const char *id) {
    FILE *file = fopen("incidents.txt", "r");
    if (!file) return 0; // file doesn't exist yet, so ID is unique

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, id)) { // ID found in file
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void generate_unique_id(char *id_buffer) {
    do {
        int random_id = 100000 + rand() % 900000; // ensures 6 digits
        sprintf(id_buffer, "%d", random_id);
    } while (id_exists_in_file(id_buffer));
}


void addIncident()
{
    struct Incident newIncident;
    generate_unique_id(newIncident.id);
    FILE *fp;
    fp = fopen("incidents.txt", "a");
    int Id=1;
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    // newIncident.id=get_next_id();
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

    fprintf(fp,"ID: %s\n",newIncident.id);
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
    printf("ID: %s\n", newIncident.id);
    printf("Date & time: %s\n",newIncident.datetime);
    printf("Title: %s\n", newIncident.title);
    printf("Description: %s\n", newIncident.description);
    printf("Reported By: %s\n", newIncident.reportedBy);
    printf("Category: %s\n", newIncident.category);
    printf("Severity: %s\n",newIncident.severity);
    printf("Status: %s\n", newIncident.status);

}

void sort_incidents_by_severity(struct Incident incidents[],int count) {

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int rank1 = getseverity(incidents[j].severity);
            int rank2 = getseverity(incidents[j + 1].severity);

            if (rank1 > rank2) {
                // Swap the two incidents
                struct Incident temp = incidents[j];
                incidents[j] = incidents[j + 1];
                incidents[j + 1] = temp;
            }
        }
    }
}
int load_incidents(struct Incident incidents[]) {
    FILE *file = fopen("incidents.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open incidents.txt\n");
        return 0;
    }

    int count = 0;
    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, "Date & time:", 12) == 0)
            sscanf(buffer, "Date & time: %[^\n]", incidents[count].datetime);
        if (fgets(buffer, sizeof(buffer), file))
            sscanf(buffer, "Title: %[^\n]", incidents[count].title);
        if (fgets(buffer, sizeof(buffer), file))
            sscanf(buffer, "Description: %[^\n]", incidents[count].description);
        if (fgets(buffer, sizeof(buffer), file))
            sscanf(buffer, "Reported By: %[^\n]", incidents[count].reportedBy);
        if (fgets(buffer, sizeof(buffer), file))
            sscanf(buffer, "Category: %[^\n]", incidents[count].category);
        if (fgets(buffer, sizeof(buffer), file))
            sscanf(buffer, "Severity: %[^\n]", incidents[count].severity);
        if (fgets(buffer, sizeof(buffer), file))
            sscanf(buffer, "Status: %[^\n]", incidents[count].status);
        // Skip blank line between incidents
        fgets(buffer, sizeof(buffer), file);
        count++;
    }
    fclose(file);
    return count;
}
void view_all_incident_normally(){

    FILE *fp;
    fp=fopen("incidents.txt","r");

    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
    printf("There are no incidents reported till now.\n");
    fclose(fp);
    return;
    }
    rewind(fp);

    char line[500];
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
void view_incidents_according_to_severity(){
    struct Incident incidents[100];
    int count=load_incidents(incidents);

    if (count == 0) {
    printf("There are no incidents reported till now.\n");
    return;
    }

    sort_incidents_by_severity(incidents,count);

    for(int i = 0; i < count; i++) {
        printf("Date & time: %s\n", incidents[i].datetime);
        printf("Title: %s\n", incidents[i].title);
        printf("Description: %s\n", incidents[i].description);
        printf("Reported By: %s\n", incidents[i].reportedBy);
        printf("Category: %s\n", incidents[i].category);
        printf("Severity: %s\n", incidents[i].severity);
        printf("Status: %s\n", incidents[i].status);
        printf("\n");
}
}

void view_incidents_from_date() {
    char startDateTime[40];
    printf("Enter start date & time (YYYY-MM-DD HH:MM:SS): ");
    scanf(" %[^\n]", startDateTime);

    struct tm start_tm = {0};
    sscanf(startDateTime, "%d-%d-%d %d:%d:%d",
    &start_tm.tm_year, &start_tm.tm_mon, &start_tm.tm_mday,
    &start_tm.tm_hour, &start_tm.tm_min, &start_tm.tm_sec);

start_tm.tm_year -= 1900; // struct tm counts years since 1900
start_tm.tm_mon  -= 1;    // struct tm months are 0–11

    time_t start_time = mktime(&start_tm);

    FILE *fp = fopen("incidents.txt", "r");
    if (!fp) {
        printf("Error opening file\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
    printf("There are no incidents reported till now.\n");
    fclose(fp);
    return;
    }
    rewind(fp);

    char line[500];
    struct Incident tempIncident;
    int printIncident = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Date & time:", 12) == 0) {
            sscanf(line, "Date & time: %[^\n]", tempIncident.datetime);

            struct tm incident_tm = {0};
            sscanf(tempIncident.datetime, "%d-%d-%d %d:%d:%d",&incident_tm.tm_year, &incident_tm.tm_mon, &incident_tm.tm_mday,&incident_tm.tm_hour, &incident_tm.tm_min, &incident_tm.tm_sec);

incident_tm.tm_year -= 1900; // struct tm years since 1900
incident_tm.tm_mon  -= 1;    // struct tm months are 0-11

time_t incident_time = mktime(&incident_tm);


            printIncident = (difftime(incident_time, start_time) >= 0);
            printf("\n"); // Separate incidents
        }

        if (printIncident) {
            printf("%s", line);
        }
    }

    fclose(fp);
}

// this function is used to view all incidents
void viewIncidents()
{
    int ch;
    while(1)
    {
        printf("\n1.View all incidents in original order.\n");
        printf("2.View incidents sorted by severity.\n");
        printf("3.View incidents sorted by date and time.\n");
        printf("4.Exit\n");

        printf("enter your choice:\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            view_all_incident_normally();
            return;
            case 2:
            view_incidents_according_to_severity();
            return;

            case 3:
            view_incidents_from_date();
            return;
            case 4:
            return;
            default:
            printf("invalid number.");
            return;

        }
    }

}
void search_keywords()
{
    char keyword[50];
    printf("\nEnter keyword to search: ");
    scanf("%[^\n]",keyword);
    FILE *fp;
    fp=fopen("incidents.txt", "r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    char line[1000];
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

void searchIncidentByID() {
    char searchID[10], line[256];
    int found = 0;
    printf("Enter Incident ID: ");
    fgets(searchID, sizeof(searchID), stdin);
    searchID[strcspn(searchID, "\n")] = 0; // remove newline

    FILE *file = fopen("incidents.txt", "r");
    if (!file) {
        printf("No incidents found.\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, searchID)) {
            found = 1;
            printf("%s", line);
            // Print remaining lines until next "ID:" or EOF
            while (fgets(line, sizeof(line), file) && !strstr(line, "ID:")) {
                printf("%s", line);
            }
            break;
        }
    }

    if (!found) printf("Incident not found.\n");
    fclose(file);
}

void searchIncidentByTitle() {
    char searchTitle[100], line[256];
    int found = 0;
    printf("Enter Incident Title: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0;

    FILE *file = fopen("incidents.txt", "r");
    if (!file) {
        printf("No incidents found.\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, searchTitle)) {
            found = 1;
            // Move back to print ID too
            printf("%s", line);
            while (fgets(line, sizeof(line), file) && !strstr(line, "ID:")) {
                printf("%s", line);
            }
        }
    }

    if (!found) printf("Incident not found.\n");
    fclose(file);
}


void search_incident() {
    int incident_number;
    printf("\n\n. Search incident by ID\n");
    printf("2. Search incident by title\n");
    printf("3. Exit\n");
    printf("\nEnter incident number to search: \n");
    scanf("%d", &incident_number);
    switch(incident_number) {
        case 1:
            searchIncidentByID();
            return;
        case 2:
            searchIncidentByTitle();
            return;
        case 3:
            return;
        default:
            printf("Invalid incident number.\n");
            return;
    }
}


int main()
{
    while(1) 
    {
        printf("\nIncident Report Management System\n");
        printf("1. Add Incident\n");
        printf("2. View Incidents\n");
        printf("3. Search a keyword\n");
        printf("4. Search Incident\n");
        printf("5. Exit\n");
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
            case 5:
                printf("Exiting...\n");
                exit(0);
            case 4:
                search_incident();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#define MAX_NAME_LENGTH 50

// Define a struct for a station
struct Station {
    char *name;
    struct Station *next;
};

// Declare the 2D int array globally
int **distanceMatrix;

typedef struct {
    int distance;
    int cost;
    int* path;
    int nodes;
    int err;
} Result;

// Function to find the vertex with the minimum distance value
int minDistance(int n, int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

Result dijkstra(int n, int src, int dest) {
    Result result;
    result.err=0;
    int dist[n];     // The output array dist[i] holds the shortest distance from src to i
    int parent[n];   // Parent array to store the shortest path tree
    result.path = (int*)malloc(n * sizeof(int));
    // Check if memory allocation is successful
    if (result.path == NULL) {
    // Handle the case where memory allocation fails
    // Set error flag or exit the program
        result.err = 1;
    } else {
    // Initialize the path array elements to -1
    for (int i = 0; i < n; i++) {
        result.path[i] = -1;
    }
}
    // sptSet[i] will be true if vertex i is included in the shortest path tree or the shortest distance from src to i is finalized
    int sptSet[n];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    // Distance from source vertex to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(n, dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < n; v++) {
            if (!sptSet[v] && distanceMatrix[u][v] && dist[u] != INT_MAX && dist[u] + distanceMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + distanceMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    // Store the results in the Result structure
    result.distance = dist[dest];

    // If there is no path from source to destination
    if (result.distance == INT_MAX) {
        printf("No possible journey.");
        result.err=-1;
        return result;
    }

    // Store the path from source to destination in the Result structure
    int pathIndex = 0;
    int tempDest = dest;

    while (tempDest != -1) {
        result.path[pathIndex] = tempDest;
        tempDest = parent[tempDest];
        pathIndex++;
    }
    result.cost=(int)(round(1.2 * (float)result.distance + 25 * ((float)pathIndex-2)));
    result.nodes = pathIndex+1;
    //printf("%d\n",pathIndex);
    return result;
}

void printMatrixAligned(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //printf("%4d| ", distanceMatrix[i][j]); // Adjust the field width as needed
        }
        //printf("\n");
    }
}

char* input(int length) {
    char* expression = (char*)malloc(length * sizeof(char));
    if (expression == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(0);
    }

    int i = 0;
    char c = '\0';
    while (i < length - 1 && scanf("%c", &c) == 1 && c != '\n') {
        expression[i++] = c;
    }
    expression[i] = '\0'; // Null-terminate the string

    // remove '\n'
    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }
    return expression;
}

int parseMatrix(int n,char* input, const char* delimiters,int i) {
    // Use strtok to tokenize the input string
    char* token = strtok(input, delimiters);
    int index=0;
    // Iterate through the tokens and print them
  
    while (token != NULL) {
        distanceMatrix[i][index++] = atoi(token);
        // Get the next token
        token = strtok(NULL, delimiters);
    }
    if(n!=index){
        printf("Invalid distance matrix.");
        return -1;
    }
    return index;
}

void deleteSpace(char *expression) {
    int i, j;    
    // Traverse the expression and remove spaces
    for (i = 0,j=0; expression[i] != '\0'; i++) {
        if (expression[i] != ' ') {
            expression[j++] = expression[i];
        }
    }    
    // Null-terminate the modified expression
    expression[j] = '\0';
}

void findAndReplace(char *originalString, const char *sequenceToFind, const char *replacementString) {
    char *foundPosition = strstr(originalString, sequenceToFind);
    while (foundPosition != NULL) {
        // Calculate the length of the prefix before the found position
        size_t prefixLength = foundPosition - originalString;
        // Calculate the length of the suffix after the found position
        size_t suffixLength = strlen(foundPosition + strlen(sequenceToFind));
        // Calculate the total length of the new string after replacement
        size_t newStringLength = prefixLength + strlen(replacementString) + suffixLength;
        // Allocate memory for the new string
        char *newString = (char *)malloc(newStringLength + 1);
        // Copy the prefix before the found position
        strncpy(newString, originalString, prefixLength);
        // Copy the replacement string
        strcpy(newString + prefixLength, replacementString);
        // Copy the suffix after the found position
        strcpy(newString + prefixLength + strlen(replacementString), foundPosition + strlen(sequenceToFind));
        // Update the original string with the new string
        strcpy(originalString, newString);
        // Free the memory allocated for the new string
        free(newString);
        // Search for the next occurrence
        foundPosition = strstr(originalString, sequenceToFind);
    }
}

void insertChar(char *str, char ch, int position) {
    int length = strlen(str);
    // Check if the position is valid
    if (position < 0 || position > length) {
        printf("Invalid position for insertion.");
        return;
    }
    // Shift the characters to the right to make space for the new character
    for (int i = length; i >= position; i--) {
        str[i + 1] = str[i];
    }
    // Insert the new character at the specified position
    str[position] = ch;
}

int comma(char * expression){
    for(int i=0;i<strlen(expression);i++){
        if(!isdigit(expression[i])&&expression[i]!=','&& expression[i]!='\n'&& expression[i]!='\0'){
            return -1;
        }
    }
    deleteSpace(expression);
    findAndReplace(expression,",,",",0,");
    insertChar(expression, 'a',0);
    findAndReplace(expression,"a,","0,");
    findAndReplace(expression,"a","");
    insertChar(expression, 'a',strlen(expression));
    findAndReplace(expression,",a",",0");
    findAndReplace(expression,"a","");
    return 0;
}

// Function to add a station to the linked list
void addStation(struct Station **head, const char *name) {
    struct Station *newStation = (struct Station *)malloc(sizeof(struct Station));
    if (newStation == NULL) {
        perror("Memory allocation error");
        exit(0);
    }

    // Allocate memory for the station name
    newStation->name = (char *)malloc(strlen(name) + 1);
    if (newStation->name == NULL) {
        perror("Memory allocation error");
        exit(0);
    }

    strcpy(newStation->name, name);
    newStation->next = *head;
    *head = newStation;
}

// Function to print all stations in the linked list
void printStations(struct Station *head) {
    while (head != NULL) {
        //printf("%s\n", head->name);
        head = head->next;
    }
}

// Function to free memory allocated for the linked list
void freeStations(struct Station *head) {
    while (head != NULL) {
        struct Station *temp = head;
        head = head->next;
        free(temp->name);
        free(temp);
    }
}

// Function to search for the index of a station in the linked list
int findStationIndex(struct Station *head, const char *stationName) {
    int index = 0;
    while (head != NULL) {
        if (strcmp(head->name, stationName) == 0) {
            return index;
        }
        head = head->next;
        index++;
    }
    return -1; // Station not found
}

char *getNthStationName(struct Station *list, int n) {
    int count = 0;
    struct Station *current = list;

    while (current != NULL) {
        if (count == n) {
            return current->name;
        }
        count++;
        current = current->next;
    }

    // If n is out of bounds, return NULL or handle appropriately
    return NULL;
}

int main() {
    int stationNumber=0;

    // Create a linked list to store stations
    struct Station *stationList = NULL;

    // Add stations to the linked list
    while (1) {
        char stationName[MAX_NAME_LENGTH];
        //printf("Enter the name of station %d: ", i + 1);        
        char a='\0';int index=0;
        while(a!=','&&a!='\n'){
            scanf("%c",&a);
            stationName[index++]=a;
        }
        stationName[index-1]='\0';
        //printf("%s",stationName);
        addStation(&stationList, stationName);
        stationNumber++;
        if (a=='\n'){
            goto label;
        }
    }
    label:
    //printf("\nstationNumber:%d",stationNumber);
    // Print the list of stations
    //printf("\nList of stations:\n");
    printStations(stationList);



     // Allocate memory for the 2D int array
    distanceMatrix = (int **)malloc(stationNumber * sizeof(int *));
    for (int i = 0; i < stationNumber; i++) {
        distanceMatrix[i] = (int *)malloc(stationNumber * sizeof(int));
    }

    // Your code to work with distanceMatrix goes here

    for(int i=0;i<stationNumber;i++){       
    // Example usage Matrix
    char *inputMatrixline = input(stationNumber*100);
    //printf("\nInput: %s\n", inputMatrixline);
    // comma(inputMatrixline);
    comma(inputMatrixline);

    // Delimiters are comma
    int matrixIndex=parseMatrix(stationNumber,inputMatrixline, ",",i);
    // Remember to free the allocated memory when done
    free(inputMatrixline);
    if(matrixIndex==-1){
        return 0;
    }   
    }
    printMatrixAligned(stationNumber);
    char source[MAX_NAME_LENGTH], destination[MAX_NAME_LENGTH];
    // Read strings separated by a comma
    scanf("%[^,],%s", source, destination);
    if (strlen(source) == 0 || strlen(destination) == 0 || isdigit(*source) || isdigit(*destination)) {
        printf("Invalid source station.");
        return 0;
    }
    // Find the index of source and destination in the stationList
    int sourceIndex = findStationIndex(stationList, source);
    int destIndex = findStationIndex(stationList, destination);

    if (sourceIndex == -1 ) {
        printf("Invalid source station.");
        return 0;
    }else if (destIndex == -1) {
        printf("Invalid destination station.");
        return 0;
    }else if (strcmp(source, destination) == 0) {// Check if the source and destination are the same
        printf("No journey, same source and destination station.");
        return 0;
    }
    sourceIndex=stationNumber-(sourceIndex+1);
    destIndex=stationNumber-(destIndex+1);
    // Check if there is a possible journey
    //printf("Source Index: %d\n", sourceIndex);
    //printf("Destination Index: %d\n", destIndex);
    Result result =dijkstra(stationNumber, sourceIndex, destIndex);
    if(result.err==-1){
    return 0;
   }
    // printf("Path: ");
    // for (int i = 0; i < stationNumber; i++) {
    //     printf("%d ", result.path[i]);
    // }
    //printf("\n");
    //printf("Path: ");


    //printf("\n");
    //printf("cost: ");
    //printf("%d ", result.cost);
    //printf("\n");
    //printf("distance: ");
    //printf("%d ", result.distance);
    printf("%d,%d\n", result.distance, result.cost);
    //printf("\n");
    for (int i = stationNumber; i >-1; i--) {
        if(result.path[i]!=-1){
        //printf("%d ", result.path[i]);
        int n = stationNumber - result.path[i]-1;  // Note: Indexing starts from 0
        char *nthStationName = getNthStationName(stationList, n);
        if (nthStationName != NULL) {
            printf("%s",nthStationName);
            if(i!=0){
                printf(",");
            }
        }
        }
    }
    // Free the allocated memory
    free(result.path);
    for (int i = 0; i < stationNumber; i++) {
        free(distanceMatrix[i]);
    }
    free(distanceMatrix);
    // Free the allocated memory
    freeStations(stationList);

    return 0;
}

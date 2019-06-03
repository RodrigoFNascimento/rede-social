#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 
#include <string.h>

static const char *addCommand = "ADD";
static const char *removeCommand = "REMOVE";
static const char *showCommand = "SHOW";

struct element {
    struct element *next;
    struct element *previous;
    char name[51];
} typedef element;

// Removes the last n characters from string
void removeLastCharacter(char* string, int n) {
    string[strlen(string)-n] = 0;
}

// Splits original in two on the first occurence of character
// and attributes the result strings to first and second
void splitString(char *original, char *first, char *second, char *character) {
    char* token;
    token = strtok(original, character);
    strcpy(first, token);
    token = strtok(NULL, character);
    strcpy(second, "");
    while (token != NULL) {
        strcat(second, token);
        strcat(second, " ");
        token = strtok(NULL, character);
    }
    removeLastCharacter(second, 2);
}

void readLine(char *line, char *command, char *name) {
    char *split = " ";
    splitString(line, command, name, split);
}

// Prints the names of every person on the list to the console
void printList(element *first) { 
    element *temp = first;  
  
    // If linked list is not empty 
    if (first != NULL)  
    { 
        // Keep printing nodes till we reach the first node again 
        do
        { 
            printf("%s\n", temp->name); 
            temp = temp->next; 
        } 
        while (temp != first); 
    } 
}

// Return 1 if any element on the list contains a node with
// name. Returns 0 otherwise.
int isOnList(element* head, char* name) {
    element *temp = head;  
  
    // If linked list is not empty 
    if (head != NULL)  
    { 
        // Keep printing nodes till we reach the first node again 
        do
        { 
            if (strcmp(head->name, name) == 0) {
                return 1;
            }
            temp = temp->next; 
        } 
        while (temp != head); 
    }
    return 0;
}

// Adds name to list
element* addName(char *name, element *list, FILE* output) {
    if (isOnList(list, name) == 1) {
        fprintf(output, "[ERROR] ADD ");
        fprintf(output, name);
        fprintf(output, "\n");
        return list;
    }

    if (list == NULL) {
        list = malloc(sizeof(element));
        strcpy(list->name, name);
        list->next = list;
        list->previous = list;
    } else {
        element *person = NULL;
        person = malloc(sizeof(element));
        strcpy(person->name, name);
        person->next = list;
        person->previous = list->previous;
        list->previous->next = person;
        list->previous = person;
    }
    fprintf(output, "[ OK  ] ADD ");
    fprintf(output, name);
    fprintf(output, "\n");
    return list;
}

// Removes name from list
element* removeName(char *name, element *list, FILE* output) {
    element *temp = list;  
    int i = 0;
    if (list != NULL)  
    {
        do
        { 
            if (strcmp(temp->name, name) == 0) {
                element* trash;
                trash = temp;
                temp->previous->next = temp->next;
                temp->next->previous = temp->previous;
                free(trash);
                fprintf(output, "[ OK  ] REMOVE ");
                fprintf(output, name);
                fprintf(output, "\n");
                i = 1;
                //return temp;
            }
            temp = temp->next;
        } 
        while (temp != NULL && temp != list && i == 0); 
    }
    if (i == 0) {
        fprintf(output, "[ERROR] REMOVE ");
        fprintf(output, name);
        fprintf(output, "\n");
    }
    return temp;
}

// Prints name to file
element* showName(char *name, element* list, FILE* output) {
    element *temp = list;
    int i = 0;
    // If linked list is not empty 
    if (list != NULL)
    { 
        // Keep printing nodes till we reach the first node again 
        do
        {
            //printf("%s\n", temp->name);
            if (strcmp(temp->name, name) == 0) {
                fprintf(output, "[ OK  ] ");
                fprintf(output, temp->previous->name);
                fprintf(output, "<-");
                fprintf(output, temp->name);
                fprintf(output, "->");
                fprintf(output, temp->next->name);
                fprintf(output, "\n");
                i = 1;
            }
            temp = temp->next;
        }
        while (temp != list && i == 0);
    }
    if (i == 0) {
        fprintf(output, "[ERROR] ?<-");
        fprintf(output, name);
        fprintf(output, "->?");
        fprintf(output, "\n");
    }
    return list;
}

// Executes one of the avaiable commands
element* executeCommand(char command[], char name[], element *head, FILE* output) {
    if (strcmp(command, addCommand) == 0) {
        return addName(name, head, output);
    } else if (strcmp(command, removeCommand) == 0) {
        return removeName(name, head, output);
    } else if (strcmp(command, showCommand) == 0) {
        return showName(name, head, output);
    }
}

int main(int argc, char* argv[]) {
	// Abrindo arquivos
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
    // Ler linhas do arquivo
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char command[7];
    char name[51];
    element *list = NULL;
    while ((read = getline(&line, &len, input)) != -1) {
        readLine(line, command, name);
        list = executeCommand(command, name, list, output);
    }
    printList(list);
	// ...
	// Fechando arquivos
	fclose(input);
	fclose(output);
	// Finalizando programa
	return 0;
}
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
    char name[50];
} typedef element;

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
}

void readLine(char *line, char *command, char *name) {
    char *split = " ";
    splitString(line, command, name, split);
}

void printLine(char line[]) {
    
}

bool addName(char *name, element *head) {
    element person = { &person, &person, *name};
    if (head != NULL) {
        person.next = head;
        person.previous = head->previous;
        head->previous = &person;
    }
    return true;
}

bool removeName(char name[], element *head) {

}

bool showName(char name[], element *head) {

}

bool executeCommand(char command[], char name[], element *head) {
    if (strcmp(command, addCommand) == 0) {
        return addName(name, head);
    } else if (strcmp(command, removeCommand) == 0) {
        return removeName(name, head);
    } else if (strcmp(command, showCommand) == 0) {
        return showName(name, head);
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
    element *head = malloc(sizeof(element));
    while ((read = getline(&line, &len, input)) != -1) {
        readLine(line, command, name);
        executeCommand(command, name, head);
        fprintf(output, command);
    }
	// ...
	// Fechando arquivos
	fclose(input);
	fclose(output);
	// Finalizando programa
	return 0;
}
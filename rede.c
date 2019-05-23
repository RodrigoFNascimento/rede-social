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

void readLine(char *line, char *command, char *name) {
    char *dummy = line;
    int i = 0;
    int length = strlen(line);
    while (*dummy != ' ') {
        strcat(dummy, command);
        dummy++;
        i++;
    }
    for (i; i < length; i++) {
        strcat(dummy, name);
        dummy++;
    }
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
	// Ilustrando uso de argumentos de programa
	printf("#ARGS = %i\n", argc);
	printf("PROGRAMA = %s\n", argv[0]);
	printf("ARG1 = %s, ARG2 = %s\n", argv[1], argv[2]);
	// Abrindo arquivos
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
    // Ler linhas do arquivo
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char command[6];
    char name[50];
    element *head = malloc(sizeof(element));
    while ((read = getline(&line, &len, input)) != -1) {
        readLine(line, command, name);
        printf("line = %s\n", line);
        printf("command = %s\n", command);
        printf("name = %s\n", name);
        fprintf(output, command);
    }
	// ...
	// Fechando arquivos
	fclose(input);
	fclose(output);
	// Finalizando programa
	return 0;
}
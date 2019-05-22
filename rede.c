#include <stdio.h>
#include <stdlib.h>

#define ADD = "ADD";
#define REMOVE = "REMOVE";
#define SHOW = "SHOW";

int main(int argc, char* argv[]) {
	// Ilustrando uso de argumentos de programa
	printf("#ARGS = %i\n", argc);
	printf("PROGRAMA = %s\n", argv[0]);
	printf("ARG1 = %s, ARG2 = %s\n", argv[1], argv[2]);
	// Abrindo arquivos
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
    // Ler linhas do arquivo
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char[6] command;
    char[50] name;
    while ((read = getline(&line, &len, input)) != -1) {
        readLine(line, &command, &name);
    }
	// ...
	// Fechando arquivos
	fclose(input);
	fclose(output);
	// Finalizando programa
	return 0;
}

void readLine(char line[], char* command, char* name) {
    int i = 0;
    int length = strlen(line);
    while (line[i] != ' ') {
        strcat(line[i], command);
        i++;
    }
    for (i; i < length; i++) {
        strcat(line[i], name);
    }
    return 0;
}

void printLine(char line[]) {
    return 0;
}

bool executeCommand(char command[], char name[]) {
    switch (command) {
        case ADD:
            add(name);
            break;
        case REMOVE:
            remove(name);
            break;
        case SHOW:
            show(name);
            break;
        default:
            break;
    }
}

void addName(char name[]) {

}

void removeName(char name[]) {

}

void showName(char name[]) {

}

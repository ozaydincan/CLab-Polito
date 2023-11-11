#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_IDENTIFIER_LENGTH 16
#define MAX_NAME_LENGTH 50
#define Date 10

typedef struct worker{
    char *name, *identifier;
    char *dateOfHire;
    int salary;
    struct worker *prev;
    struct worker *next;
}worker;

worker *readWorkers(char *filename);
worker *headInsert(worker *head);
void freeWorker(worker *linkedList);
void moveAndPrint(worker *linkedList, char *instructions, char *name);

int main(int argc, char **argv) {
    if (argc != 4){
        printf("Wrong Command Line Inputs!");
        exit(EXIT_FAILURE);
    }
    char *filename = argv[1], *name = argv[2], *instructions = argv[3];
    worker *head = readWorkers(filename);
    moveAndPrint(head, instructions, name);
    freeWorker(head);
    return 0;
}

worker  *readWorkers(char *filename){
    FILE *fp = fopen(filename, "r");
    if (!fp){
        fprintf(stderr,"Input file error");
        exit(EXIT_FAILURE);
    }
    worker *head =(worker*) malloc(sizeof(worker));
    int pay = 0;
    char *name =(char*) malloc(sizeof(char) * (MAX_NAME_LENGTH+1));
    char *id = (char *) malloc(sizeof(char) *(MAX_IDENTIFIER_LENGTH+1));
    char *date = (char *) malloc(sizeof(char) * (Date + 1));
    while (fscanf(fp ,"%s %s %s %d\n", name, id, date, &pay) != EOF){
        head->name = strdup(name),
        head->identifier = strdup(id);
        head->dateOfHire = strdup(date);
        head->salary = pay;
        head = headInsert(head);
    }
    fclose(fp);
    return head;
}

worker *headInsert(worker *head){
    worker *newNode =(worker*) malloc(sizeof(worker));
    if (newNode == NULL){
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    head->prev = newNode;
    newNode->next = head;
    newNode->prev = NULL;

    return newNode;
}

void moveAndPrint(worker *linkedList, char *instructions, char *name){
    int control = 0;
    while (linkedList){
        if (linkedList->name && strcmp(name, linkedList->name) == 0) {
            printf("%s %s %s %d\n", linkedList->name, linkedList->identifier, linkedList->dateOfHire, linkedList->salary);
            control = 1;
            break;
        }
        linkedList= linkedList->next;
    }
    if (control == 0){
        printf("Invalid name input!\nWorker not found!");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (instructions[i]){
        char move = instructions[i];
        if (move == '+'){
            if (linkedList->next->name){
                linkedList = linkedList->next;
            }
        }else if(move == '-'){
            if (linkedList->prev->name){
                linkedList = linkedList->prev;
            }
        } else{
            printf("Wrong input!");
            exit(EXIT_FAILURE);
        }
        printf("%s %s %s %d\n", linkedList->name, linkedList->identifier, linkedList->dateOfHire, linkedList->salary);
        i++;
    }
}

void freeWorker(worker *linkedList){
    while (linkedList){
        free(linkedList->name);
        free(linkedList->identifier);
        free(linkedList->dateOfHire);
        linkedList = linkedList->next;
    }
}
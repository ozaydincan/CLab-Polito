#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct node_s{
    char *word;
    int occurrence;
    struct node_s* next;
}Node;

Node* insertNode(Node* head, char* word);
Node* fillList(char* filename);
void display(Node *head, char *outfile);
void freeList(Node *head);

int main(int argc, char *argv[]) {
    if (argc != 3){
        fprintf(stderr,"Name of the program:%s\nName of the input file: %s\nName of the output file: %s\n", argv[0], argv[1], argv[2]);
        exit(EXIT_FAILURE);
    }
    char *infile = argv[1];
    char *outfile = argv[2];
    Node *linkedHead = fillList(infile);
    display(linkedHead, outfile);
    freeList(linkedHead);

    return 0;
}

Node* fillList(char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        perror("Input file couldn't be opened");
        exit(2);
    }
    Node *head = NULL;
    while (!feof(fp)){
        int i = 0, ch;
        char *temp =(char*) malloc(sizeof(char));
        while ((ch = fgetc(fp)) != ' ' && ch != '\n'&& ch != EOF){
            temp[i] = tolower(ch);
            temp = realloc(temp, sizeof(char)*(i+1));
            i++;
        }
        temp[i+1] = '\0';
        if (ch == EOF){
            break;
        }
        head = insertNode(head, temp);
        free(temp);
    }
    fclose(fp);
    return head;
}

void display(Node *head, char *outfile){
    FILE *f_out = fopen(outfile, "w+");
    fprintf(f_out,"Word frequencies:\n");
    while (head != NULL){
        fprintf(f_out, "%s %d\n", head->word, head->occurrence);
        head = head->next;
    }
    fclose(f_out);
}


Node* insertNode(Node* head, char *readWord){
    Node *new = head;
    while (new != NULL){
        char *temp = new->word;
        if (strcmp(temp, readWord) == 0){
            new->occurrence++;
            return head;
        }
        new = new->next;
    }
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL){
        perror("Memory allocation error");
        exit(4);
    }
    newNode->word = strdup(readWord);
    newNode->occurrence = 1;
    newNode->next = head;

    return newNode;
}

void freeList(Node *head){
    while (head != NULL){
        Node *temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}



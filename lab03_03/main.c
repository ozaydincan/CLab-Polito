#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 20

typedef struct products{
    char *model, *id;
    int price;
    struct products *next;
}product;

typedef struct cars{
    char *brandName, *id;
    product *products;
    struct cars *next;
}producer;

producer *readBrands(char *producerFile, char *productFile);
void readProducts(char *productFile, producer *cars);
producer *addNode(producer *head);
void displayModels(producer *head);
void freeCars(producer *head);

int main(int argc, char **argv) {
    if (argc != 3){
        fprintf(stderr,"CLI problem!");
        exit(EXIT_FAILURE);
    }else{
        printf("Program name: %s\nProducer File: %s\nProduct File: %s\n",argv[0], argv[1], argv[2]);
    }
    char *producerFile = argv[1], *productFile = argv[2];
    producer *brands= readBrands(producerFile, productFile);
    displayModels(brands);
    freeCars(brands);
    return 0;
}

producer *readBrands(char *producerFile, char *productFile){
    FILE *f_producer = fopen(producerFile, "r");
    if (f_producer == NULL){
        perror("Producer file couldn't be opened");
        exit(EXIT_FAILURE);
    }
    producer *car = malloc(sizeof(producer));
    char *manufacturer = (char *) malloc(sizeof(char)*(MAX_STRING_LENGTH+1));
    char *producerCode = (char *) malloc(sizeof(char)*(MAX_STRING_LENGTH+1));
    while (fscanf(f_producer, "%s %s\n", manufacturer, producerCode)!=EOF){
        car->brandName = strdup(manufacturer);
        car->id = strdup(producerCode);
        readProducts(productFile, car);
        car = addNode(car);
    }
    fclose(f_producer);
    return car;
}

producer *addNode(producer *head){
    producer *newNode =(producer*) malloc(sizeof(producer));
    newNode->next = head;
    return newNode;
}

void readProducts(char *productFile, producer *cars){
    FILE *fp = fopen(productFile, "r");
    if (fp == NULL){
        perror("");
        exit(EXIT_FAILURE);
    }
    char *identifier = malloc(sizeof(char)*(MAX_STRING_LENGTH+1));
    char *model = malloc(sizeof(char)*(MAX_STRING_LENGTH+1));
    int price = 0;
    producer *current = cars;
    product *head =(product*) malloc(sizeof(product));
    while (current){
        while (fscanf(fp, "%s %s %d\n", identifier, model, &price)!=EOF){
            if (strcmp(current->id, identifier)==0) {
                if (head->id != NULL) {
                    product *newNode = malloc(sizeof(product));
                    newNode->id = strdup(identifier);
                    newNode->model = strdup(model);
                    newNode->price = price;
                    head->next = newNode;
                    head = newNode;
                } else {
                    head->id = strdup(identifier);
                    head->model = strdup(model);
                    head->price = price;
                    current->products = head;
                }
            }
        }
        current = current->next;
    }
    fclose(fp);
}

void displayModels(producer *head){
    while (head){
        if (head->brandName != NULL){
            printf("Brand: %s\nProducts:\n", head->brandName);
            while (head->products){
                printf("%s %s %d\n", head->products->id, head->products->model, head->products->price);
                head->products = head->products->next;
            }
        }
        head = head->next;
    }
}

void freeCars(producer *head){
    while (head){
        if (head->brandName){
            while (head->products){
                free(head->products->id);
                free(head->products->model);
                head-> products = head->products->next;
            }
        }
        free(head->brandName);
        free(head->id);
        free(head->products);
        head = head->next;
    }
}
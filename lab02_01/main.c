#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct string{
    char *str;
};

struct matrix{
    char **dMatrix;
    int range;
};

struct matrix fillMatrix(char *filename);
void printMatrix(char **matrix, char *filename, int size);
void sortAlphabetical (struct string *s, int n);
void printStructs(struct string *s, char *filename);
void sortMatrix(char **str1, char** str2);

int main(int argc, char* argv[]) {
    if (argc == 3){
        printf("Name of the program: %s\n", argv[0]);
        printf("Name of the input file: %s\n", argv[1]);
        printf("Name of the output file: %s\n", argv[2]);
    } else if (argc > 3){
        perror("Too many arguments supplied!");
        return 1;
    }else {
        printf("Not enough arguments supplied!");
        return 2;
    }
    char *infile = argv[1], *outfile = argv[2];
    //struct string *words = fillStructs(infile);
    //printStructs(words, outfile);
    //free(words);

    struct matrix dynamicMatrix;
    dynamicMatrix = fillMatrix(infile);
    char **matrix = dynamicMatrix.dMatrix;
    printMatrix(matrix, outfile, dynamicMatrix.range);
    free(dynamicMatrix.dMatrix);
    return 0;
}

void sortAlphabetical (struct string *s, int n){
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(s[i].str, s[j].str) > 0) {
                char *tempS = s[i].str;
                if (strlen(s[i].str) < strlen(s[j].str)) {
                    s[i].str = realloc(s[i].str, sizeof(s[j].str));
                } else {
                    s[j].str = realloc(s[j].str, sizeof(s[i].str));
                }
                s[i].str = s[j].str;
                s[j].str = tempS;
            }
        }
    }
}

struct string *fillStructs(char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        perror("Problem occurred opening the input file");
    }
    int ch, i = 0, size;
    fscanf(fp, "%d\n", &size);
    struct string *words;
    words = malloc(size * sizeof(struct string));
    while (!feof(fp)) {
        words[i].str = (char *) malloc(sizeof(char));
        int k = 0;
        while ((ch = fgetc(fp)) != '\n'&& ch != EOF) {
            words[i].str[k] = ch;
            k++;
            words[i].str = realloc(words[i].str, sizeof(char) * (k + 1));
        }
        words[i].str[k] = '\0';
        i++;
    }
    sortAlphabetical(words, size);
    return words;
}

struct matrix fillMatrix(char *filename){
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL){
        printf("%s couldn't be opened.", filename);
        perror("");
        exit(3);
    }
    char **dynamicMatrix, ch;
    int size, i = 0;
    fscanf(fp, "%d\n", &size);
    dynamicMatrix = malloc((size)* sizeof(char*));
    while (!feof(fp) && i < size){
        dynamicMatrix[i] =  (char *)malloc(sizeof(char));
        int k = 0;
        while ((ch = fgetc(fp)) != '\n' && ch!=EOF) {
            dynamicMatrix[i][k] = ch;
            k++;
            dynamicMatrix[i] = realloc(dynamicMatrix[i], sizeof(char) * (k+1));
        }
        for (int j = 0; j <= i; j++){
            sortMatrix(&dynamicMatrix[j], &dynamicMatrix[i]);
        }
        i++;
    }
    fclose(fp);
    struct matrix dMatrix;
    dMatrix.range = size;
    dMatrix.dMatrix = dynamicMatrix;
    return dMatrix;
}

void printStructs(struct string *s, char *filename){
    FILE *fp = fopen(filename, "w+");
    if (fp == NULL){
        perror("Problem opening the output file");
    }
    int i = 0;
    fprintf(fp,"Words In Alphabetical Order:\n");
    while (s[i].str != NULL){
        fprintf(fp, "%s\n", s[i].str);
        i++;
    }
}

void sortMatrix(char **str1, char** str2){
    if (strcmp(*str1, *str2) > 0){
        char *temp;
        temp = *str1;
        *str1 = *str2;
        *str2 = temp;
    }
}

void printMatrix(char **matrix, char *filename, int size){
    FILE *fp = fopen(filename, "w+");
    if (fp == NULL){
        perror("Problem opening the output file");
    }
    fprintf(fp,"Words In Alphabetical Order:\n");
    for (int i = 0; i < size; i++){
        char *word = matrix[i];
        fprintf(fp, "%s\n", word);
    }
    fclose(fp);
}

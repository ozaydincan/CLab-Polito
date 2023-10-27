#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **readFile(char *filename);
void alphabeticSort(char **str1, char **str2);
void printToFile(char *outfile, char** M);



int main(int argc, char *argv[]) {
    if (argc == 3){
        printf("Name of the file: %s\n", argv[0]);
        printf("First argument: %s\n", argv[1]);
        printf("Second argument: %s\n", argv[2]);
    }
    else if (argc < 3){
       printf("Not enough arguments.");
       return 1;
    }else {
        printf("Too many arguments.");
        return 2;
    }
    char *filename = argv[1], *outfile = argv[2];
    char **matrix = readFile(filename);
    printToFile(outfile, matrix);
    return 0;
}

char **readFile(char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        perror("Input file couldn't be opened");
    }
    int rows, columns, i = 0;
    fscanf(fp ,"%d %d\n", &rows, &columns);
    int newSize = rows *columns;
    char **matrix = (char **)malloc(newSize * sizeof(char*));
    char ch;
    while (!feof(fp)){
        matrix[i] = (char*) malloc(sizeof(char));
        int j = 0;
        while ((ch = fgetc(fp)) && ch != EOF){
            if(ch == ' ' || ch == '\n'){
                break;
            }
            matrix[i][j] = ch;
            j++;
            matrix[i] = realloc(matrix[i], sizeof(char) * (j+1));
        }
        matrix[i][j+1] = '\0';
        for (int k = 0; k<=i; k++){
            alphabeticSort(&matrix[k], &matrix[i]);
        }
        i++;
    }
    return matrix;
}

void alphabeticSort(char **str1, char **str2){
    if (strcmp(*str1, *str2) > 0){
        char *temp;
        temp = *str1;
        *str1 = *str2;
        *str2 = temp;
    }
}

void printToFile(char *outfile, char **M){
    FILE *f_out = fopen(outfile, "w+");
    if (f_out == NULL){
        perror("Couldn't create output file");
    }
    int i = 0;
    fprintf(f_out, " \n");
    while (M[i] != NULL){
        fprintf(f_out, "%s\n", M[i]);
        i++;
    }
    rewind(f_out);
    fprintf(f_out, "%d\n", i-1);
}
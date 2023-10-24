#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_WORD_LENGTH 101


typedef struct {
    char *word;
    int occurrences;
}index_t;


index_t *readWord(char *filename, index_t words[]){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        perror("Problem opening file");
    }
    char *lines;
    int i = 0;
    bool flag = false, key = true;
    lines = malloc(sizeof (char *) * MAX_WORD_LENGTH);
    words = malloc(sizeof(index_t) * (i+1));
    while (!feof(fp)){
        fscanf(fp,"%s", lines);
        int k = 0;
        while (lines[k] != '\0' && !ispunct(lines[0])){
            lines[k] = tolower(lines[k]);
            k++;
        }
        if(key) {
            words[i].word = malloc(sizeof(char *) * (k+1));
            strcpy(words[i].word, lines);
            words[i].occurrences = 1;
            key = false;
            i++;
        }
        else if(!ispunct(lines[0])){
            for (int j = 0; j < i; j++) {
                char *compare = words[j].word;
                if (strcmp(compare, lines) == 0) {
                    words[j].occurrences++;
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                words = realloc(words, sizeof(index_t) * (i+1));
                words[i].word = malloc(sizeof(char *) * (k+1));
                strcpy(words[i].word, lines);
                words[i].occurrences = 1;
                i++;
            }
        }
        flag = false;
    }
    free(lines);
    fclose(fp);
    return words;
}


void readSecond(char *filename, index_t *s){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        perror("Problem accessing file.");
    }
    int i = 0, ch;
    bool flag = true;
    char **charArray;
    while (!feof(fp)){
        if (flag){
            ch = fgetc(fp);
            charArray = (char **)malloc(((int) ch-48)+1 * sizeof(char *));
            flag = false;
        }
        int j = 0;
        charArray[i] = (char *)malloc(sizeof(char)*(j+1));
        while (ch != '\n'&& (ch != EOF)){
            charArray[i] = realloc(charArray[i], sizeof(char*) * (j+1));
            charArray[i][j] = (char) ch;
            j++;
            ch = fgetc(fp);
        }
        if (ch == '\n'){
            i++;
            ch = fgetc(fp);
        }
    }
    fclose(fp);
    int len = i;
    int l = 0;
    while(s[l].word != NULL){
        for (int k = 0; k < len; k++) {
            if (strcmp(s[l].word, charArray[k]) == 0) {
                printf("%s: %d\n", s[l].word, s[l].occurrences);
            }
        }
        l++;
    }
    free(s);
    free(charArray);
}


int main(void) {
    index_t *words;
    char *filename = "/Users/canozaydin/CLionProjects/lab00_01/lab01_01_A/cmake-build-debug/lab00_01.txt";
    char *secondFile = "/Users/canozaydin/CLionProjects/lab00_01/lab01_01_A/cmake-build-debug/lab00_01B.txt";
    words = readWord(filename, words);
    readSecond(secondFile, words);
    return 0;
}
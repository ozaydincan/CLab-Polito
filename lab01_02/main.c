#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct {
    char *identifier;
    double *x, *y;
    double area, perimeter;
} Rectangle;


Rectangle *fillRectangles(Rectangle s[], char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        perror("Problem opening file.");
    }
    int ch, i = 0;
    fscanf(fp, "%d\n", &ch);
    s = malloc(ch * sizeof(Rectangle));
    for (int j = 0; j < ch; j++){
        s[j].x = malloc(sizeof(double) *2);
        s[j].y = malloc(sizeof(double) *2);
        s[j].identifier = malloc(sizeof(char) *5);
    }
    char *tempId = malloc(sizeof(s[i].identifier));
    double tempX, tempY;
    bool flag = false;
    while(!feof(fp)){
        fscanf(fp, "%s %lf %lf\n", tempId, &tempX, &tempY);
        for (int k = 0; k <= i; k++){
            if (strcmp(tempId, s[k].identifier) == 0){
                flag = true;
                s[k].x[1] = tempX;
                s[k].y[1] = tempY;
                s[k].area = fabs(s[k].x[0] - s[k].x[1]) * fabs(s[k].y[0] - s[k].y[1]);
                s[k].perimeter = 2 * (fabs(s[k].x[0] - s[k].x[1]) + fabs(s[k].y[0] - s[k].y[1]));
                break;
            }
        }
        if (!flag){
            strcpy(s[i].identifier, tempId);
            s[i].x[0] = tempX;
            s[i].y[0] = tempY;
            i++;
        }
        flag = false;
    }
    free(tempId);
    return s;
}


void printStructsArea(FILE *fp, int n, Rectangle *sortedRecs){
    for (int i = 0; i < n; i++){
        fprintf(fp,"Name: %s\nArea: %.2lf\n\n",sortedRecs[i].identifier, sortedRecs[i].area);
    }
    fclose(fp);
}

void printStructsPerimeter(FILE *fp, int n, Rectangle *sortedRecs){
    for (int i = 0; i < n; i++){
        fprintf(fp,"Name: %s\nPerimeter: %.2lf\n\n",sortedRecs[i].identifier, sortedRecs[i].perimeter);
    }
    fclose(fp);
}



void sortByArea(Rectangle *rectangles, int size){
    FILE *f_out = fopen("e02area.txt", "w+");

    if (f_out == NULL){
        perror("Couldn't open file!");
    }

    for (int i = 0; i < size-1; i++){
        int minIndex = i;
        for (int j = i+1; j < size; j++){
            if (rectangles[j].area < rectangles[minIndex].area){
                minIndex = j;
            }
        }
        if (minIndex != i){
            Rectangle temp = rectangles[minIndex];
            rectangles[minIndex] = rectangles[i];
            rectangles[i] = temp;
        }
    }
    printStructsArea(f_out,size ,rectangles);
}

void sortByPerimeter(Rectangle *rectangles, int size){
    FILE *f_out = fopen("e02perimeter.txt", "w+");
    if (f_out == NULL){
        perror("Couldn't open file!");
    }

    for (int i = 0; i < size-1; i++){
        int minIndex = i;
        for (int j = i+1; j < size; j++){
            if (rectangles[j].perimeter < rectangles[minIndex].perimeter){
                minIndex = j;
            }
        }
        if (minIndex != i){
            Rectangle temp = rectangles[minIndex];
            rectangles[minIndex] = rectangles[i];
            rectangles[i] = temp;
        }
    }
    printStructsPerimeter(f_out,size ,rectangles);
}


int main() {
    Rectangle *recs;
    char *filename = "e02.txt";
    recs = fillRectangles(recs, filename);

    int n = 0;
    while (recs[n].identifier != NULL){
        n++;
    }
    sortByArea(recs, n);
    sortByPerimeter(recs, n);
    return 0;
}

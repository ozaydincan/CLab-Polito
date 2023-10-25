#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_NAME_LENGTH 30

typedef struct {
    char *name;
    int identifier, lap;
    double *times, avg;
} Cyclists;


void getCommand(char *cmd, Cyclists s[]){
    fprintf(stdout, "Choose a command (list, best, detail Name or stop): ");
    char *name = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
    int i = 0;
    scanf("%s", cmd);
    if (strcmp(cmd, "list") == 0) {
        while (s[i].name != NULL){
            printf("Name: %s #ID: %d #Laps: %d #Average Lap: %.2lf\n", s[i].name, s[i].identifier, s[i].lap,s[i].avg);
            i++;
        }
    }
    else if(strcmp(cmd, "best") == 0){
        printf("Name: %s #ID: %d #Laps: %d #Average Lap: %.2lf\n", s[0].name, s[0].identifier, s[0].lap, s[0].avg);
        for (int j = 0; j < s[0].lap; j++){
            printf("Lap %d: %.2lf ", (j+1), s[0].times[j]);
        }
        printf("\n");
    }
    else if(strcmp(cmd, "detail") == 0){
        bool flag = true;
        scanf("%s", name);
        while (s[i].name != NULL){
            if (strcmp(s[i].name, name) == 0){
                flag = false;
                printf("#ID: %d #Laps: %d #Average Lap: %.2lf ", s[i].identifier, s[i].lap, s[i].avg);
                for (int j = 0; j < s[i].lap; j++){
                    printf("Lap %d: %.2lf ", (j+1), s[0].times[j]);
                }
                printf("\n");
                break;
            }
            i++;
        }
        if(flag){
            printf("Invalid name!\n");
        }
    } else if (strcmp(cmd, "stop") == 0){
        printf("Exiting program...");
    } else{
        printf("Invalid input.\n");
    }
}


void selectionSort (Cyclists cyclist[], int size){
    for (int k = 0; k < size -1; k++){
        int maxId = k;
        for (int l = k+1; l < size; l++){
            if (cyclist[l].avg > cyclist[maxId].avg){
                maxId = l;
            }
        }
        if (maxId != k){
            Cyclists temp = cyclist[k];
            cyclist[k] = cyclist[maxId];
            cyclist[maxId] = temp;
        }
    }
}


Cyclists * fillCyclists(char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        perror("Problem occurred opening file.");
    }
    int size, i = 0;
    fscanf(fp,"%d", &size);
    Cyclists *cyclist = malloc(size * sizeof(Cyclists));
    for (; i < size; i++) {
        cyclist[i].name = (char*) malloc(MAX_NAME_LENGTH * sizeof(char ));
        fscanf(fp, "%s %d %d", cyclist[i].name, &cyclist[i].identifier, &cyclist[i].lap);

        cyclist[i].times = (double *) malloc((cyclist[i].lap) * sizeof(double));

        int j = 0;
        double sumTime = 0;
        for (; j < cyclist[i].lap; j++) {
            fscanf(fp,"%lf", &cyclist[i].times[j]);
            sumTime += cyclist[i].times[j];
        }
        cyclist[i].avg = sumTime / cyclist[i].lap;
    }
    fclose(fp);
    selectionSort(cyclist, size);
    return cyclist;
}


int main(void) {
    char *filename = "e03.txt";
    char cmd[256];

    Cyclists *cyclists = fillCyclists(filename);
    while (strcmp(cmd, "stop") != 0){
        getCommand(cmd, cyclists);
    }

    free(cyclists);
    return 0;
}

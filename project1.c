/*
    Name: Quoc Viet Nguyen
    Student Number: 22112348
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

#include "quickSort.h"
#include "mergeSort.h"
#include "extraFunc.h"
#include "enumSort.h"

// static int MAX_LENGTH = 10000000;

int compare_function(const void *a,const void *b) {
    double *x = (double *) a;
    double *y = (double *) b;
    // return *x - *y; // this is WRONG...
    if (*x < *y) return -1;
    else if (*x > *y) return 1; 
    return 0;
}

/*  Input handler to make main() cleaner
*/
int inputHandler(int numThreads, int arMaxLen, char *action)
{
    printf("Num threads passed: %d\n", numThreads);
    omp_set_num_threads(numThreads); 
    printf("OpenMP running with %d threads \n", omp_get_max_threads() );

    // int arrLen = (int)(((double)rand()/(double)(RAND_MAX)) * MAX_LENGTH);
    int arrLen = arMaxLen;

    printf("Max length: %d\n", arrLen);
    
    // Generate random doubleing point array
    double *arr = malloc(arrLen* sizeof(double));
    arrayGen(arr, arrLen);
    // for (int i=0; i < arrLen; i++){
    //     printf("%lf, ", arr[i]);
    // } 
    // printf("\n\n");

    double *modelAr = copyArray(arr, arrLen);
    struct timeval start, end;
    
    gettimeofday(&start, NULL);
    qsort(modelAr, arrLen, sizeof(double), compare_function);
    gettimeofday(&end, NULL);

    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    printf("Library sort time spent = %12.10f\n\n",delta);

    // ACTION HANDLING
    // action specified what sorting algo to display
    // m for merge sort
    // q for quick sort
    // e for enum sort
    // d for default: no enum sort
    // a for all
    if(action[0] == 'a' || action[0] == 'm' || action[0] == 'd'){
        // Merge sort check
        gettimeofday(&start, NULL);
        double *mergeSortArr = msHandler(arr, arrLen);
        gettimeofday(&end, NULL);

        double msDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        printf("Merge sort time spent = %12.10f\n",msDelta);

        printf("Merge sorted array check:\n");

        if (arrayCheck(modelAr, mergeSortArr, arrLen))
        {
            printf("Sort algo broken\n");
            exit(EXIT_FAILURE);
        }
        
        printf("End, empty means good\n\n");

        // Parallelization merge sort check
        gettimeofday(&start, NULL);
        double *paraMergeAr = paraMSHandler(arr, arrLen);
        gettimeofday(&end, NULL);

        double paraMSDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        printf("Para Merge sort time spent = %12.10f\n",paraMSDelta);

        printf("Para Merge sorted array check:\n");

        if (arrayCheck(modelAr, paraMergeAr, arrLen))
        {
            printf("Sort algo broken\n");
            exit(EXIT_FAILURE);
        }

        printf("End, empty means good\n\n");

        printf("Merg sort parallelization time reduction (percent): %lf \n\n", ((msDelta - paraMSDelta) / msDelta) * 100);

        free(mergeSortArr);
        free(paraMergeAr);
    }
    if(action[0] == 'a' || action[0] == 'q' || action[0] == 'd'){
        // Quick sort check...
        gettimeofday(&start, NULL);
        double *quickSortArr = quickSort(arr, arrLen);
        gettimeofday(&end, NULL);

        double qsDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        printf("Quick sort time spent = %12.10f\n",qsDelta);

        printf("Quick sorted array check:\n");

        if (arrayCheck(modelAr, quickSortArr, arrLen))
        {
            printf("Sort algo broken\n");
            exit(EXIT_FAILURE);
        }

        printf("End, empty means good\n\n");

        // Parallelization quick sort check
        gettimeofday(&start, NULL);
        double *paraQSArr = paraQSHandler(arr, arrLen);
        gettimeofday(&end, NULL);

        double paraQSDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        printf("Para Quick sort time spent = %12.10f\n",paraQSDelta);

        printf("Para Quick sorted array check:\n");

        if (arrayCheck(modelAr, paraQSArr, arrLen))
        {
            printf("Sort algo broken\n");
            exit(EXIT_FAILURE);
        }

        printf("End, empty means good\n\n");
        
        printf("Quick sort parallelization time reduction (percent): %lf \n\n", ((qsDelta - paraQSDelta) / qsDelta) * 100);
    }
    if(action[0] == 'a' || action[0] == 'e'){
        // Enumeration sort check
        gettimeofday(&start, NULL);
        double *enumSortAr = enumSort(arr, arrLen);
        gettimeofday(&end, NULL);

        double enumDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        printf("Enum sort time spent = %12.10f\n",enumDelta);

        printf("Enum sorted array check:\n");

        if (arrayCheck(modelAr, enumSortAr, arrLen))
        {
            printf("Sort algo broken\n");
            exit(EXIT_FAILURE);
        }

        printf("End, empty means good\n\n");
        
        // Parallelization enumeration sort check
        gettimeofday(&start, NULL);
        double *paraEnumAr = paraEnumSort(arr, arrLen);
        gettimeofday(&end, NULL);
        double paraEDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        printf("Para Enum sort time spent = %12.10f\n",paraEDelta);

        printf("Para Enum sorted array check:\n");

        if (arrayCheck(modelAr, paraEnumAr, arrLen))
        {
            printf("Sort algo broken\n");
            exit(EXIT_FAILURE);
        }

        printf("End, empty means good\n\n");
        
        printf("Enum sort parallelization time reduction (percent): %lf \n\n", ((enumDelta - paraEDelta) / enumDelta) * 100);
    }

    return 0;
}

/*  Duplicate of input handler but modified to return time runs of each sorting algorithm.
    Also, no printf().
*/
double *justRun(int arMaxLen, char *action)
{
    double *timeList = malloc(4 * sizeof(double));

    // int arrLen = (int)(((double)rand()/(double)(RAND_MAX)) * MAX_LENGTH);
    int arrLen = arMaxLen;
    
    // Generate random doubleing point array
    double *arr = malloc(arrLen* sizeof(double));
    arrayGen(arr, arrLen);
    // for (int i=0; i < arrLen; i++){
    //     printf("%lf, ", arr[i]);
    // } 
    // printf("\n\n");

    double *modelAr = copyArray(arr, arrLen);
    struct timeval start, end;
    
    // gettimeofday(&start, NULL);
    qsort(modelAr, arrLen, sizeof(double), compare_function);
    // gettimeofday(&end, NULL);

    // double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    // ACTION HANDLING
    // action specified what sorting algo to display
    // m for merge sort
    // q for quick sort
    // e for enum sort
    // d for default: no enum sort
    // a for all
    if(action[0] == 'a' || action[0] == 'm' || action[0] == 'd'){
        // Merge sort check
        gettimeofday(&start, NULL);
        double *mergeSortArr = msHandler(arr, arrLen);
        gettimeofday(&end, NULL);

        double msDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

        if (arrayCheck(modelAr, mergeSortArr, arrLen))
        {
            printf("Sort algo broken\n");
            exit(EXIT_FAILURE);
        }
        timeList[0] = msDelta;

        // Parallelization merge sort check
        gettimeofday(&start, NULL);
        double *paraMergeAr = paraMSHandler(arr, arrLen);
        gettimeofday(&end, NULL);

        double paraMSDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

        if (arrayCheck(modelAr, paraMergeAr, arrLen))
        {
            printf("Sort algo broken\n");
            exit(EXIT_FAILURE);
        }

        timeList[1] = paraMSDelta;

        free(mergeSortArr);
        free(paraMergeAr);
    }
    if(action[0] == 'a' || action[0] == 'q' || action[0] == 'd'){
        // Quick sort check...
        gettimeofday(&start, NULL);
        double *quickSortArr = quickSort(arr, arrLen);
        gettimeofday(&end, NULL);

        double qsDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

        if (arrayCheck(modelAr, quickSortArr, arrLen))
        {
            printf("Sort algo broken\n");
            exit(EXIT_FAILURE);
        }
        
        timeList[2] = qsDelta;

        // Parallelization quick sort check
        gettimeofday(&start, NULL);
        double *paraQSArr = paraQSHandler(arr, arrLen);
        gettimeofday(&end, NULL);

        double paraQSDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;


        if (arrayCheck(modelAr, paraQSArr, arrLen))
        {
            printf("Sort algo broken\n");
            exit(EXIT_FAILURE);
        }

        timeList[3] = paraQSDelta;

        free(quickSortArr);
        free(paraQSArr);
    }
    // if(action[0] == 'a' || action[0] == 'e'){
    //     // Enumeration sort check
    //     gettimeofday(&start, NULL);
    //     double *enumSortAr = enumSort(arr, arrLen);
    //     gettimeofday(&end, NULL);

    //     double enumDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    //     if (arrayCheck(modelAr, enumSortAr, arrLen))
    //     {
    //         printf("Sort algo broken\n");
    //         exit(EXIT_FAILURE);
    //     }

    //     timeList[4] = enumDelta;
        
    //     // Parallelization enumeration sort check
    //     gettimeofday(&start, NULL);
    //     double *paraEnumAr = paraEnumSort(arr, arrLen);
    //     gettimeofday(&end, NULL);
    //     double paraEDelta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    //     if (arrayCheck(modelAr, paraEnumAr, arrLen))
    //     {
    //         printf("Sort algo broken\n");
    //         exit(EXIT_FAILURE);
    //     }

    //     timeList[5] = paraEDelta;

    //     free(enumSortAr);
    //     free(paraEnumAr);
    // }
    
    free(arr);
    free(modelAr);

    return timeList;
}

int runReport(int numThreads, int arMaxLen, char *action, int timesRun){
    printf("Num threads passed: %d\n", numThreads);
    omp_set_num_threads(numThreads); 
    printf("OpenMP running with %d threads \n", omp_get_max_threads() );

    double totalTimeMS = 0;
    double totalTimeParaMS = 0;
    double totalTimeQS = 0;    
    double totalTimeParaQS = 0;
    // double totalTimeES = 0;
    // double totalTimeParaES = 0;

    for (int i = 0; i < timesRun; i++)
    {
        double *timeList = justRun(arMaxLen, "d");

        totalTimeMS += timeList[0];
        // printf("Run %d: Merge Sort time:%12.10f\n", i + 1, timeList[0]);
        totalTimeParaMS += timeList[1];
        // printf("Run %d: Para Merge Sort time:%12.10f\n", i + 1, timeList[0]);

        totalTimeQS += timeList[2];
        // printf("Run %d: Quick Sort time:%12.10f\n", i + 1, timeList[0]);
        totalTimeParaQS += timeList[3];

        // totalTimeES += timeList[4];
        // totalTimeParaES += timeList[5];

        free(timeList);
    }
    
    double avTimeMS = totalTimeMS / (double)timesRun;
    double avTimeParaMS = totalTimeParaMS / (double)timesRun;

    double avTimeQS = totalTimeQS / (double)timesRun;
    double avTimeparaQS = totalTimeParaQS / (double)timesRun;

    // double avTimeES = totalTimeES / (double)timesRun;
    // double avTimeParaES = totalTimeParaES / (double)timesRun;

    printf("Average time for merge sort: %12.10f\n", avTimeMS);
    printf("Average time for parallel merge sort: %12.10f\n", avTimeParaMS);
    printf("Average Merge sort parallelization time reduction (percent): %12.10f \n\n", ((avTimeMS - avTimeParaMS) / avTimeMS) * 100);


    printf("\n");

    printf("Average time for quick sort: %12.10f\n", avTimeQS);
    printf("Average time for parallel quick sort: %12.10f\n", avTimeparaQS);
    printf("Average Quick sort parallelization time reduction (percent): %12.10f \n\n", ((avTimeQS - avTimeparaQS) / avTimeQS) * 100);

    // printf("\n");

    // printf("Average time for enum sort: %12.10f\n", avTimeES);
    // printf("Average time for parallel enum sort: %12.10f\n", avTimeParaES);
    // printf("Average Enum sort parallelization time reduction (percent): %12.10f \n\n", ((avTimeES - avTimeParaES) / avTimeES) * 100);

    return 0;
}

int giveHelp()
{
    printf("""Main takes in at least one argument in format: ./{executable}\
            \nAt most 4 arguments. Example format below:\
            \n1 arg:  ./{executable} -> This runs default settings: 8 threads, 10 000 000 array length, run serialization and parallelization for all except enum sort; only once\
            \n2 args: ./{executable} report -> This runs default settings in loop of 10 times, then calculate the average time of each and average time reduction of each\
            \n3 args: ./{executable} report {(int) number} -> Same as 2 args but run in loop of secify number\
            \n4 args: ./{executable} {(int) num threads} {(int) array length} {(char) action} -> Refer to 1 args, runs same but with specify number.\
            \n{action}: Includes following tags: d for default run; q for quick sort run; m for merge sort run; e for enumeration sort run; a for all sort run\
            \n""");

    return 0;
}

/*----------------------------------------------------------------
Main takes in at least one argument in format: ./{executable}
At most 4 arguments. Example format below:
1 arg:  ./{executable} -> This runs default settings: 8 threads, 10 000 000 array length, run serialization and parallelization for all except enum sort; only once
2 args: ./{executable} report -> This runs default settings in loop of 10 times, then calculate the average time of each and average time reduction of each
3 args: ./{executable} report {(int) number} -> Same as 2 args but run in loop of secify number
4 args: ./{executable} {(int) num threads} {(int) array length} {(char)action} -> Refer to 1 args, runs same but with specify number.
{action}: Includes following tags: d for default run; q for quick sort run; m for merge sort run; e for enumeration sort run; a for all sort run
*/
int main(int argc, char *argv[]) {
    printf("CITS3402 - Project 1: Quoc Viet Nguyen 22112348\n\n");
    srand(time(NULL));
    if (argc <2){
        int numThreads = 8;
        int arMaxLen = 10000000;
        char *action = "d";
        printf("Running default settings: %d threads, %d array length, and action %c\n", numThreads, arMaxLen, *action);
        
        inputHandler(numThreads, arMaxLen, action);

        exit(EXIT_SUCCESS);
    }else if (argc == 2 || argc == 3)
    {
        char *reportRun = "report";
        if (strcmp(reportRun, argv[1]))
        {
            giveHelp();

            exit(EXIT_FAILURE);
        }

        int numThreads = 8;
        int arMaxLen = 1000;
        char *action = "d";
        int timesRun = 20;
        if (argc == 3)
        {
            if (isInteger(argv[2]))
            {
                arMaxLen = atoi(argv[2]);
            }
            else
            {
                printf("Wrong input type. Type: './{executable} help' for more information \n");
                exit(EXIT_FAILURE);
            }            
        }
        
        printf("Running report with settings: %d threads, %d array length, action %c, and %d times loop\n", numThreads, arMaxLen, *action, timesRun);
        runReport(numThreads, arMaxLen, action, timesRun);

        exit(EXIT_SUCCESS);
    }    
    else if (argc == 4)
    {
        printf("%d :: %d\n", isInteger(argv[1]), isInteger(argv[2]));
        if (isInteger(argv[1]) == 0 || isInteger(argv[2]) == 0 || (argv[3][0] != 'd' && argv[3][0] != 'q' && argv[3][0] != 'm' && argv[3][0] != 'a' && argv[3][0] != 'e'))
        {
            printf("Wrong input type. Type: './{executable} help' for more information \n");
            exit(EXIT_FAILURE);
        }
        
        // printf("Here")
        int numThreads = atoi(argv[1]);
        int arMaxLen = atoi(argv[2]);
        char *action = argv[3];

        inputHandler(numThreads, arMaxLen, action);

        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Wrong input type. Type: './{executable} help' for more information \n");
        exit(EXIT_FAILURE);
    }
    

    return 0;    
}
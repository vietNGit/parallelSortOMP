project1make: project1.c quickSort.c mergeSort.c enumSort.c extraFunc.c
	gcc -std=c99 -Wall -Werror -pedantic -fopenmp project1.c quickSort.c mergeSort.c enumSort.c extraFunc.c -o sort
# parallelSortOMP
Sorting algorithms implement in serial and parallel OpenMP versions.

Sorting algorithms covered: Merge Sort, Quick Sort, and Enumeration Sort.

The main file to run everything is in project1.c.

## To compile:
Simply type make in the terminal. The compiled out file is set to be
“sort”

## To run:
There are 2 options to run “sort”:
- Option 1: write in terminal “./sort” : This will run the default settings with: 8
threads, 10 000 000 array length, and action “d” means run serial and parallel sort
algorithm of Merge Sort and Quick Sort.
- Option 2: Specify inputs, must full-fill all 3 inputs:
  - ./sort {Number of threads} {Array length} {Action}
  - Number of threads: Specify the number of threads for parallel runs
  - Array length: Specify the array size to be randomly generated
  - Action: One of 4 options, all will run serial and parallel solutions for each sort:
  - “default” for merge sort and quick sort run
  - “merge” for merge sort only run
  - “quick” for quick sort only run
  - “enum” for enumeration sort only run
  - “all” for all sort algorithms run

## Requirements:
- Environment: Ubuntu 20.04 or above
- Packages required: openmpi-bin openmpi-common openmpi-doc libopenmpi-dev
- To install packages: `sudo apt-get install openmpi-bin openmpi-common openmpi-doc libopenmpi-dev`

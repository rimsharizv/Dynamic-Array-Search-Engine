// 
// CS 211 - Project 1: Storing data by user into dynamically stored arrays to then search values from it, and report data
// Rimsha Rizvi (659249234)
// 


#include <stdio.h>
#include <stdlib.h>



// doubleArray - doubles the size of the array
void doubleArray(int darr[], int *size)
{
  int *temp = darr;
  darr = (int *) malloc ( *size * 2 * sizeof(int) );
  int i;
  for ( i = 0 ; i < *size ; i++) {
    darr[i] = temp[i];
  }
  free (temp); // Freeing the original array
  *size = *size * 2;
}


// arrayCopy - copies the contents of an array to another array.
void arrayCopy (int fromArray[], int toArray[], int size) {
  for (int i = 0; i < size; i++) {
    toArray[i] = fromArray[i];
  }
}


// myFavoriteSort - sorts the array being passed in.
void myFavoriteSort(int arr[], int size)
{
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = 0; j < size - 1; j++)
    {
      if (arr[j] > arr[j+1])
      {
        int temp = arr[j+1];
        arr[j+1] = arr[j];
        arr[j] = temp;
      }
    }
  }
}


void linearSearch(int darr[], int size, int search, int *found, int *comparisions, int *position) {

  int count = 0;

  for (int i = 0; i < size; i++)
  {
    //printf("search: %d, darr: %d\n", search, darr[i]);
    if (darr[i] == search)    //If required element is found
    {
      *found = 1;
      *comparisions = (i+1); //number of comparisions+1 as element starts index from 0
      *position = i;
      return;
    }
    count++;
  }
  if (count == size){
    found = 0;
  }
}


void binarySearch(int copyDarr[], int size, int search, int *found, int *comparisions, int *position) {

  int first;
  int last;
  int middle;

  first = 0;
  last = size - 1;
  middle = (first+last)/2;

  int count = 0;

  while (first <= last) {

    if (copyDarr[middle] < search) {
      first = middle + 1;
      count++;
    }
    else if (copyDarr[middle] == search) {

      *found = 1;
      count++;
      *comparisions = count;
      *position = middle;
      return;
    }
    else{
      last = middle - 1;
      count++;
    }
    middle = (first + last)/2;
  }
  if (first > last){
    *found = 0;
  }

  *comparisions = count;
}


int main()
{
  int values; // values that are input by the user

  int *darr;
  int size = 100;
  darr = (int *) malloc (size * sizeof(int) );

  // prompt to input values
  printf("Enter a number of elements to store in a dynamic array.\n");
  printf("Input -999 to end the list.\n");


  int i = 0;
  scanf("%d", &values);
  while (values != -999)
  {
    if (i >= size)
    {
      doubleArray(darr, &size);
      // printf("Size: %d\n", size);
    }
    // storing the input value into the array 
    darr[i] = values;
    i++;
    // enter the next input
    scanf("%d", &values);
  }

  // make a copy of the array
  int *copyDarr = (int *)malloc(sizeof(int) * size);
  arrayCopy (darr, copyDarr, i); 

  // sort the array being passed
  myFavoriteSort(copyDarr, i);

  int search;

  printf("Enter numbers to search\n");
  scanf("%d", &search);

  int k = 0;
  int size_2 = 5;
  int *arr_2;
  arr_2 = (int *) malloc (size_2 * sizeof(int) );

   while (search != -999)
  {
    if (k >= size_2)
    {
      doubleArray(arr_2, &size_2);
    }
    // storing the input value into the array 
    arr_2[k] = search;
    k++;
    // enter the next input
    scanf("%d", &search);
  }


  int found;
  int comparisions;
  int position;

  //linear search on unsorted array
  printf("\n");
  printf("LINEAR SEARCH OUTPUTS:\n");
  printf("\n");

  for (int t = 0; t < k; t++){
    found = 0;
    comparisions = 0;

    linearSearch(darr, i, arr_2[t], &found, &comparisions, &position);
    if (found == 1){
      printf("The value %d was FOUND in the unsorted array.\n", arr_2[t]);
      printf("Comparisions made: %d\n", comparisions);
      printf("Position found: %d\n", position);
      printf("\n");
    }
    else{
      printf("The value %d was NOT FOUND in the unsorted array.\n", arr_2[t]);
      comparisions = i;
      printf("Comparisions made: %d\n", comparisions);
      printf("\n");
    }

  }


  //binary search on sorted array
  printf("\n");
  printf("BINARY SEARCH OUTPUTS:\n");
  printf("\n");

  for (int t = 0; t < k; t++){

    binarySearch(copyDarr, i, arr_2[t], &found, &comparisions, &position);
    if (found == 1){
      printf("The value %d was FOUND in the sorted array.\n", arr_2[t]);
      printf("Comparisions made: %d\n", comparisions);
      printf("Position found: %d\n", position);
      printf("\n");
    }
    else{
      printf("The value %d was NOT FOUND in the sorted array.\n", arr_2[t]);
      printf("Comparisions made: %d\n", comparisions);
      printf("\n");
    }

  }


  return 0;

}

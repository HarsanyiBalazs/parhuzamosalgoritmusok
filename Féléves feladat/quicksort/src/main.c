#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <windows.h>

int THREAD_LIMIT;
int CURRENT_THREAD_NUMBER=1;
pthread_mutex_t thread_number_mutex = PTHREAD_MUTEX_INITIALIZER;


void quicksort(int* values, int p, int r);

/**
 * Description of a task for a thread.
 */
typedef struct Task
{
  int* values;
  int p;
  int r;
} Task;


/**
 * Generate the data for experimentation.
 */
int* generate_data(long size)
{
  int* data;
  int i;

  data = (int*)malloc(size * sizeof(int));
  for (i = 0; i < size; ++i) 
  {
    data[i] =rand()%(1000);
  }

  return data;
}

/**
 * Partition the array around the pivot element.
 */
int partition(int* values, int p, int r, int x)
{
    int i, j;
    int temp;

    i = p - 1;
    j = r + 1;
    while (i < j) 
    {
        do 
        {
            ++i;
        } while (values[i] < x);
        do 
        {
            --j;
        } while (values[j] > x);
        if (i < j) 
        {
        temp = values[i];
        values[i] = values[j];
        values[j] = temp;
        }
    }

    return j;
}



void* quicksort_wrapper(void* param)
{
    Task *task= (Task*)param;
    quicksort(task->values, task->p, task->r);
}

/**
 * Sort the element in the given interval.
 */
void quicksort(int* values, int p, int r)
{
  int q;
  pthread_t thread;
  Task task;

  if (p < r) {
    q = partition(values, p, r, values[p]);
    if(CURRENT_THREAD_NUMBER < THREAD_LIMIT)
    {
        pthread_mutex_lock(&thread_number_mutex);
        CURRENT_THREAD_NUMBER++;
        pthread_mutex_unlock(&thread_number_mutex);

        task.values = values;
        task.p = p;
        task.r = q;
        pthread_create(&thread, NULL,quicksort_wrapper, (void*)&task);
        quicksort(values, q + 1, r);
        pthread_join(thread, NULL);
        CURRENT_THREAD_NUMBER--;

    }else{
        quicksort(values, p, q);
        quicksort(values, q + 1, r);
    }
  }
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
    int* data;
    int size;
    int i,j;
    clock_t passed_time;

    THREAD_LIMIT= 4;

    srand(123);

    size = 2000000;

    data = generate_data(size);

    /*
    for (i = 0; i < size; ++i)
    {
        printf("data[%d] = %d\n", i, data[i]);
    }
    printf("Sorted:\n");
    */

    passed_time = clock();
    quicksort(data, 0, size - 1);
    passed_time = clock() - passed_time;
    double time_taken = ((double)passed_time)/CLOCKS_PER_SEC;
    
    /*
    for (i = 0; i < size; ++i)
    {
        printf("data[%d] = %d\n", i, data[i]);
    }
    */

    free(data);

    printf("The program took %f seconds to execute\n", time_taken);
    
    return 0;
}

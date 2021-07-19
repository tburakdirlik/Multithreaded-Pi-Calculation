#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

//Tunahan Burak Dirlik 20170808076
int op_count;
double range;
int NUM_THREADS;
clock_t start, end;
double cpu_time_used;
double pi_sum = 0;
double PI = 3.141592653589793238462643383279;

void *threadFunc(void *parg) {

    int thread_id = *((int*) parg);
    int end;
    int start;
    double part_sum = 0;

    start = (thread_id * (int) range);
    end = (thread_id + 1) * (int) range;

    if (thread_id + 1 == NUM_THREADS) {
        end = op_count;
    }
    
    int x;
    for (x = start; x < end; x++) {
        part_sum += 4 * (pow(-1, x) / (2 * x + 1));
    }

    pi_sum += part_sum;

    return 0;
}

int main(void) {

    printf("Give the operation count : ");
    scanf("%d", &op_count);
    printf("Give the thread count \n: ");
    scanf("%d", &NUM_THREADS);
    int thread_range=NUM_THREADS;
    int q;
for (q =1; q<=thread_range; ++q){
//------------------------------------------------------------------------	
	NUM_THREADS = q;

    range = (double) op_count / (double) NUM_THREADS;

    if (range > floor(range)) {
        range = floor(range);
    }

    
//------------------------------------------------------------------------
struct timeval begin, end;
gettimeofday(&begin, 0);

    int i;
    pthread_t tid[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++) {
        int *thread_id;
        thread_id = (int *) malloc(sizeof (int));
        *thread_id = i;
        pthread_create(&tid[i], NULL, threadFunc, (void *) thread_id);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
gettimeofday(&end, 0);
//------------------------------------------------------------------------

    
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    printf("multithreaded pi =%.10f\t real pi =%.10f\t approximation error=%.10f\t computation time:%.8f second\t  thread count :%d\t\n" , pi_sum, PI, PI - pi_sum, elapsed,q);
    pi_sum=0;
    cpu_time_used =0;
}
    return 0;

}

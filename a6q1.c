#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;
sem_t empty;
sem_t full;
void  *thread_accept_num (void* arg){
    pthread_mutex_lock(&mutex);
    int num;
    printf("Input a number: ");
    scanf( "%d",&num);
    pthread_mutex_unlock(&mutex);
    return (void*) (size_t) num;
}
int total = 0;
void *thread_sum_nums(void* arg){
    pthread_mutex_lock(&mutex);
    int num = *(int*)arg;
    if (num > 0){
        total += num;
        printf("Current Total: %d\n",total);
    }
    pthread_mutex_unlock(&mutex);
    return (void*) (size_t) total;
}

int main(int argc, char *argv[]){
    pthread_t thread_id1, thread_id2;
    void *th1_num;
    void *th2_total;
    int num = 0;
    while (num >= 0){
        pthread_create(&thread_id1, NULL, thread_accept_num, NULL );
        pthread_join(thread_id1, &th1_num);
        num = (int) (size_t) th1_num;
        pthread_create(&thread_id2, NULL, thread_sum_nums, &num );
    }
    pthread_join(thread_id2, &th2_total);
    int sum = (int) (size_t) th2_total;
    printf("The sum of the input numbers is %d\n",sum);
    return 0;
}
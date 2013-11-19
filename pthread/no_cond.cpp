
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_once_t once = PTHREAD_ONCE_INIT;
pthread_key_t key;

pthread_t exiting_thread = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void delete_p(void *p)
{
    printf("%lu delete\n", pthread_self());
    delete (int*)p;
}

void creat_key_once(void)
{
    int ret = 0;

    ret = pthread_key_create(&key, delete_p); 
    if (ret != 0)
    {
        printf("pthread_key_create: %s\n", strerror(ret)); 
        exit(ret); 
    }
}

void* f(void *)
{
    int ret = 0;

    ret = pthread_once(&once, creat_key_once);
    if (ret != 0)
    {
        printf("pthread_once: %s\n", strerror(ret)); 
        exit(ret); 
    }

    for (int i = 0; i < 10; ++i)
    {
        int *p = (int *)pthread_getspecific(key);
        if (NULL == p)
        {
            p = new int(0);
            ret = pthread_setspecific(key, p);
            if (ret != 0)
            {
                printf("pthread_setspecific: %s\n", strerror(ret)); 
                exit(ret); 
            }
        }

        printf("%lu: %d\n", pthread_self(), (*p)++);
        sleep(1);
    }

    pthread_mutex_lock(&mutex);
    exiting_thread = pthread_self();
    pthread_mutex_unlock(&mutex); 

    return NULL;
}


int main()
{
    int ret = 0;

    pthread_t thid[5];

    for (int i = 0; i < 5; ++i)
    {
        ret = pthread_create(&thid[i], NULL, f, NULL);
        if (ret != 0)
        {
            printf("pthread_create: %s\n", strerror(ret)); 
            return ret;
        }
    }
    
    int dones = 0;
    int loops = 0;
    while (dones < 5)
    {
        pthread_mutex_lock(&mutex); 
        if (exiting_thread != 0)
        {
            ret = pthread_join(exiting_thread, NULL); 
            if (ret != 0)
            {
                printf("pthread_join: %s\n", strerror(ret));
                return ret;
            }
            exiting_thread = 0;
            dones++;
        }
        pthread_mutex_unlock(&mutex); 
        loops++;
    }

    printf("loops: %d\n", loops); 

    return 0; 
}

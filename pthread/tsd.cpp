#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int count = 0;

void* f(void*)
{
    for (int i = 0; i < 10; ++i)
    {
        printf("%lu: %d\n", pthread_self(), count++);
        sleep(1);
    }
    return NULL;
}

pthread_once_t once = PTHREAD_ONCE_INIT;
pthread_key_t key;

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

void* f2(void *)
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
    return NULL;
}


int main()
{
    int ret = 0;

    pthread_t thid[5];

    for (int i = 0; i < 5; ++i)
    {
        ret = pthread_create(&thid[i], NULL, f2, NULL);
        if (ret != 0)
        {
            printf("pthread_create: %s\n", strerror(ret)); 
            return ret;
        }
    }

    
    for (int i = 0; i < 5; ++i)
    {
        ret = pthread_join(thid[i], NULL);
        if (ret != 0)
        {
            printf("pthread_join: %s\n", strerror(ret)); 
            return ret;
        }
    }

    return 0; 
}


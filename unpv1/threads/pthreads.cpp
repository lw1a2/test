#include <iostream>
#include <pthread.h>
#include <cstring>
#include <cstdlib>

using namespace std;

pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t COND = PTHREAD_COND_INITIALIZER;

enum STATUS {RUNNING, JOINABLE, EXIT
};

struct Thread_info
{
    pthread_t id;
    enum STATUS status;
};

Thread_info thread_info[5];

void* f(void* arg)
{
    int *i = (int*)arg;
    if (0 == *i)
    {
        sleep(3);
    }
    pthread_t *id = new pthread_t(pthread_self());
    pthread_mutex_lock(&MUTEX);
    cout << "thread " << *id << ": " << *i << endl;
    thread_info[*i].status = JOINABLE;
    pthread_cond_signal(&COND);
    pthread_mutex_unlock(&MUTEX);
    delete i;
    
    return id;
}

int main()
{
    const int count = 5;
    pthread_t thread_id[count];
    int thread_running = 0;
    
    int ret = 0;
    
    for (int i = 0; i < count; ++i)
    {
        //不能直接把i的地址传递给f，因为这样会使多个线程同时使用i的地址，f得到的值将不确定
        int* arg = new int(i);
        ret = pthread_create(thread_id + i, NULL, f, arg);
        if (ret != 0)
        {
            cout << "create thread " << i << "failed: "
                << strerror(ret) << endl;
            exit(ret);
        }
        thread_info[i].id = thread_id[i];
        thread_info[i].status = RUNNING;
        ++thread_running;
    }

    pthread_mutex_lock(&MUTEX);

    //此种实现，修正了上一版本的问题，可以等待任意线程退出
    while (thread_running > 0)
    {
        pthread_cond_wait(&COND, &MUTEX);

        for (int i = 0; i < count; ++i)
        {
            if (JOINABLE == thread_info[i].status)
            {
                pthread_t *id = NULL;
                ret = pthread_join(thread_id[i], (void**)&id);
                if (ret != 0)
                {
                    cout << "join thread " << *id << " failed: "
                        << strerror(ret) << endl;
                    exit(ret);
                }
                cout << "join thread " << *id << ": " << i << endl;
                thread_info[i].status = EXIT;
                --thread_running;
                delete id;
            }
        }
    }

    pthread_mutex_unlock(&MUTEX);

    return 0;
}



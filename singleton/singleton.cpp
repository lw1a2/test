#include <pthread.h>
#include <iostream>

using namespace std;

class Lock
{
public:
    Lock()
    {
        pthread_mutex_init(&mutex, NULL);
    }

    ~Lock()
    {
        pthread_mutex_destroy(&mutex);
    }

    void lock()
    {
        pthread_mutex_lock(&mutex);
    }

    void unlock()
    {
        pthread_mutex_unlock(&mutex);
    }

private:
    pthread_mutex_t mutex;
};

class Singleton
{
public:
    static Singleton* instance()
    {
        if (NULL == m_instance)
        {
            m_l.lock();
            if (NULL == m_instance)
            {
                m_instance = new Singleton;
            }
            m_l.unlock();
        }
        return m_instance;
    }
    ~Singleton()
    {
        delete m_instance;
    }
private:
    Singleton()
    {
    }
    Singleton(const Singleton&);
    Singleton& operator = (const Singleton&);
    static Singleton* m_instance;
    static Lock m_l;
};
Singleton* Singleton::m_instance = NULL;
Lock Singleton::m_l;


int main()
{
    Singleton* s = Singleton::instance();
    cout << s << endl;
    Singleton* s2 = Singleton::instance();
    cout << s2 << endl;

    return 0;
}


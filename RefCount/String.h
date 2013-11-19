#pragma once

#include <cstring>

class String
{
    struct RefCount
    {
        int m_count;
        char * m_str;
        RefCount(const char* s) : m_count(1)
        {
            if (s != NULL)
            {
                m_str = new char[strlen(s) + 1];
                strncpy(m_str, s, strlen(s) + 1);
            }
            else
            {
                m_str = NULL;
            }
        }

        ~RefCount()
        {
            delete [] m_str;
        }
    };

public:
    String() : m_refCount(new RefCount(""))
    {
    }

    String(const char* str) : m_refCount(new RefCount(str))
    {
    }

    String(const String& rhs) : m_refCount(rhs.m_refCount)
    {
        ++m_refCount->m_count;
    }

    String& operator = (const String& rhs)
    {
        if (m_refCount == rhs.m_refCount)
        {
            return *this;
        }

        --m_refCount->m_count;
        if (0 == m_refCount->m_count)
        {
            delete m_refCount;
        }
        m_refCount = rhs.m_refCount;
        ++m_refCount->m_count;

        return *this;
    }

    ~String()
    {
        --m_refCount->m_count;
        if (0 == m_refCount->m_count)
        {
            delete m_refCount;
        }
    }

    char operator[](const int x) const
    {
        return m_refCount->m_str[x];
    }

    char& operator[](const int x)
    {
        if (m_refCount->m_count > 1)
        {
            --m_refCount->m_count;
            m_refCount = new RefCount(m_refCount->m_str);
        }
        return m_refCount->m_str[x];
    }

private:
    RefCount* m_refCount;
};


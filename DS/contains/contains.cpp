#include <iostream>
#include <string>
#include <cstring>

using namespace std;

/* 
�ο���http://blog.csdn.net/beiyeqingteng/article/details/7447908 
���⣺
�������ַ�����ÿ���ַ������ַ���A-Z��ѡȡ�����磺B="ABBC"��A="ACBBD"����ôA��������B�г��ֵ��ַ��� 
���A="ACBD"����A="ABBD"����������ΪA������B�����е��ַ���
������
����"�Ƿ����"�����⣬�����ϴ���ķ���������hashtable�йء� 
����Ҳ�����⡣˼·�ǰ�����A�г��ֵ��ַ�����һ������Ϊ256���ַ�����array[256]� �ַ���asciiֵΪ������±�
���磬"ABBC"����array[256] = {..., 0, 1, 2, 1, 0, ... , 0}��
Ȼ�����ÿ����B�ַ����г��ֵ��ַ�����array[256]������Ӧ�ļ����� 
ֻҪ����array[i] < 0, ���� false��
*/

bool contains(const string& A, const string& B)
{
    int count[256];
    memset(count, 0, 256 * sizeof(int));
    for (string::size_type i = 0; i < A.size(); ++i)
    {
        ++count[A[i]];
    }

    for (string::size_type i = 0; i < B.size(); ++i)
    {
        if (--count[B[i]] < 0) return false;
    }
    return true;
}

int main()
{
    string A = "ACBBD";
    string B = "ABBC";
    cout << contains(A, B) << endl;

    A = "ACBD";
    cout << contains(A, B) << endl;

    A = "ABBD";
    cout << contains(A, B) << endl;

    return 0;
}

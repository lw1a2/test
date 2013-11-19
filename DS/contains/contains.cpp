#include <iostream>
#include <string>
#include <cstring>

using namespace std;

/* 
参考：http://blog.csdn.net/beiyeqingteng/article/details/7447908 
问题：
有两个字符串，每个字符串的字符从A-Z中选取，比如：B="ABBC"，A="ACBBD"，那么A包含所有B中出现的字符。 
如果A="ACBD"或者A="ABBD"，则我们认为A不包含B中所有的字符。
分析：
对于"是否包含"的问题，基本上处理的方法都会与hashtable有关。 
这题也不例外。思路是把所有A中出现的字符放在一个长度为256的字符数组array[256]里， 字符的ascii值为数组的下标
比如，"ABBC"就是array[256] = {..., 0, 1, 2, 1, 0, ... , 0}。
然后对于每个在B字符串中出现的字符，在array[256]里做相应的减法。 
只要遇到array[i] < 0, 返回 false。
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

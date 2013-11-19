#include <iostream>
#include <cstring>

using namespace std;

char* Strcpy(char *dst,const char *src) 
{
	if (dst == NULL || src == NULL || dst == src) return NULL;
	
	int size = 0;
	char* p = (char*)src;
	while (*p++) size++;
	
	if (dst <= src || dst >= src + size)
	{
		while (*dst++ = *src++);
	}  
	else
	{   
		p = dst + size - 1;  
		src += size - 1;   
		while(size--) *p-- = *src--;
	}  
	
	return dst;
}

int main()
{
	char str[10]="abc";
	Strcpy(str+1,str);  
	cout << str << endl;  
	
	char str2[10];
	memset(str2, 0, 10);
	Strcpy(str2, "str");  
	cout << str2 << endl;  
	return 0;
}


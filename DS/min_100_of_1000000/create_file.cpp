#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    ofstream f("input.txt");
    srand(time(NULL));
    
    for (int i = 0; i < 1000000; ++i)
    {
        f << rand() << '\n';
    }

    return 0;
}


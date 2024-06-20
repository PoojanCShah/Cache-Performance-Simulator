#include "cache.h"
#include <fstream>
// write a function to check if an integer is a poer of 2 or not
bool isPowerOfTwo(ll n)
{
    return (n && !(n & (n - 1)));
}

int main(int argc, char *argv[])
{

    if (argc != 7)
    {
        cout << "Usage: ./cacheSim <numSets> <numBlocks> <blockSize> <write-allocate/no-write-allocate> <write-through/write-back> <lru/fifo>" << endl;
        return 0;
    }

    string lf = argv[6];
    string wt = argv[5];
    string wa = argv[4];

    ll numSets = stoi(argv[1]);
    ll numBlocks = stoi(argv[2]);
    ll blockSize = stoi(argv[3]);
    if (lf != "lru" && lf != "fifo")
    {
        cout << "Invalid Replacement Policy" << endl;
        cout << "Usage: ./cacheSim <numSets> <numBlocks> <blockSize> <write-allocate/no-write-allocate> <write-through/write-back> <lru/fifo>" << endl;
        return 0;
    }
    if (wt != "write-through" && wt != "write-back")
    {
        cout << "Invalid Write Policy" << endl;
        cout << "Usage: ./cacheSim <numSets> <numBlocks> <blockSize> <write-allocate/no-write-allocate> <write-through/write-back> <lru/fifo>" << endl;
        return 0;
    }
    if (wa != "write-allocate" && wa != "no-write-allocate")
    {
        cout << "Invalid Write Allocate Policy" << endl;
        cout << "Usage: ./cacheSim <numSets> <numBlocks> <blockSize> <write-allocate/no-write-allocate> <write-through/write-back> <lru/fifo>" << endl;
        return 0;
    }

    if (numSets == 0 || numBlocks == 0 || blockSize < 4 || !isPowerOfTwo(numSets) || !isPowerOfTwo(numBlocks) || !isPowerOfTwo(blockSize))
    {
        cout << "Invalid Cache Configuration" << endl;
        cout << "Usage: ./cacheSim <numSets> <numBlocks> <blockSize> <write-allocate/no-write-allocate> <write-through/write-back> <lru/fifo>" << endl;
        return 0;
    }



    bool lru_fifo = (lf == "lru") ? 1 : 0;
    bool writeThrough = (wt == "write-through") ? 1 : 0;
    bool writeAllocate = (wa == "write-allocate") ? 1 : 0;
    Cache c(numSets, numBlocks, blockSize, lru_fifo, writeThrough, writeAllocate);

    char ch;
    long long unsigned int hex;
    int num;
    while (scanf(" %c %llx %d \n", &ch, &hex, &num) == 3)
    {
        if (ch == 'l')
        {
            c.read(hex);
        }
        else if (ch == 's')
        {
            c.write(hex);
        }
        else
        {
            break;
        }
    }
    c.print();
    return 0;
}

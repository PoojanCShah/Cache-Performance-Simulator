#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
typedef long long ll;
using namespace std;

#define CACHE 1
#define MEM 100

class Block
{
    public : 
    ll tag;
    bool dirty;
    Block();
    Block(ll t);
    bool operator==(Block b);
};

class Address
{
    public:
    ll tag;
    ll index;
    ll offset;
    Address(ll t, ll i, ll o);
};

class Cache
{
    public:
    vector<vector<Block>> sets;
    ll num_sets;
    ll num_blocks;
    ll block_size;
    bool lru;
    bool write_through;
    bool write_allocate;

    ll load_hits;
    ll load_misses;
    ll store_hits;
    ll store_misses;

    ll cycles;

    ll HIT;
    ll MISS;

    Cache(ll num_sets, ll num_blocks, ll block_size, bool lru, bool write_through, bool write_allocate);

    void read(ll address);
    void write(ll address);

    Address decode(ll address);

    void print();

    void evict(ll idx);

};
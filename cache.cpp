#include "cache.h"

Block::Block()
{
    tag = -1;
    dirty = false;
}

Block::Block(ll t)
{
    tag = t;
    dirty = false;
}

bool Block::operator==(Block b)
{
    return tag == b.tag;
}

Address::Address(ll t, ll i, ll o)
{
    tag = t;
    index = i;
    offset = o;
}

Cache::Cache(ll num_sets, ll num_blocks, ll block_size, bool lru, bool write_through, bool write_allocate)
{
    this->num_sets = num_sets;
    this->num_blocks = num_blocks;
    this->block_size = block_size;
    this->lru = lru;
    this->write_through = write_through;
    this->write_allocate = write_allocate;

    load_hits = 0;
    load_misses = 0;
    store_hits = 0;
    store_misses = 0;

    cycles = 0;

    sets.resize(num_sets);

    // HIT = CACHE;
    // MISS = CACHE + MEM * block_size / 4;
}

Address Cache::decode(ll address)
{
    ll blockOffset = address & (block_size - 1);
    address = address / block_size;
    ll setIndex = address & (num_sets - 1);
    address = address /(num_sets);
    ll tag = address;
    return Address(tag, setIndex, blockOffset);
}

void Cache ::evict(ll idx)
{
   
    Block evict_blk = sets[idx][0];
    if (!write_through && evict_blk.dirty)
    {
         cycles += 25 * block_size ;
    }
    sets[idx].erase(sets[idx].begin());
}

void Cache::read(ll address)
{
    Address addr = decode(address);
    ll idx = addr.index;
    ll tag = addr.tag;
    auto it = find(sets[idx].begin(), sets[idx].end(), Block(tag));

    if (it != sets[idx].end())
    {
        if (lru)
        {
            Block b = *it;
            sets[idx].erase(it);
            sets[idx].push_back(b);
        }

        load_hits++;
         cycles += 1;
    }

    else
    {
        load_misses++;
        cycles += 25*block_size + 1;
        if ((ll)(sets[idx].size()) == num_blocks)
        {
            evict(idx);
        }
        sets[idx].push_back(Block(tag));
    }
}

void Cache ::write(ll address)
{
    Address addr = decode(address);
    ll idx = addr.index;
    ll tag = addr.tag;
    auto it = find(sets[idx].begin(), sets[idx].end(), Block(tag));

    if (it != sets[idx].end())
    {
    
         (*it).dirty = true;

        if (lru)
        {
            Block b = *it;
            sets[idx].erase(it);
            sets[idx].push_back(b);
        }

        store_hits++;
       
        if(write_through)
        {
            cycles += 101;
        }
        else
        {
            cycles += 1;
        }
    }

    else
    {
        store_misses++;
        if(write_allocate)
        {
            if((ll) (sets[idx].size()) == num_blocks)
            {
                evict(idx);
            }
            Block b = Block(tag);
            b.dirty = true;
            sets[idx].push_back(b);
            if(write_through)
            {
                cycles += 25*block_size + 1 + 100;
            }
            else
            {
                cycles += 25*block_size + 1;
            }
            
        }
        else
        {
             cycles += 100;
        }
    }
}


void Cache::print()
{
    cout << "Total loads: " << load_hits + load_misses << endl;
    cout << "Total stores: " << store_hits + store_misses << endl;
    cout << "Load hits: " << load_hits << endl;
    cout << "Load misses: " << load_misses << endl;
    cout << "Store hits: " << store_hits << endl;
    cout << "Store misses: " << store_misses << endl;
    cout << "Total cycles: " << cycles << endl;
}
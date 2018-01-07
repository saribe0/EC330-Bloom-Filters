#ifndef MYBLOOMFILTER_H
#define MYBLOOMFILTER_H

#include "BloomFilter.h"

using namespace std;

class myBloomFilter : public BloomFilter
{
public:
        //Creates an empty Bloom filter of length chars
        myBloomFilter(int length);

        //Creates a Bloom filter from a given string
        myBloomFilter(string filter);

        //Inserts an item into the filter
        void insert(string item);

        //Checks to see whether or not an item is in the filter
        // @returns true if it is likely in the filter
        // @returns false if it is not in the filter
        bool exists(string item);

        //Gives the filter as a string
        // @returns a string representing the filter
        string output();

        //Hashes the string into a location and value in the filter
        int* hashFunc(string item);

private:
        char* bloom;
};

#endif /* MYBLOOMFILTER_H */

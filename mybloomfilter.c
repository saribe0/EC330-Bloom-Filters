#include "myBloomFilter.h"

using namespace std;

//Creates bloom filter of certain length
myBloomFilter::myBloomFilter(int length) : BloomFilter(length)
{
        bloom = new char[length]();
}

//Creates bloom filter as array of characters based off a strings
myBloomFilter::myBloomFilter(string filter) : BloomFilter(filter)
{
        bloom = new char[filter.size()+1];
        strcpy(bloom, filter.c_str());
}

//Inserts a string into the bloom filter
void myBloomFilter::insert(string item)
{
        //Hashes the strings
        int* hash = hashFunc(item);
        int loc = hash[0];
        char val = hash[1];

        int locOriginal = loc;

        //If the loc is NULL, put it there
        if (bloom[loc] == '\0')
        bloom[loc] = val;

        //If not look for the next open cell or one with
        //	the same value.
        else
        {
                //Go through location and look for a spot to put the value
                do
                {
                        loc++;
                        if (bloom[loc] == val)
                        break;
                        if (loc == BloomFilter::length)
                        loc = 0;
                        if (loc == locOriginal)
                        break;
                } while (bloom[loc] != '\0');
        }
}

//Check to see if a string is probably in the filter
bool myBloomFilter::exists(string item)
{
        //Hashes the string
        int* hash = hashFunc(item);
        int loc = hash[0];
        char val = hash[1];

        int locOriginal = loc;

        //Look for where the hash would be stored, if it reaches
        //	the original location or null, it is not there
        do
        {
                if (loc == BloomFilter::length - 1)
                loc = 0;
                if (bloom[loc] == val)
                return true;
                loc++;
                if (loc == locOriginal)
                return false;
        } while (bloom[loc] != '\0');
}

//Displays the values contained in the filter as a string
string myBloomFilter::output()
{
        return string(bloom, BloomFilter::length);
}

//Hashes the string into a location and a value to be turned into
//	a character
int* myBloomFilter::hashFunc(string item)
{
        int* hash = new int[2];
        unsigned int loc = 0;
        unsigned int val = 0;

        //Actual Hash Function
        for (int ii = 0; ii < item.length()-1; ii++)
        {
                loc = (loc * 37 + item[ii]*loc) % 57;
                val = val + item[ii]*11*loc%87;
        }

        hash[0] = loc%BloomFilter::length;
        hash[1] = (val % 31) + 33;

        return hash;
}
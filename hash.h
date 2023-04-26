#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctype.h>
#include <vector>

#include <ctime>
#include <cstdlib>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        int a_index = (6 - (k.length() % 6)) % 6;
        long long curr_sum = 0;

        std::vector<long long> w;

        for (size_t i = 0; i < k.length(); i++) {
            int curr_char = letterDigitToNumber(k[i]);
            curr_sum = 36 * curr_sum + curr_char;
            a_index++;

            if (a_index > 5) {
                w.push_back(curr_sum);
                // w[w_index] = curr_sum;
                // w_index++;

                curr_sum = 0;   
                a_index = 0;
            }
        }

        while (w.size() < 5) {
            w.insert(w.begin(), 0);
        }

        long long final = 0;
        for (int i = 0; i < 5; i++) {
            final += w[i] * rValues[i];
        }

        return final;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if (toascii(letter) >= 97 && toascii(letter) <= 122) {
            return toascii(letter)-97;
        } else if (toascii(letter) >= 65 && toascii(letter) <= 90) {
            return toascii(letter)-65;
        } else {
            return toascii(letter)-22;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

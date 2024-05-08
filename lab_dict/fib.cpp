/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/** 
 * Calculates the nth Fibonacci number where the zeroth is defined to be 
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
    unsigned long result = 0;
    unsigned long previous = 0;
    unsigned long current = 1;
    for(unsigned long i = 0; i < n; i++) {
        result = previous + current;
        previous = current;
        current = result;
    }
    return result;
}

/** 
 * Calculates the nth Fibonacci number where the zeroth is defined to be 
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */
    unsigned long result = 0;
    static map<unsigned long, unsigned long> memo = {{0, 0}, {1, 1}};
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    else {
        result = memoized_fib(n - 1) + memoized_fib(n - 2);
        memo[n] = result;
        return result;
    }
    
}

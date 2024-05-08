/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    vector< StringTriple > result;
    if (wordsFile.is_open()) {
        string word;
        while (getline(wordsFile, word)) {
            if (word.length() >= 3) {
                string word1 = word.substr(1);
                string word2 = word[0] + word.substr(2);
                if (d.homophones(word, word1) && d.homophones(word, word2)) {
                    result.push_back(make_tuple(word, word1, word2));
                }
            }
        }
    }
    return result;
    // return vector< StringTriple >();
}



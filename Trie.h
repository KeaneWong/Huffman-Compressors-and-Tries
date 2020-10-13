#pragma once
#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <vector>
#include <fstream>
const int ALPHABET_SIZE = 26;
using namespace std;
struct TrieNode
{
    TrieNode* children[ALPHABET_SIZE] = { nullptr };
    int isTerminal=0;
    char value;


};
class Trie {
public:
    Trie(string fileName);
    void insert(string s);
   // bool deletion(string s);
    int search(string s);
    int numWords();
private:
    TrieNode* root;
    int numWordsRecursive(TrieNode* root);
    TrieNode* newNode();
    int index1(char a)
    {
        return a - 'a';//shifting the alphabet over since we're only daeling with lowercase a-z
    }

};
#endif
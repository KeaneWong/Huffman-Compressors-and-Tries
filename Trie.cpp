#include "Trie.h"
#include <vector>
#include <string>
Trie::Trie(string fileName) {
    fstream file;
    string word;
    file.open(fileName);
    root = newNode();
    while (file >> word)
    {
        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] >= 'A' && word[i] <= 'Z')//if its capital case then lower case it
            {
                word[i] = tolower(word[i]);
            }
            else if (word[i] < 'a' || word[i]>'z')//if it made it here then its not a capital letter and is therefore either lowercase or an external symbol
            {
                word.erase(i, 1);//we erase the external symbol
                i--;//now that we errased a character we need to shift back to adjust for it
                //i--;
            }
        }
        insert(word);
    }
    file.close();


}

int Trie::search(string s)
{
    TrieNode* curNode = root;
    for (int i = 0; i < s.length(); i++)
    {
        int index = index1(s[i]);
        if (curNode->children[index] == nullptr)//if theres nothing at the index that means that part of the word is cutoff and the word was not inputted in
        {
            return 0;
        }
        curNode = curNode->children[index];
    }
    return curNode->isTerminal;
};

void Trie::insert(string s)
{
    TrieNode* curNode = root;
    for (int r = 0; r < s.length(); r++)//stop right before final string part?
    {
        int ind = index1(s[r]);

        if (curNode->children[ind] == nullptr)//this means its empty and we need a new branch
        {
            TrieNode* newnode = newNode();
            curNode->children[ind] = newnode;
        }
        curNode = curNode->children[ind];
    }
    curNode->isTerminal++;
}

TrieNode* Trie::newNode()
{
    TrieNode *newnode = new TrieNode();
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        newnode->children[i] = nullptr;
    }
    newnode->isTerminal = 0;
    newnode->value = '0';
    return newnode;
}

int Trie::numWords()//wrapper function
{
    return numWordsRecursive(root);
}

int Trie::numWordsRecursive(TrieNode* root)
{
    int numberWords = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i]!=nullptr&&root->children[i]->isTerminal>0)
        {
            numberWords++;//every node noted as a terminal node is a unique word
        }
        if (root->children[i] != nullptr)//note that we dont stop even if we find a terminal node because a terminal node may not be external. This is to account for words that are substrings of other words
        {
            numberWords += numWordsRecursive(root->children[i]);
        }
    }
    return numberWords;

};

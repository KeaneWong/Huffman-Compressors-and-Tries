#include <iostream>
#include <string>
#include "Trie.h"
#include "HuffmanCompressor.h"
using namespace std;
int main()
{
    cout << "Enter the name of the file you wish to input" << endl;
    string txt;
    cin >> txt;
    Trie myTrie(txt);
    cout << "Number of words: " << myTrie.numWords() << endl;
    cout << "Search for words? (Enter 0 to end)" << endl;
    while (cin >> txt && txt != "0")
    {
        for (int i = 0; i < txt.length(); i++)
        {
            if (txt[i] >= 'A' && txt[i] <= 'Z')
            {
                txt[i] = tolower(txt[i]);
            }
        }
        if (myTrie.search(txt))
        {
            cout << "Word found" << endl;
        }
        else
        {
            cout << "Word not found" << endl;
        }
        cout << "Search for words? (Enter 0 to end)" << endl;
    }
    cout << "Enter the name of the file you wish to input" << endl;
    cin >> txt;
    HuffmanCompressor myCompressor(txt);
    cout << "Enter the name of the output file you wish to output to" << endl;
    cin >> txt;
    myCompressor.printTable(txt);
    //C:\Users\keane\Downloads\usdeclarPC.txt
    //C:\Users\keane\Downloads\moneyIn.txt
    //C:\Users\keane\Downloads\moneyOut.txt
}

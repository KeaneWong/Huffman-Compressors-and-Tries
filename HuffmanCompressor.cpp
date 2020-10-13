#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include "HuffmanCompressor.h"
const int ALPHABET_SIZE = 128;







Node* HuffmanCompressor::newNode(char cha, int frequ, Node* left1, Node* right1)
{
    Node *newnode = new Node();
    newnode->ch = cha;
    newnode->left = left1;
    newnode->right = right1;
    newnode->frequency = frequ;
    return newnode;

}

void HuffmanCompressor::encode(Node* root, string str,//recursive encoding algorithm. Assumes you have some form of tree setup as an input
    string* huffmanCodeTabl)
{
    if (root == nullptr)
        return;


    if (root->left == nullptr && root->right == nullptr) //if it is invalid then they're external
    {
        huffmanCodeTabl[root->ch ] = str;
    }

    encode(root->left, str + "0", huffmanCodeTabl);
    encode(root->right, str + "1", huffmanCodeTabl);
}

class HuffmanCompressor::C//comparison object solely for the pq argument
{
public:
    bool operator()(Node* l, Node* r)
    {
        return l->frequency > r->frequency;
    }
};
HuffmanCompressor::HuffmanCompressor(string fileName)
{
    fstream file1;
    file1.open(fileName);
    if (file1.is_open())
    {
        cout << "FILE OPENED SUCCESSFULLY" << endl;
    }
    
    int* alphabet = new int[ALPHABET_SIZE+1];
    for (int e = 0; e < ALPHABET_SIZE + 1; e++)
    {
        alphabet[e] = 0;
    }
    char ch;
    numCharacters = 0;
    origText = "";
    while (file1>>noskipws>>ch)//reusing code from Trie to gather data 
    {
        numCharacters++;
        origText += ch;

        alphabet[ch]++;//add the lowercase symbol character to our frequency array
        //erased a lot of code after realizing we dont need to filter out non lower case letters
  
        
        
    }
    priority_queue<Node*, vector<Node*>, C> myQueue;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
       // cout << "Alphabet size " <<alphabet[i]<< endl;
        if (alphabet[i] > 0)//skip anythign that has a frequency of 0
        {
            myQueue.push(newNode((char)i, alphabet[i], nullptr, nullptr));//creating a least priority quueeu so that we can construct our heap from bottom up (min heap)
        }
    }
    while (myQueue.size() != 1)//go through until we only have the root. 
    {
        Node *lef = myQueue.top();//by using a pq we can ensure we only add the nodes with the smallest total frequency.
        myQueue.pop();
        Node *rig = myQueue.top();
        myQueue.pop();
        int newFreq = lef->frequency + rig->frequency;
        myQueue.push(newNode('\0', newFreq, lef, rig));//guarantees that we're only adding the smallest nodes, not necessarily the smallest external nodes
    }
    Node* root = myQueue.top();
    huffmanCodeTable = new string[ALPHABET_SIZE ];
    encode(root, "", huffmanCodeTable);

    file1.close();
}

void HuffmanCompressor::printTable(string fileName)
{
    fstream myFile;
    myFile.open(fileName);
    for (int i = 0; i < ALPHABET_SIZE; i++) 
    {
        if (huffmanCodeTable[i] !="")//checks if there is an entry here
        {
            myFile << (char)i << " Code equivalent: " << huffmanCodeTable[i] << endl;//we enter the code equivalent next to each letter
        }
    }
    myFile << "********" << endl;
    myFile << "Number of characters: " << numCharacters << endl;
    string s = encodeText(origText);
    myFile << "Number of bits: " << s.length() << endl;
    myFile << s << endl;
    myFile.close();
}

string HuffmanCompressor::encodeText(string originalText)//method to turn a text into the coded version using the huffman table
{
    string returnString = "";
    for (int i = 0; i < originalText.length(); i++)
    {
        char charact = originalText[i];
        int ind;


        ind = charact;//add the lowercase symbol character to our frequency array
         returnString += huffmanCodeTable[ind];
        

    }
    return returnString;
    
}

//string HuffmanCompressor::decode(string originalText)
//{
    //return;
//}
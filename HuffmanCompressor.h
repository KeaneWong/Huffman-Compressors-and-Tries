#pragma once
#ifndef HUFFMANCOMPRESSOR_H
#define HUFFMANCOMPRESSOR_H
#include <iostream>
#include <fstream>
using namespace std;
struct Node
{
	char ch;
	int frequency;
	Node* left, * right;
};
class HuffmanCompressor
{
public:
	HuffmanCompressor(string filename);
	void printTable(string fileName);
private:

	string *huffmanCodeTable;
	class C;
	Node* newNode(char cha, int frequ, Node* left1, Node* right1);
	void encode(Node* root, string str, string* huffmanCodeTabl);
	string encodeText(string s);
	//string decode(string originalText); not enough time for extra credit
	char toChar(int i);
	string origText;
	int numCharacters;
	int numBits;
	

};


#endif
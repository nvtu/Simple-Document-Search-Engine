#ifndef FUNCTIONS
#define FUNCTIONS
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <ctype.h>
#include <vector>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct Node{
    vector<int> Offset[180];
    Node* pNext[63];
};
struct File{
    string FileName;
    bool isInFile;
};
struct Position{
    vector<int> offset;
    vector<int> occurence;
};
struct Scoring{
    long long score;
    int DocOffset;
};
class Trie{
private:
    Node* pRoot;
    Node* pNRoot;
    void FreeTrie(Node*& pRoot);
    void InsertWordToTrie(Node* pRoot, string word, int FILE_INDEX, int OffsetNumber);
    void NormalInsertWordToTrie(Node* pRoot, string word, int FILE_INDEX, int OffsetNumber);
    void ANDSearch(Node* pCur, bool isContained[]);
    void ORSearch (Node* pCur, bool isContained[]);
public:
    void Init();

    //******************************STRING HANDLE AND QUERY EXECUTION*****************************
    void StringInputHandle(string StringInput, bool isFilter, int FILE_INDEX, int& OffsetNumber);
    void StringQueryHandle(int NUMBER_OF_QUERRIES, bool isFilter, bool StopWord, string OutputSign);
    void QueryExecution(bool isFilter, bool StopWord, string OutputSign);

    //********************SEARCHING AND UPDATE RESULT***********************************************
    void SearchWord (Node* pRoot, bool isContained[], Position Offset[], string word, string sign);
    void NormalSearchWord (Node* pRoot, bool isContained[], Position Offset[], string word, string sign);
    void SpecialSearchWord(Node* pRoot, bool specialContained[], Position Offset[], string word);
    void MatchWordSearch(Node* pRoot, bool specialContained[], Position Offset[]);
    void UpdateResult(File Doc[], bool isContained[]);

    //*****************LOADING DATA*********************************
    void LoadQuery();
    void LoadStopWordList();
    void LoadDoc(bool isFilter);

    //***************RANKING DOC AND OUTPUT*******************************
    void RankingDoc(vector<int> MainOffset[], Position SubOffset[], Scoring DocRate[]);
    void Snapshot(vector<int> Offset[], int DocOffset);
    void ConsoleOutput(int i, clock_t ProcessTime, vector<int> MainOffset[], Scoring DocRate[]);
    void SaveFile(clock_t ProcessTime, Scoring DocRate[]);
    void SaveFile(clock_t ProcessTime);

    //**********STOP WORD LIST SEARCH*******************
    bool StopWordFilter(string word);
    bool BinarySearch(int l, int r, string word);

    void Free();
};
int Sorting(Scoring a, Scoring b);
#endif // FUNCTIONS


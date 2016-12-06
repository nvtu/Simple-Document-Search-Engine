#include "TRIE.h"
int NUMBER_OF_FILES, NUMBER_OF_QUERIES;
string* Query;
File Doc[180];
ofstream fout;
vector<string> StopList;
char* path="Group3_result.txt";
//************************************CONSTRUCTOR****************************
void Trie::Init(){ //Initialize the Root of the Trie data structure whose Root is an empty Node
    pRoot=new Node;
    for (int i=0; i<63; i++)
        pRoot->pNext[i]=NULL;
    pNRoot=new Node;
    for (int i=0; i<63; i++)
        pNRoot->pNext[i]=NULL;
}
//**************************************************************************

//************************************LOAD FILE FUNCTIONS*************************************************
void Trie::LoadQuery(){ //Load the query needed to find from file query.txt
    ifstream fin;
    fin.open("Query.txt");
    if (!fin.is_open())
        return;
    fin>>NUMBER_OF_QUERIES;
    Query=new string[NUMBER_OF_QUERIES];
    fin.get();
    for (int i=0; i<NUMBER_OF_QUERIES; i++){
        getline(fin,Query[i]); //Load query and store them in the array Query
    }
    fin.close();
}

void Trie::LoadDoc(bool isFilter){ //Load the data files into the Trie structure
    ifstream fin;
    string StringInput;
    const char* path[]={"Data001.txt", "Data002.txt", "Data003.txt", "Data004.txt", "Data005.txt", "Data006.txt", "Data007.txt", "Data008.txt", "Data009.txt", "Data010.txt", "Data011.txt", "Data012.txt", "Data013.txt", "Data014.txt", "Data015.txt", "Data016.txt", "Data017.txt", "Data018.txt", "Data019.txt", "Data020.txt", "Data021.txt", "Data022.txt", "Data023.txt", "Data024.txt", "Data025.txt", "Data026.txt", "Data027.txt", "Data028.txt", "Data029.txt", "Data030.txt", "Data031.txt", "Data032.txt", "Data033.txt", "Data034.txt", "Data035.txt", "Data036.txt", "Data037.txt", "Data038.txt", "Data039.txt", "Data040.txt", "Data041.txt", "Data042.txt", "Data043.txt", "Data044.txt", "Data045.txt", "Data046.txt", "Data047.txt", "Data048.txt", "Data049.txt", "Data050.txt", "Data051.txt", "Data052.txt", "Data053.txt", "Data054.txt", "Data055.txt", "Data056.txt", "Data057.txt", "Data058.txt", "Data059.txt", "Data060.txt", "Data061.txt", "Data062.txt", "Data063.txt", "Data064.txt", "Data065.txt", "Data066.txt", "Data067.txt", "Data068.txt", "Data069.txt", "Data070.txt", "Data071.txt", "Data072.txt", "Data073.txt", "Data074.txt", "Data075.txt", "Data076.txt", "Data077.txt", "Data078.txt", "Data079.txt", "Data080.txt", "Data081.txt", "Data082.txt", "Data083.txt", "Data084.txt", "Data085.txt", "Data086.txt", "Data087.txt", "Data088.txt", "Data089.txt", "Data090.txt", "Data091.txt", "Data092.txt", "Data093.txt", "Data094.txt", "Data095.txt", "Data096.txt", "Data097.txt", "Data098.txt", "Data099.txt", "Data100.txt", "Data101.txt", "Data102.txt", "Data103.txt", "Data104.txt", "Data105.txt", "Data106.txt", "Data107.txt", "Data108.txt", "Data109.txt", "Data110.txt", "Data111.txt", "Data112.txt", "Data113.txt", "Data114.txt", "Data115.txt", "Data116.txt", "Data117.txt", "Data118.txt", "Data119.txt", "Data120.txt", "Data121.txt", "Data122.txt", "Data123.txt", "Data124.txt", "Data125.txt", "Data126.txt", "Data127.txt", "Data128.txt", "Data129.txt", "Data130.txt", "Data131.txt", "Data132.txt", "Data133.txt", "Data134.txt", "Data135.txt", "Data136.txt", "Data137.txt", "Data138.txt", "Data139.txt", "Data140.txt", "Data141.txt", "Data142.txt", "Data143.txt", "Data144.txt", "Data145.txt", "Data146.txt", "Data147.txt", "Data148.txt", "Data149.txt", "Data150.txt", "Data151.txt", "Data152.txt", "Data153.txt", "Data154.txt", "Data155.txt", "Data156.txt", "Data157.txt", "Data158.txt", "Data159.txt", "Data160.txt", "Data161.txt", "Data162.txt", "Data163.txt", "Data164.txt", "Data165.txt", "Data166.txt", "Data167.txt", "Data168.txt", "Data169.txt", "Data170.txt", "Data171.txt", "Data172.txt", "Data173.txt", "Data174.txt", "Data175.txt", "Data176.txt", "Data177.txt", "Data178.txt", "Data179.txt", "Data180.txt"};
    for (NUMBER_OF_FILES=0; NUMBER_OF_FILES<180; NUMBER_OF_FILES++){ //Using distribution algorithm to manage each doc
        int OffsetNumber=0;                                          //For example: Data001.txt will be at Doc[0]
        fin.open(path[NUMBER_OF_FILES]);                             //In general: Data_i.txt will be at Doc[i-1]
        if (!fin.is_open())
            break;
        Doc[NUMBER_OF_FILES].FileName=path[NUMBER_OF_FILES]; //Set the name of the doc
        Doc[NUMBER_OF_FILES].isInFile=false; //Initialize all the doc haven't been checked
        while (!fin.eof()){
            getline(fin,StringInput);
            //Load file and handle the raw string input before add it to Trie structure
            StringInputHandle(StringInput, isFilter, NUMBER_OF_FILES, OffsetNumber);
        }
        fin.close();
    }
}

void Trie::LoadStopWordList(){ //Read stop word list from file into a vector type string
    ifstream fin;               //Then use binary search to check if a word is a stop word
    fin.open("StopWordList.txt");
    if (!fin.is_open()){
        return;
    }
    string word;
    while(!fin.eof()){
        getline(fin, word);
        StopList.push_back(word);
    }
    fin.close();
}
//********************************************************************************************************

//**************************************STRING HANDLE*****************************************************
void Trie::StringInputHandle(string StringInput, bool isFilter, int FILE_INDEX, int& OffsetNumber){ //Handle raw input string
    for (int i=0; i<StringInput.size(); i++){ // Read a paragraph, then split the paragraph into words
        string word;
        while ((StringInput[i]>='a' && StringInput[i]<='z') || (StringInput[i]>='A' && StringInput[i]<='Z') || (StringInput[i]>='0' && StringInput[i]<='9')){
            word+=StringInput[i++];
        } // If it contains the character a->z, or A->Z or 0->9, it is completely consider as a word
        if (word.size()){ //If it is completely a word, insert it to trie structure
            if (isFilter){ //Distinguish upper, lower case letters
                InsertWordToTrie(pRoot, word, FILE_INDEX, OffsetNumber);
            }
            else{ //Do not distinguish upper, lower case letters
                NormalInsertWordToTrie(pNRoot, word, FILE_INDEX, OffsetNumber);
            }
            OffsetNumber++; //The position of the word in the paragraph
        }
    }
}

void Trie::QueryExecution(bool isFilter, bool StopWord, string OutputSign){ //Function to run the search Engine
    fout.open(path);
    if (!fout.is_open())
        return;
    //*************Load Doc, query and counting the pre-processing time********
    clock_t ProcessTime=clock();
    if (StopWord){
        LoadStopWordList();
    }
    LoadQuery();
    LoadDoc(isFilter);
    SaveFile(ProcessTime);
    //*************************************************************************
    StringQueryHandle(NUMBER_OF_QUERIES, isFilter, StopWord, OutputSign);
    fout.close();
}

void Trie::StringQueryHandle(int NUMBER_OF_QUERIES, bool isFilter, bool StopWord, string OutputSign){ //Handle raw query strings
    for (int i=0; i<NUMBER_OF_QUERIES; i++){
        bool isContained[180];
        fill (isContained, isContained+180, false);
        clock_t ProcessTime=clock();
        string sign="OR";
        Scoring DocRate[180]; //An array to store the score of the doc after a query done - used for priority snapshot
        for (int j=0; j<180; j++){ //Initialize
            DocRate[j].DocOffset=j;
            DocRate[j].score=0;
        }
        vector<int> MainOffset[180]; //The vector array to store the specific offset for snapshot, the main one in all the sub-offset
        Position SubOffset[180];
        for (int j=0; j<Query[i].size(); j++){ //For each splitting word, search it based on OR search or AND search
            string word;
            while ((Query[i][j]>='a' && Query[i][j]<='z') || (Query[i][j]>='A' && Query[i][j]<='Z') || (Query[i][j]>='0' && Query[i][j]<='9')){
                word+=Query[i][j++];
            } //Split a query into word
            if (StopWord){ //If the filter stop word list is turned on, check for stop word
                if (StopWordFilter(word)){
                    continue;
                }
            }
            if (word=="AND" || word=="OR"){
                sign=word;
                if (sign=="OR"){ //If we have already finished searching a phrase (a block pf word)
                    UpdateResult(Doc, isContained); //Update the result for output
                    RankingDoc(MainOffset, SubOffset, DocRate); //Rank the doc again
                    fill(isContained, isContained+180, false); //Initialize the check list again
                }
            }
            else if (word.size()>0){
                if (Query[i][j]=='*'){ //If it is the special case for matching word
                    bool specialContained[180];
                    fill (specialContained, specialContained+180, false);
                    SpecialSearchWord(pRoot, specialContained, SubOffset, word);
                    if (sign=="OR"){ //OR search
                        for (int k=0; k<180; k++){
                            isContained[k]=specialContained[k];
                        }
                    }
                    else{ //AND search
                        for (int k=0; k<180; k++){
                            if (isContained[k] && !specialContained[k]){
                                isContained[k]=false;
                            }
                        }
                    }
                    continue;
                }
                else if (isFilter){ //Distinguish upper, lower case letters
                    SearchWord(pRoot,isContained, SubOffset, word, sign);
                }
                else{ //Do not distinguish upper, lower case letters
                    NormalSearchWord(pNRoot, isContained, SubOffset, word, sign);
                }
            }
        }
        //Finally, update the result for this query, rank doc, and output snapshot to the console
        UpdateResult(Doc, isContained);
        RankingDoc(MainOffset, SubOffset, DocRate);
        sort(DocRate, DocRate+180, Sorting);
        if (OutputSign=="F"){
            SaveFile(ProcessTime);
        }
        else{
            SaveFile(ProcessTime, DocRate);
            ConsoleOutput(i, ProcessTime, MainOffset, DocRate);
            cout<<endl<<endl;
        }
        for (int k=0; k<180; k++){ //Reset the checking is in doc to false
            Doc[k].isInFile=false;
        }
    }
}
//********************************************************************************************************

//**************************************INSERT TO TRIE****************************************************
void Trie::InsertWordToTrie(Node* pRoot, string word, int FILE_INDEX, int OffsetNumber){//Distinguish upper, lower case letters
    for (int i=0; i<word.size(); i++){ //Traverse through each character of the word in the trie structure
                                        //Create a new Node if it is an empty Node in the path traversing
        int idx; //Count the index of the next Node;
        if (word[i]>='0' && word[i]<='9'){
            idx=(int) word[i]-'0';
        }
        else if (word[i]>='a' && word[i]<='z'){
            idx=(int) word[i]-'a'+10;
        }
        else{
            idx=(int) word[i]-'A'+36;
        }

        if (!pRoot->pNext[idx]){
            pRoot->pNext[idx]=new Node;
            for (int j=0; j<63; j++){
                pRoot->pNext[idx]->pNext[j]=NULL;
            }
        }
        pRoot=pRoot->pNext[idx];
    }
    if (word.size()){ //At the end of the word - at the Node contains the final character of the word
                    //insert the information of that word and the doc offset it belongs to
        pRoot->Offset[FILE_INDEX].push_back(OffsetNumber);
    }
}

void Trie::NormalInsertWordToTrie(Node* pRoot, string word, int FILE_INDEX, int OffsetNumber){ //Do not distinguish upper, lower case letters
    for (int i=0; i<word.size(); i++){ //Traverse through each character of the word in the trie structure
                                        //Create a new Node if it is an empty Node in the path traversing
        int idx; //Count the index of the next Node;
        if (word[i]>='0' && word[i]<='9'){
            idx=word[i]-'0';
        }
        else{
            idx=tolower(word[i])-'a'+10;
        }
        if (!pRoot->pNext[idx]){
            pRoot->pNext[idx]=new Node;
            for (int j=0; j<63; j++){
                pRoot->pNext[idx]->pNext[j]=NULL;
            }
        }
        pRoot=pRoot->pNext[idx];
    }
    if (word.size()){ //At the end of the word - at the Node contains the final character of the word
                        //insert the information of that word and the doc offset it belongs to
        pRoot->Offset[FILE_INDEX].push_back(OffsetNumber);
    }
}
//********************************************************************************************************

//**************************************SEARCH WORD*******************************************************
void Trie::SearchWord (Node* pRoot, bool isContained[], Position Offset[], string word, string sign){ //Search in distinguishing upper, lower case letters mode
    Node* pCur=pRoot;
    for (int i=0; i<word.size(); i++){ //Traverse to the Node containing the last character of the word
        int idx; //Count the index of the next Node;
        if (word[i]>='0' && word[i]<='9'){
            idx=word[i]-'0';
        }
        else if (word[i]>='a' && word[i]<='z'){
            idx=word[i]-'a'+10;
        }
        else{
            idx=word[i]-'A'+36;
        }
        if (!pCur->pNext[idx]){ //If the word is not in the doc file
            fill(isContained, isContained+180, false);
            return;
        }
        pCur=pCur->pNext[idx];
    }
    for (int i=0; i<NUMBER_OF_FILES; i++){
        if (pCur->Offset[i].size()){
            for (int j=0; j<pCur->Offset[i].size(); j++)
                Offset[i].offset.push_back(pCur->Offset[i][j]);
            Offset[i].occurence.push_back(pCur->Offset[i].size());
        }
    }
    if (sign=="AND"){ //AND search
        ANDSearch(pCur, isContained);
    }
    else{ //OR search
        ORSearch(pCur, isContained);
    }
}

void Trie::NormalSearchWord (Node* pRoot, bool isContained[], Position Offset[], string word, string sign){//Search without distinguish upper, lower case
    Node* pCur=pRoot;
    for (int i=0; i<word.size(); i++){
        int idx; //Count the index of the next Node;
        if (word[i]>='0' && word[i]<='9'){
            idx=word[i]-'0';
        }
        else{
            idx=tolower(word[i])-'a'+10;
        }
        if (!pCur->pNext[idx]){
            fill(isContained, isContained+180, false);
            return;
        }
        pCur=pCur->pNext[idx];
    }
    for (int i=0; i<NUMBER_OF_FILES; i++){
        if (pCur->Offset[i].size()){
            for (int j=0; j<pCur->Offset[i].size(); j++)
                Offset[i].offset.push_back(pCur->Offset[i][j]);
            Offset[i].occurence.push_back(pCur->Offset[i].size());
        }
    }
    if (sign=="AND"){
        ANDSearch(pCur, isContained);
    }
    else{
        ORSearch(pCur, isContained);
    }
}

void Trie::SpecialSearchWord(Node* pRoot, bool specialContained[], Position Offset[], string word){//Search for matching words
    Node* pCur=pRoot;
    for (int i=0; i<word.size(); i++){
        int idx; //Count the index of the next Node;
        if (word[i]>='0' && word[i]<='9'){
            idx=word[i]-'0';
        }
        else if (word[i]>='a' && word[i]<='z'){
            idx=word[i]-'a'+10;
        }
        else{
            idx=word[i]-'A'+36;
        }
        if (!pCur->pNext[idx]){
            fill(specialContained, specialContained+180, false);
            return;
        }
        pCur=pCur->pNext[idx];
    }
    MatchWordSearch(pCur, specialContained, Offset); //Call the matching word search function
}

void Trie::MatchWordSearch(Node* pRoot, bool specialContained[], Position Offset[]){ //Search for matching word
    if (!pRoot)
        return;
    for (int i=0; i<63; i++){
        MatchWordSearch(pRoot->pNext[i], specialContained, Offset);
    }
    for (int i=0; i<NUMBER_OF_FILES; i++){
        if (pRoot->Offset[i].size()){
            for (int j=0; j<pRoot->Offset[i].size(); j++)
                Offset[i].offset.push_back(pRoot->Offset[i][j]);
            Offset[i].occurence.push_back(pRoot->Offset[i].size());
        }
    }
    ORSearch(pRoot, specialContained); //Using OR search only
}

void Trie::UpdateResult(File Doc[], bool isContained[]){ //Update the isInDoc checking for final output
    for (int i=0; i<NUMBER_OF_FILES; i++){
        if (isContained[i]){
            Doc[i].isInFile=true;
        }
    }
}

void Trie::ANDSearch(Node* pCur, bool isContained[]){ //AND search query: Uncheck the doc that has the different offset doc that the Current Node is containing
    for (int i=0; i<NUMBER_OF_FILES; i++){
        if (!pCur->Offset[i].size()){
            isContained[i]=false;
        }
    }
}

void Trie::ORSearch(Node* pCur, bool isContained[]){ //OR search query: Check all the doc that the Current Node is containing
    for (int i=0; i<NUMBER_OF_FILES; i++){
        if (pCur->Offset[i].size()){
            isContained[i]=true;
        }
    }
}

bool Trie::BinarySearch(int l, int r, string word){ //Binary Search function
    int mid=(l+r)/2;
    if (l==r){
        if (word==StopList[mid]){
            return true;
        }
        return false;
    }
    if (word>StopList[mid]){
        return BinarySearch(mid+1, r, word);
    }
    else if (word<StopList[mid]){
        return BinarySearch(l, mid-1, word);
    }
    else{
        return true;
    }
}

bool Trie::StopWordFilter(string word){ //Stop word execution
    return BinarySearch(0, StopList.size()-1, word);
}
//********************************************************************************************************

//**************************************RANKING DOC AND SNAPSHOT******************************************
void Trie::RankingDoc(vector<int> MainOffset[], Position SubOffset[], Scoring DocRate[]){ //Rank the doc for its priority
    for (int i=0; i<180; i++){
        if (Doc[i].isInFile){ //The first condition is that it must be contain in the doc
            //Calculate the score based on the total offset of each word*the number of occurrence of each word
            //Then divide that result for the total number of occurrences for each word in the doc to obtain the final score
            int cnt=0;
            for (int j=0; j<SubOffset[i].occurence.size(); j++){
                MainOffset[i].push_back(SubOffset[i].offset[cnt+SubOffset[i].occurence[j]/2]); //Get the middle offset for specific offset to snapshot
                cnt+=SubOffset[i].occurence[j];
                for (int k=0; k<SubOffset[i].occurence[j]; k++){ //for each word, score = offset*occurrence
                    DocRate[i].score+=SubOffset[i].occurence[j]*SubOffset[i].offset[k];
                }
            }
            if (cnt>0){
                DocRate[i].score/=cnt; //take the average value for scoring
            }
        }
        //Reset the sub-offset vector
        while(!SubOffset[i].offset.empty()){
            SubOffset[i].offset.pop_back();
        }
        while (!SubOffset[i].occurence.empty()){
            SubOffset[i].occurence.pop_back();
        }
    }
}

int Sorting(Scoring a, Scoring b){ //Struct sorting guide
    return (a.score>b.score);
}

void Trie::Snapshot(vector<int> Offset[], int DocOffset){ //Snapshot function - Output console
    //Read the files again and output the specific phrases based on the offset of the word
    ifstream fin;
    const char* path=Doc[DocOffset].FileName.c_str();
    cout<<"\t \t \t "<<path<<endl;
    fin.open(path);
    if (!fin.is_open())
        return;
    int cnt=-1, j=0;
    if (Offset[DocOffset].empty()){ //If the vector Main offset has no elements, exit then
        return;
    }
    if (Offset[DocOffset][j]>6){ //If the first offset is longer than 6 words, output ... for symbolizing
        cout<<"...";
    }
    string StringInput;
    sort (Offset[DocOffset].begin(), Offset[DocOffset].end()); //Output from the beginning of the file to the end of the file in order
    while (!fin.eof() && j<Offset[DocOffset].size()){ //Read file, get paragraph input, split word, and output based on the offset of the word in file
        getline(fin, StringInput);
        for (int i=0; i<StringInput.size(); i++){
            string word;
            while ((StringInput[i]>='a' && StringInput[i]<='z') || (StringInput[i]>='A' && StringInput[i]<='Z') || (StringInput[i]>='0' && StringInput[i]<='9')){
                word+=StringInput[i++];
            }
            if (word.size()){
                cnt++;
                if (cnt>=Offset[DocOffset][j]-6 && cnt<=Offset[DocOffset][j]+6){ //Take 13 words for outputting
                    cout<<word<<" ";
                    if (cnt==Offset[DocOffset][j]+6){
                        j++;
                        cout<<"...";
                        if (j==Offset[DocOffset].size()){ //If it reach the limit of the main offset, then exit
                            cout<<endl;
                            return;
                        }
                    }
                }
            }
        }
    }
    cout<<endl;
    fin.close();
}

//********************************************************************************************************

//**************************************OUTPUT RESULT*****************************************************
void Trie::ConsoleOutput(int i, clock_t ProcessTime, vector<int> MainOffset[], Scoring DocRate[]){ //Snapshot function
    char a;
    cout<<"\t"<<i+1<<") QUERY:"<<Query[i]<<endl<<endl;
    cout<<"\t   SEARCHING TIME: "<<clock()-ProcessTime<<" ms"<<endl<<endl;
    cout<<"\t   FILES CONTAIN: ";
    for (int j=0; j<180; j++){
        if (Doc[DocRate[j].DocOffset].isInFile){
            cout<<Doc[DocRate[j].DocOffset].FileName<<" ";
        }
    }
    cout<<endl<<endl;
    cout<<"Press S for skimming output and C for consecutive output: ";
    cin>>a;
    cin.get();
    cout<<endl<<endl;
    for (int j=0; j<180; j++){ // In each ranked file, Output all the snapshots of a query
        if (Doc[DocRate[j].DocOffset].isInFile){ //For each snapshot in a file, input a character to continue
            Snapshot(MainOffset, DocRate[j].DocOffset);
            if (a=='C')
                getch();
        }
    }
}


void Trie::SaveFile(clock_t ProcessTime, Scoring DocRate[]){ //Save data to file: processing time, the name of the file satisfies the query
    fout<<(float) clock()-ProcessTime<<" ms ";              //Save the doc by ranking
    for (int i=0; i<180; i++){
        if (DocRate[i].score){
            fout<<Doc[DocRate[i].DocOffset].FileName<<" ";
        }
    }
    fout<<endl;
}

void Trie::SaveFile(clock_t ProcessTime){ //Save data to file: processing time, the name of the file satisfies the query
    fout<<(float) clock()-ProcessTime<<" ms "; //Save the doc not by ranking
    for (int i=0; i<NUMBER_OF_FILES; i++){
        if (Doc[i].isInFile){
            fout<<Doc[i].FileName<<" ";
        }
    }
    fout<<endl;
}
//********************************************************************************************************

//************************************DESTRUCTOR*****************************
void Trie::FreeTrie(Node*& pRoot){ //Delete All Node in the trie structure and set it to NULL
    if (!pRoot)
        return;
    for (int i=0; i<63; i++){
        FreeTrie(pRoot->pNext[i]);
    }
    delete pRoot;
    pRoot=NULL;
}

void Trie::Free(){ //Free function execution
    FreeTrie(pRoot);
    FreeTrie(pNRoot);
    delete[] Query;
}
//***************************************************************************

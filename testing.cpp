#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <fstream>
using namespace std;

vector<string> split(string inp, char delim);
int main(int argc, char* argv[])
{
    /*
    string s1 = "TAATGACCTAAATAATCTAAACAAAAGGAAGAGAGATAGTCCGGATTACC";
    string s2 = "TGGGACATGGAAAACCCTCCTTTCTCTCATCAGCTTCCCACCCCACCTCT";
    string s3 = "GCCCAGCGCTAATCATGATTTAATAGCCTTCCTTAATCACTTACTCTGTT";
    string s4 = "TGCTGCTTCATCTAAAAACTTAAGATGCTCTGGGTTAGATCACAGTCTAA";
    string s5 = "CTCATCACAAATGGATAGAACGACCTGGTAGTTTTCCAGATTTCCATTGT";
    string s6 = "CCAAACTAATCAGCCAACACACTCAATGATGCACATTATTTTCCACGTAT";
    string s7 = "ATGGCCTTAGAGATGGGACTAAAAGTCCCGACTGTACTGAGGATGTTTGA";
    string s8 = "CAGGTTTTGCCATTCTAACTGCTAGTGCTGTGTAATGTGGCTAGGAAGAA";
    string s9 = "GCAAGGAACAGAGAGATACAGATATGATTTCCTGGGACCAGCTATAGGAG";
    string s10 = "AGATTCTTCAATTACATCATCTTTGCTCATCCCAAACACCTTGACAAGTA";
    string big = s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9 + s10;
    */
    string big;
    ifstream istr("genome_small.txt");
    string fl;
    vector<string> fileLines;
    while(!istr.eof())
    {
        getline(istr, fl);
        fl.erase(remove(fl.begin(), fl.end(), '\n'), fl.end());
        fileLines.push_back(string(fl));
    }
    for(int i = 0; i < fileLines.size(); i++)
    {
        big = big + fileLines[i];
    }
    
    cout << big << endl;
    int k = 5;
    for(int pos = 0; pos < big.length()-k; pos++)
    {
        string temp = big.substr(pos, k);
        cout << temp << endl;
    }

}

vector<string> split(string inp, char delim)
{
    vector<string> words;
    stringstream ss(inp);
    string temp;
    while(getline(ss, temp, delim))
    {
        words.push_back(temp);
    }
    return words;
}
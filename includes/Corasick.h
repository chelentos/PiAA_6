#ifndef KORASIK_H
#define KORASIK_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <math.h>
#include <cstring>

using namespace std;

const vector<char> alphabet = {'A','C','G','T','N'};

char detect_pos(const char& ch);

struct bohr_vrtx {
   
   vector<int> next_vrtx; 
   
   int par;
   
   vector<int> auto_move;
   
   char symb;
   
   vector<int> pat_nums;
   
   int suff_link = -1;
   
   int good_suff_link = -1;
   
   bool flag = false;
};

class Bohr {
public:

   bohr_vrtx make_bohr_vrtx(int p, char c);
   
   void bohr_ini();
   
   Bohr();
   
   void add_string_to_bohr(const string& s);
   
   bool is_string_in_bohr(const string& s);
   
   int get_suff_link(int v);

   int get_good_suff_link(int v);
 
   int get_auto_move(int v, char ch);
   
   void check(int v,int i);

   void find_all_pos(const string& s);
   
   void add_parts_to_bohr(const string& pattern, char joker);

   void joker_case_results(int size_of_text, int size_of_pattern);
   
   vector<int> GetJokerCaseResaults();
   
   vector<int> GetIndexes();
   
   vector<int> GetPatternNums();
   
   //int GetNumOfInd();
   
   //void PrintBohr();
   
   void PrintDefaultResaults();
   
   void PrintJokerCaseResaults();
   
private:

   vector<int> indexes;
   
   vector<int> pattern_nums;

   vector<bohr_vrtx> bohr;
   
   vector<string> pattern;
   
   vector<int> jokers_case;
   
   vector<int> jokers_case_indexes;
   
};

#endif //KORASIK_H
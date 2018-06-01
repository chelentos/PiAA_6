#include "Corasick.h"

   char detect_pos(const char& ch) {
       switch(ch) {
             case 'A':
               return 0;
             case 'C':
               return 1;
             case 'G':
               return 2;
             case 'T':
               return 3;
             case 'N':
               return 4;
       }
       
       throw invalid_argument("No symbol " + to_string(ch) + " in alphabet!");
   }

   bohr_vrtx Bohr::make_bohr_vrtx(int p, char c) {
      bohr_vrtx v;
      v.next_vrtx = vector<int>(alphabet.size(), -1);
      v.auto_move = vector<int>(alphabet.size(), -1);
      v.par = p;
      v.symb = c;
      return v;
   }
   
   void Bohr::bohr_ini() {
      bohr.push_back(make_bohr_vrtx(0,'$'));
   }
   
   Bohr::Bohr() {
      bohr_ini();
   }
   
   void Bohr::add_string_to_bohr(const string& s){
      int num = 0; //начинаем с корня   
      for (unsigned int  i = 0; i < s.length(); ++i) {
         char ch = detect_pos(s[i]); //получаем номер в алфавите
         if (bohr[num].next_vrtx[ch] == -1) { //-1 - признак отсутствия ребра
            bohr.push_back(make_bohr_vrtx(num, s[i]));
            bohr[num].next_vrtx[ch] = bohr.size() - 1;         
            }
         num = bohr[num].next_vrtx[ch];
      }
      bohr[num].flag = true;
      pattern.push_back(s);
      bohr[num].pat_nums.push_back(pattern.size() - 1);
   }
   
   bool Bohr::is_string_in_bohr(const string& s) {
      int num = 0;   
      for (unsigned int i = 0; i < s.length(); ++i) {
         char ch = detect_pos(s[i]);
         if (bohr[num].next_vrtx[ch] == -1) {
               return false;         
            }
         num=bohr[num].next_vrtx[ch];
      }
      return true;
   }
   
   int Bohr::get_suff_link(int v) {
      if (bohr[v].suff_link == -1) {
         if (v == 0 || bohr[v].par == 0) {
            bohr[v].suff_link = 0;
         }
         else {
            bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), detect_pos(bohr[v].symb));
         }
      }
         
      return bohr[v].suff_link;
   }

   int Bohr::get_good_suff_link(int v) { 
      if (bohr[v].good_suff_link == -1) {
         int  u = get_suff_link(v);
         if (u == 0) {
            bohr[v].good_suff_link = 0;
         }
         else {
            bohr[v].good_suff_link = (bohr[u].flag) ? u : get_good_suff_link(u);
         }
      }
      return bohr[v].good_suff_link;
   }
 
   int Bohr::get_auto_move(int v, char ch) {
      if (bohr[v].auto_move[ch] == -1) {
         if (bohr[v].next_vrtx[ch] != -1) {
            bohr[v].auto_move[ch] = bohr[v].next_vrtx[ch];
         }
         else {
            if (v == 0) {
               bohr[v].auto_move[ch] = 0;
            }
            else {
               bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
            }
         }
      }
      return bohr[v].auto_move[ch];
   }
   
   void Bohr::check(int v,int i) {
      for(int u = v; u!= 0; u = get_good_suff_link(u)) {
        if (bohr[u].flag) {
            for(const auto& num : bohr[u].pat_nums) {
               int pos = i - pattern[num].length();
                  indexes.push_back(pos);
                  pattern_nums.push_back(num);
            }
         }
      }
   }

   void Bohr::find_all_pos(const string& s) {
       int u = 0;
       for(unsigned int i = 0; i < s.length(); i++) {
           u  = get_auto_move(u, detect_pos(s[i]));
           check(u, i + 1);
       }
   }
   
   void Bohr::add_parts_to_bohr(const string& pattern, char joker) {
      string part_of_pattern;
      for(unsigned int i = 0; i < pattern.length(); ++i) {
          if(pattern[i] != joker) {
              part_of_pattern += pattern[i];
              if(pattern[i+1] == joker || pattern[i+1] == '\0') {
                 add_string_to_bohr(part_of_pattern);
                 jokers_case_indexes.push_back(i - part_of_pattern.length() + 2);
                 part_of_pattern = "";
              }
          }
      }
   }

   void Bohr::joker_case_results(int size_of_text, int size_of_pattern) {
       jokers_case.resize(size_of_text);
       for(unsigned int i = 0; i < pattern_nums.size(); ++i) {
         int index = indexes[i] - jokers_case_indexes[pattern_nums[i]] + 1;
         if(index + size_of_pattern > size_of_text)
            continue;
         if(indexes[i] >= jokers_case_indexes[pattern_nums[i]] - 1)
            jokers_case[index]++;
      }

   }
   
   vector<int> Bohr::GetJokerCaseResaults() {
      vector<int> results;
      for(unsigned int i = 0; i < jokers_case.size(); ++i) {
        if(jokers_case[i] == pattern.size())
            results.push_back(i+1);
      }
      
      return results;
   }
   
   void Bohr::PrintDefaultResaults() {
      for(unsigned int i = 0; i < indexes.size(); ++i) {
         cout << indexes[i] + 1 << " " << pattern_nums[i] + 1 << endl;
      }
   }
   
   void Bohr::PrintJokerCaseResaults() {
      for(unsigned int i = 0; i < jokers_case.size(); ++i) {
        if(jokers_case[i] == pattern.size())
            cout << i + 1 << endl;
      }
   }
   
   vector<int> Bohr::GetIndexes() {
      return indexes;
   }
   
   vector<int> Bohr::GetPatternNums() {
      return pattern_nums;
   }
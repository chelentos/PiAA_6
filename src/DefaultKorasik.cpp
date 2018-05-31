#include "Korasik.h"

int main() {
   Bohr br;
   string text = "";
   int num;
   cout << "Enter text T (1≤|T|≤100000): ";
   cin >> text;
   cout << endl << "Enter num of patterns (1≤num≤3000): ";
   cin >> num;
   cout << endl << "Enter " << num << " patterns (P={p1,…,pn}1≤|pi|≤75):" << endl;
   for(int i = 0; i < num; ++i) {
      string pattern;
      cin >> pattern;
      br.add_string_to_bohr(pattern);
   }
   br.find_all_pos(text);
   br.PrintDefaultResaults();
   return 0;
}
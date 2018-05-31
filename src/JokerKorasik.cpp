#include "Korasik.h"

int main() {
   Bohr bohr;
   string text = "";
   string pattern = "";
   char joker;
   cout << "Enter text T (1≤|T|≤100000): ";
   cin >> text;
   cout << endl << "Enter pattern with jokers (P,1≤|P|≤40): ";
   cin >> pattern;
   cout << "Enter joker: ";
   cin >> joker;
   bohr.add_parts_to_bohr(pattern, joker);
   bohr.find_all_pos(text);
   bohr.joker_case_results(text.size(), pattern.size());
   bohr.PrintJokerCaseResaults();
   return 0;
}
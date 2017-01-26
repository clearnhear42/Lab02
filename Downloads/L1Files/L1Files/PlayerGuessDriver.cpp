#if !defined (GUESS_ENUM)
#define GUESS_ENUM
   enum GuessEnum {EXACT, TOO_LOW, TOO_HIGH};
#endif

#include "Text.h"
#include "ReadFile.h"
#include "Random.h"
#include "Keyboard.h"

#include <iostream>
using namespace std;

//insert your methods here












int main()
{
   String* n = createString("n");
   String* ready_str = readString("Are you ready to play? (y/n) ");

   while (compare(n, ready_str) != 0)
   {
      destroyString(ready_str);
   
      //DO THIS














      cout << "You got it in " << total_guess << " guesses!" << endl;
      cin.ignore();
      ready_str = readString("Are you ready to play? (y/n) ");
   }

   destroyString(ready_str);
   destroyString(n);
   return 0;
}

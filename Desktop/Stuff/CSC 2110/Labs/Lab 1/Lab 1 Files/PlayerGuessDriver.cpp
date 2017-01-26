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

int* getRange() {
	String* whatis = readString("Enter the file name containing the range for the secret number: ");
	ReadFile* rf = createReadFile(getText(whatis));
	String* range = readLine(rf);
	String* range2 = readLine(rf);
	int* rangeint;
	rangeint = new int [2];
	rangeint[0] = a_to_i(range);
	rangeint[1] = a_to_i(range2);
	close(rf);
	
	return rangeint;
}

int getSecret (int* range) {
	int high, low;
	high = range[1];
	low = range[0];
	randomInit();
	int random = getRandomInt(low, high);
	return random;
}

int getGuess (int* range) {
	bool right = false;
	String* guess_str = readString("Enter your guess: ");
	String* error_str = createString("Error: Guess not in range.");
	int low, high, guess_int;
	low = range[0];
	high = range[1];
	
	guess_int = a_to_i(guess_str);
	String* rangeS = i_to_a(*range);
	while(right == false) {
		if(a_to_i(guess_str) <= high && a_to_i(guess_str) >= low) {
			right = true;
		}
		if(a_to_i(guess_str) > high || a_to_i(guess_str) < low) {
			displayString(error_str);
			cout << endl;
			delete guess_str;
			guess_str = readString("Enter your guess: ");
		}
	}
	return a_to_i(guess_str);
}

GuessEnum processGuess (int guess, int secret) {
	if(guess < secret) {
		return TOO_LOW;
	}
	if(guess > secret) {
		return TOO_HIGH;
	}
	if(guess == secret) {
		return EXACT;
	}
}

int play (int* range, int secret) {
	int guess;
	int totalguess = 0;
	while(guess != secret) {
		guess = getGuess(range);
		if(processGuess(guess, secret) == TOO_LOW) {
			String* toolow = createString("Too low");
			displayString(toolow);
			cout << endl << endl;
			destroyString(toolow);
		}
		if(processGuess(guess, secret) == TOO_HIGH) {
			String* toohigh = createString("Too high");
			displayString(toohigh);
			cout << endl << endl;
			destroyString(toohigh);
		}
		totalguess = totalguess+1;
	}
	return totalguess;
}

int main()
{
	
   String* n = createString("n");
   String* ready_str = readString("Are you ready to play? (y/n) ");
   int* rangeM;
   int total_guess, secret;
   
   while (compare(n, ready_str) != 0)
	{
		rangeM = getRange();
		secret = getSecret(rangeM);
		destroyString(ready_str);
	  
		//DO THIS
		total_guess = play(rangeM,secret);
		
		cout << "You got it in " << total_guess << " guesses!" << endl;
		cin.ignore();
		ready_str = readString("Are you ready to play? (y/n) ");
		delete rangeM;
	}

   destroyString(ready_str);
   destroyString(n);
   return 0;
}

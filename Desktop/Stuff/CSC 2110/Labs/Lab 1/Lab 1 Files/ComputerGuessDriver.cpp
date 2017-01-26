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
	int high,low,mid;
	bool trigger = false;
	int totalguess = 0;
	high = range[1];
	low = range[0];
	mid = (high + low)/2;
	cout << "Secret: " << secret << endl;
	
	while(!trigger) {
		cout << "Mid: " << mid << endl;
		if(processGuess(mid, secret) == EXACT) {
			cout << "EXACT" << endl;
			mid = secret;
			trigger = true;
		}
		if(processGuess(mid, secret) == TOO_HIGH) {
			cout << "HIGH" << endl;
			high = mid - 1;
			mid = (high + low)/2;
		}
		if(processGuess(mid, secret) == TOO_LOW) {
			cout << "LOW" << endl;
			low = mid + 1;
			mid = (high + low)/2;
		}
		totalguess = totalguess + 1;
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

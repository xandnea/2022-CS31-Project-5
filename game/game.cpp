#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6262)
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int MAXWORDS = 9000;
const int MAXWORDSLEN = 7;
const char WORDFILENAME[] = "C:/School/CS31 Projects/Project 5/words.txt";

int playOneRound(const char words[][MAXWORDSLEN], int nWords, int wordnum) { 

	int attempts = 0;
	char word[MAXWORDSLEN + 1];
	char probe[256];
	strcpy(word, words[wordnum]);
	
	/*strcpy(word, "raven");
	strcpy(word, "egret");
	strcpy(word, "sigh");*/

	//If nWords is not positive, or if wordnum is less than 0 or greater than or equal to nWords, then playOneRound must return −1 without writing anything to cout
	if ((nWords < 0) || (wordnum < 0) || (wordnum >= nWords)) {
		return -1;
	}

	/*cout << "The hidden word is ";
		for (int i = 0; i < strlen(word); i++) {
			cout << word[i];
		}
	cout << endl;*/

	//cin.ignore(10000, '\n'); // to stop the geetline from reading a space for the first probe word of the first round

	while (true) { // infinite loop
		char wordCopy[MAXWORDLEN + 1]; // make copy of hidden word to change
		char probeCopy[256]; // make copy of probe word to change
		strcpy(wordCopy, word);
		
		int silvers = 0;
		int golds = 0;

		bool error = false;
		
		cout << "Probe word: ";
		cin.getline(probe, 256); 
		strcpy(probeCopy, probe);

		if ((strlen(probe) < 4) || (strlen(probe) > 6)) { // error checking for probe word
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			error = true;
			continue;
		}
		
		for (int i = 0; i < strlen(probe); i++) { // error checking for characters in probe word 
			if (!islower(probe[i])) {
				cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
				error = true; // allows while loop to restart from inside for loop with if (error) checks
				break;
			}
		}

		if (error) {
			continue;
		}

		for (int i = 0; i < nWords; i++) { // if probe word isn't in the wordList (list of possible probe words), break for loop & set error to true
			if (strcmp(words[i], probe) == 0) {
				break;
			}
			if ((i == (nWords - 1)) && (strcmp(words[i], probe) != 0)) { 
				cout << "I don't know that word." << endl;
				error = true;
				break;
			}
		}

		for (int i = 0; wordCopy[i] != '\0'; i++) {			// check for golds in probe word first, then check for silvers; if there is a gold or silver, change the letter in both hidden word copy 
			for (int j = 0; probeCopy[j] != '\0'; j++) {	// and probe word copy to be a space (ensures that a letter won't be checked 
				
				if ((word[i] != ' ') && (probeCopy[j] != ' ')) {
					if (wordCopy[j] == probeCopy[j]) {
						golds++;
						wordCopy[j] = ' ';
						probeCopy[j] = ' ';
					}
					else if (wordCopy[i] == probeCopy[j]) {
						silvers++;
						wordCopy[i] = ' ';
						probeCopy[j] = ' ';
					}
				}
			}
		}

		if (golds == strlen(word)) { // if every letter is the same, add to attempts and break while loop 
			attempts++;
			break;
		}

		if (!error) { // if there is still no error, output # of golds and silvers and add to attempts
			cout << "Golds: " << golds << ", Silvers: " << silvers << endl;
			attempts++;
			continue;
		}
	}

	
	return attempts;
}

int main() {

	char wordList[MAXWORDS][MAXWORDLEN + 1];
	int nWords = getWords(wordList, MAXWORDS, WORDFILENAME); // nWords should now be 7265 and wordList should be filled with words 
	int nRounds;
	int minTries = 100000000; // using a huge number to check if nTries is lower than it 
	int maxTries = 0;
	int totalTries = 0;
	int nTries;
	double avgTries;

	if (nWords < 1) { // nWords error checking
		cout << "No words were loaded, so I can't play the game.";
		return 0;
	}
	else if (nWords > MAXWORDS) {
		cerr << "Number of words is greater than max words.";
		return 0;
	}

	// take in # of rounds wanting to be played; if # is -, error message

	cout << "How many rounds do you want to play? ";
	cin >> nRounds;
	cin.ignore(10000, '\n');

	for (int i = 0; i < nRounds; i++) {

		cout << "\nRound " << (i + 1) << endl;

		int indexOfWord = randInt(0, nWords);
		char word[MAXWORDSLEN + 1];
		strcpy(word, wordList[indexOfWord]);


		/*cout << "The hidden word is '";
		for (int i = 0; i < strlen(word); i++) {
			cout << word[i];
		}*/

		cout << "The hidden word is " << strlen(word) << " letters long." << endl;

		nTries = playOneRound(wordList, nWords, indexOfWord);
		//nTries = randInt(1, 10);
		//nTries = 1;

		if (nTries == 1) {
			cout << "You got it in " << nTries << " try." << endl;
		} else {
			cout << "You got it in " << nTries << " tries." << endl;
		}

		totalTries += nTries;
		avgTries = ((double)totalTries / (i+1));
		cout.setf(ios::fixed);
		cout.precision(2);

		if (nTries < minTries) {
			minTries = nTries;
		}
		if (nTries > maxTries) {
			maxTries = nTries;
		}

		//cout << "TOTAL TRIES = " << totalTries << endl;

		cout << "Average: " << avgTries << ", minimum: " << minTries << ", maximum: " << maxTries << endl;

	}
	
	//each round returns the numberOfAttempts, player successfully determining the word is displayed here (main)

}
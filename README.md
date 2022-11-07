# 2022-CS31-Project-5

You have been hired to write a program that plays a word guessing game similar to the one from which Wordle was derived. Here's how one round of the game works: The computer picks a hidden word of four to six letters and tells the player how many letters are in the word. The player tries to determine the hidden word by presenting the computer with a series of probe words. Each probe word is a four to six letter word. If the probe word is the hidden word, the player wins. Otherwise, the computer responds to the probe word with two integers: the number of golds and the number of silvers. Golds and silvers are pairings between a letter in the probe word and the same letter in the hidden word:

A gold is a pairing of a letter in the probe word and the same letter in the hidden word in the same position. For example, if the hidden word is EGRET and the probe word is AGATE, there's one gold: The Gs in both words are in the same position, the second letter.

A silver is a pairing between a letter in the probe word and the same letter in the hidden word, but not in the same position as in the probe word, provided that neither of the two letters are involved in a gold or another silver. For example, if the hidden and probe words are EGRET and AGATE, the Ts form a silver, since we can pair them up but they're not in the same position, since one is the fifth letter of EGRET and the other is the fourth letter of AGATE. The E in AGATE and, say, the first E in EGRET can be paired up to form another silver; the second E in EGRET would then not be part of a silver — we can't pair it up with the E in AGATE because that E is already paired up with the first E in EGRET. If instead we paired the E in AGATE with the second E in EGRET, then the first E in EGRET would have to remain unpaired.

If a letter at a particular position in a word could be considered part of a gold or part of a silver, it must be treated as part of a gold. For example, if the hidden and probe words were EGRET and VIXEN, the E in VIXEN must be paired up with the second E in EGRET to form a gold; that takes priority over pairing it with the first E in EGRET to form a silver.

The player's score for each round is the number of probe words needed to determine the correct word (counting the probe word that matched the hidden word).
As an example, suppose the hidden word is EGRET. Here are some examples of the gold and silver counts for various probe words:


        EGRET        EGRET        EGRET        EGRET        EGRET
        GOOSE        RAGE         SIREN        EERIE        EERIE
        s   s        s sg           gg         gsg     or   g g s
      0 g / 2 s    1 g / 2 s    2 g / 0 s    2 g / 1 s    2 g / 1 s
 
        EGRET        EGRET        EGRET        EGRET
        GREET        OKAPI        REGRET  or   REGRET
        sssgg                     sss ss        sssss
      2 g / 3 s    0 g / 0 s    0 g / 5 s    0 g / 5 s
Your program must ask the player how many rounds to play, and then play that many rounds of the game. After each round, the program must display some statistics about how well the player has played the rounds so far: the average score, the minimum score, and the maximum score.

Here is an example of how the program must interact with the player (player input is in boldface):

	How many rounds do you want to play? 3

	Round 1
	The hidden word is 5 letters long.
	Probe word: assert
	Golds: 1, Silvers: 2
	Probe word: xyzzy
	I don't know that word.
	Probe word: bred
	Golds: 0, Silvers: 2
	Probe word: mucus
	Golds: 0, Silvers: 0
	Probe word: never
	Golds: 2, Silvers: 2
	Probe word: enter
	Golds: 1, Silvers: 2
	Probe word: river
	Golds: 3, Silvers: 0
	Probe word: raven
	You got it in 7 tries.
	Average: 7.00, minimum: 7, maximum: 7

	Round 2
	The hidden word is 5 letters long.
	Probe word: eerie
	Golds: 2, Silvers: 1
	Probe word: rage
	Golds: 1, Silvers: 2
	Probe word: greet
	Golds: 2, Silvers: 3
	Probe word: egret
	You got it in 4 tries.
	Average: 5.50, minimum: 4, maximum: 7

	Round 3
	The hidden word is 4 letters long.
	Probe word: monkey
	Golds: 0, Silvers: 0
	Probe word: puma
	Golds: 0, Silvers: 0
	Probe word: Hello
	Your probe word must be a word of 4 to 6 lower case letters.
	Probe word: what?
	Your probe word must be a word of 4 to 6 lower case letters.
	Probe word: wrap-up
	Your probe word must be a word of 4 to 6 lower case letters.
	Probe word: stop it
	Your probe word must be a word of 4 to 6 lower case letters.
	Probe word: sigh
	You got it in 3 tries.
	Average: 4.67, minimum: 3, maximum: 7
Notice that unknown words and probe strings that don't consist of exactly 4 to 6 lower case letters don't count toward the number of tries for a round.

You can assume the player will always enter an integer for the number of rounds (since you haven't learned a clean way to check that yet). If the number of rounds entered is not positive, write the message

	The number of rounds must be positive.
(not preceded by an empty line) to cout and terminate the program immediately.

The program will be divided across three files: game.cpp, which you will write; utilities.h, which we have written and which you must not change; and utilities.cpp, which we have written and you must not change. You will turn in only game.cpp; when we test your program, our test framework will supply utilities.h and our own special testing version of utilities.cpp.

In order for us to thoroughly test your program, it must have at least the following components:

In game.cpp, a main routine that declares an array of C strings. This array exists to hold the list of words from which the hidden word will be selected. The response to a probe word will be the number of golds and silvers only if the probe word is in this array. (From the example transcript above, we deduce that "xyzzy" is not in the array.) The declared number of C strings in the array must be at least 9000. (You can declare it to be larger if you like, and you don't have to use every element.)

Each element of the array must be capable of holding a C string of length up to 6 letters (thus 7 characters counting the zero byte). So a declaration such as char wordList[9000][7]; is fine, although something like char wordList[MAXWORDS][MAXWORDLEN+1];, with the constants suitably defined, would be stylistically better.

Along with the array, your main routine must declare an int that will contain the actual number of words in the array (i.e., elements 0 through one less than that number are the elements that contain the C strings of interest). The number may well be smaller than the declared size of the array, because for test purposes you may not want to fill the entire array.

Before prompting the player for the number of rounds to play, your main routine must call getWords (see below) to fill the array. The only valid words in the game will be those that getWords puts into this array.

If the player's score for a round is not 1, the message written to cout reporting the score must be

	You got it in n tries.
where n is the score. If the score is 1, the message must be
	You got it in 1 try.
In utilities.cpp, a function named getWords with the following prototype:

	int getWords(char words[][7], int maxWords, const char wordfilename[]);
(Instead of 7, our utilities.cpp actually says MAXWORDLEN+1, where MAXWORDLEN is declared to be the constant 6 in utilities.h.) This function puts words into the words array and returns the number of words put into the array. The array must be able to hold at least maxWords words. The file named by the third argument is the plain text file that contains the words, one per line, that will be put into the array.

You must call getWords exactly once, before you start playing any of the rounds of the game. If your main routine declares wordList to be an array of 10000 C strings and nWords to be an int, you'll probably invoke this function like this:

	const char WORDFILENAME[] = "the path for the word file";
	...
	int nWords = getWords(wordList, 10000, WORDFILENAME);
You may use this 7265-word file if you want a challenging game. Here's how you'd specify the path to the word file for various systems:

Windows: Provide a path for the filename, but use / in the string instead of the \ that Windows paths use, e.g. "C:CS31/P5/mywordfile.txt".
Mac: It's probably easiest to use the complete pathname to the words file, e.g. "/Users/yourUsername/words.txt" or "/Users/yourUsername/CS31/P5/words.txt".
Linux: If you put the words.txt file in the same directory as your .cpp file, you can use "words.txt" as the file name string.
We have given you an implementation of getWords. (Don't worry if you don't understand every part of the implementation.) It fills the array with the four-to-six-letter words found in the file named as its third argument. To do simple testing, you can temporarily change the implementation of getWords to something like this that ignores the file name and hard codes a small number of words to be put in the array:

	int getWords(char words[][7], int maxWords, const char wordfilename[])
	{
	    if (maxWords < 2)
	        return 0;
	    strcpy(words[0], "eagle");
	    strcpy(words[1], "goose");
	    return 2;
	}
Whatever implementation of getWords you use, each C string that it puts into the array must consist of four to six lower case letters; the C strings must not contain any characters that aren't lower case letters. If you have made a temporary change to getWords for test purposes, be sure to restore utilities.cpp back to its original state and verify that your program still runs correctly.

The getWords function must return an int no greater than maxWords. If it returns a value less than 1, your main routine must write

	No words were loaded, so I can't play the game.
to cout and terminate the program immediately, without asking the player for the number of rounds to play, etc.

When we test your program, we will replace utilities.cpp (and thus any changed implementation of getWords you might have made) with our own special testing implementation that will ignore the third argument and fill the array with the test words we want to use.

If getWords returns a value in the range from 1 to maxWords inclusive, your program must write no output to cout other than what is required by this spec. If you want to print things out for debugging purposes, write to cerr instead of cout. When we test your program, we will cause everything written to cerr to be discarded instead — we will never see that output, so you may leave those debugging output statements in your program if you wish.

In game.cpp, a function named playOneRound with the following prototype:
	int playOneRound(const char words[][7], int nWords, int wordnum);
(Again, instead of 7, you can use something like MAXWORDLEN+1.) Using words[wordnum] as the hidden word, this function plays one round of the game, reading from cin and writing to cout. It returns the score for that round. In the transcript above, for round 1, for example, this function is responsible for this much of the round 1 output, no more, no less:

        Probe word: assert
        Golds: 1, Silvers: 2
        Probe word: xyzzy
        I don't know that word.
        Probe word: bred
        Golds: 0, Silvers: 2
        Probe word: mucus
        Golds: 0, Silvers: 0
        Probe word: never
        Golds: 2, Silvers: 2
        Probe word: enter
        Golds: 1, Silvers: 2
        Probe word: river
        Golds: 3, Silvers: 0
        Probe word: raven
Your program must call this function to play each round of the game. Notice that this function does not select a random number and does not tell the user the length of the hidden word; the caller of this function does, and passes the random number as the third argument. Notice also that this function does not write the message about the player successfully determining the hidden word; the caller of this function does. If you do not observe these requirements, your program will fail most test cases.

The parameter nWords represents the number of words in the array; if it is not positive, or if wordnum is less than 0 or greater than or equal to nWords, then playOneRound must return −1 without writing anything to cout.

If for a probe word the player enters a string that does not contain four to six lower case letters or contains any character that is not a lower case letter, the response written to cout must be

	Your probe word must be a word of 4 to 6 lower case letters.
If the player enters a string consisting of exactly four to six lower case letters, but that string is not one of the words in the array of valid words, then the response written to cout must be

	I don't know that word.
To make things interesting, your program must pick hidden words at random using the function randInt, contained in utilities.cpp:

	int randInt(int min, int max);
Every call to randInt returns a random integer between min and max, inclusive. If you use it to generate a random position in an array of n interesting items, you should invoke it as randInt(0, n-1), not randInt(0, n), since the latter might return n, which is not a valid position in an n-element array.

Your program must not use any std::string objects (C++ strings); you must use C strings. Your program must not use any standard library containers (such as vectors, maps, etc.).

You may assume (i.e., we promise when testing your program) that any line entered in response to the probe word prompt will contain fewer than 100 characters (not counting the newline at the end). You may also assume that for any platform on which we run your program, 'z'-'a' == 25 && 'Z'-'A' == 25 is true; in other words, that the character encodings for lower case letters are consecutive, as are those for upper case letters.

Your program must not use any global variables whose values may change during execution. Global constants are all right; our utilities.h declares const int MINWORDLEN = 4; globally, for example, and it's fine for your game.cpp to declare your own additional global constants. The reason for this restriction is that part of our testing will involve replacing your playOneRound function with ours to test some aspects of your main function, or replacing your main with ours to test aspects of your playOneRound. For this reason, you must not use any non-const global variables to communicate between these functions, because our versions won't know about them; all communication between these functions must be through the parameters (for main to tell playOneRound the words, number of words, and hidden word number for a round), and the return value (for playOneRound to tell main the score for that round). Global constants are OK because no function can change their value in order to use them to pass information to another function.

Standard C++ requires that the number of elements in an array you declare to be known at compile time. Since the g31 command on cs31.seas.ucla.edu enforces that requirement, and your program must run under that compiler, you must meet that requirement. Thus, you must not do something like this:

        void somefunction(char someword[])
        {
            char a[strlen(someword)+1]; // Error! strlen(someword) not known at compile time

//============================================================================
// Name        : solitaire.cpp
// Author      : Matthew McCormick
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime> // for time
#include <cstdlib> // for rand
#include <string> // string functions
#include <cctype> // for punc check
#include <algorithm> // for remove_if

using namespace std;

int deck[54]; // makes deck a global variable so that it doesn't need to be passed to functions

void shiftJokers() // moves Joker A down one card and Joker B down two cards
{
//	cout << "in shift jokers" << endl; // << "starting deck is " << endl;
//
//	for(int i = 0; i < 54; i++)
//	{
//		cout << deck[i] << " ";
//	}
//	cout << endl << endl;

	for(int i = 0; i < 54; i++)
		{
			if(deck[i] == 53) // check if joker A is in last position of deck
			{
				if(i == 53) // Joker A is last in deck
				{
					while((i-1) != 0) // moves joker A to index 1
					{
						int temp = deck[i-1];
						deck[i-1] = deck[i];
						deck[i] = temp;
					}
				}
				else // joker A not last in deck, swap joker with next lower card
				{
					int temp = deck[i+1];
					deck[i+1] = deck[i];
					deck[i] = temp;
					i++;
				}
			}
		}

//	cout << "joker A shifted" << endl;
//	for(int i = 0; i < 54; i++)
//		{
//			cout << deck[i] << " ";
//		}
//	cout << endl << endl;

	for(int i = 0; i < 54; i++) // looking for joker B
		{
			if(deck[i] == 54)
			{
				if(i == 53) // check if joker B is last position in deck
				{
					while((i-2) != 0) // Joker B in last, move to index 2
					{
						int temp = deck[i-1];
						deck[i-1] = deck[i];
						deck[i] = temp;
					}
				}
				else if(i == 52) // check if joker B 2nd to last index
				{
					while((i-1) != 0)// joker B in 2nd to last index, move to index 1
					{
						int temp = deck[i+1];
						deck[i+1] = deck[i];
						deck[i] = temp;
					}
					i++;
				}
				else // joker B not at index 52 or 53, shift joker B down two cards
				{
					int temp = deck[i+1];
					deck[i+1] = deck[i];
					deck[i] = temp;
					i++;
					temp = deck[i+1];
					deck[i+1] = deck[i];
					deck[i] = temp;
					i++;
				}
			}
		}
//	cout << "joker B shifted" << endl;
//		for(int i = 0; i < 54; i++)
//			{
//				cout << deck[i] << " ";
//			}
//		cout << endl << endl;
}

void TripleCut() // performs the triple cut: moving all cards above 1st joker below the 2nd joker, all cards below 2nd joker above 1st joker
				 // joker to joker not moving
{
	//cout << "in triple cut" << endl;
	int array[54]; // temp array for use in function
	int above = 100, below; // above is 100 to check if first joker has been found yet. if 100, not found, if !100, first joker found, now looking at 2nd Joker
	for(int i = 0; i < 54; i++)
	{
		if((deck[i] == 53) || (deck[i] == 54)) // check to see if card is joker
		{
			if(above == 100) // this is first joker
			{
				above = i;
			}
			else
			{
				below = i;
			}
		}
	}
	int swap = 0;
	while((below + swap + 1) != 54) // last section moves to front
	{
		array[swap] = deck[below + swap + 1];
		swap++;
	}

	for(int i = above; i <= below; i++) // joker to joker moved to middle
	{
		array[swap] = deck[i];
		swap++;
	}


	for(int i = 0; i < above; i++) // position zero to before first joker moves to end
	{
		array[swap] = deck[i];
		swap++;
	}

	for(int i = 0; i < 54; i++) // copies temp deck into real deck
	{
		deck[i] = array[i];
	}
}

void CountCut() // performs count cut function by moving a group of cards the same size as the value of the last card to the end
				// of the deck, just before the last card
{
	//cout << "in countcut" << endl;
	int array[54];
	int a;

	int cut = deck[53]; // selects cut value
	if(cut == 54)
	{
		cut = 53;
	}

	array[53] = deck[53]; // copies last card of provided deck to temp deck

	a = 0;
	for(int i = cut; i <= 52; i++) // fills array[0] to array[52-cut] with deck[cut] to deck[52]
	{
		array[a] = deck[i];
		a++;
	}

	for(int i = 0; i < cut; i++) // fills array deck from array[52-cut] to array[52]
	{
		array[a] = deck[i]; // array moves from 52 down while deck moves from 0 to cut
		a++;
	}

	for(int i = 0; i < 54; i++) //changes deck to copy array
	{
		deck[i] = array[i];
	}
}

int getOutput() // finds key value for a single character
{
	//cout << "in output" << endl;
	int temp = deck[0]; // looks at value of top card

	if(temp == 54)
	{
		temp = 53;
	}

	if(deck[temp] == 53 || deck[temp] == 54)
	{
		return 100;
	}

	return deck[temp]; // returns value of card that is selected by value of top card
}

void getKeystream(int keys[], int length) // fills encode array with keystream values
{
	//cout << "in Keystream" << endl;
	for (int i = 0; i < length; i++)
	{
		cout << "i = " << i << endl;
		shiftJokers();

		TripleCut();

		CountCut();

		keys[i] = getOutput();

		if(keys[i] == 100)
		{
			i--;
			cout << "i = " << i << " output was a joker." << endl;
		}

		if(keys[i] > 26)
		{
			keys[i] -= 26;
		}

		cout << keys[i] << " " << endl;
	}
}

int main() {

	srand(time(0)); // seed random number
	string input, output, temp;

	for (int i = 0; i < 54; i++) // fills deck array with values from 1 to 54
	{
		deck[i] = i+1;
	}

	for (int i=0; i<(54-1); i++) // shuffles deck
	{
		int r = i + (rand() % (54-i)); // Random remaining position.
		int temp = deck[i]; deck[i] = deck[r]; deck[r] = temp;
	}

//	shiftJokers();

cout << "What is your message? Write out numbers please." << endl; // prompts for message to be encoded
getline (cin, input);

for (int i = 0, len = input.size(); i < len; i++) // removes punctuation, whitespace and converts to all caps
    {
        if (ispunct(input[i]))
        {
            input.erase(i--, 1);
            len = input.size();
        }
        if (isspace(input[i]))
	    {
		    input.erase(i--, 1);
		    len = input.size();
	    }
        input.at(i) = toupper(input.at(i));
        cout << input[i];
    }
cout << endl << endl;

int encode[input.length()]; // creates an int array the same length as the message

for(int i = 0; i < input.length(); i++) // fills int array with the value of each letter of message
{
	encode[i] = (int(input.at(i)) - 64);
	cout << encode[i] << " ";
}
cout << endl << "ASCII value of written message" << endl << endl;

int length = input.length();

int keys[length];

getKeystream(keys, length);

for(int i = 0; i < length; i++)
{
	cout << keys[i] << " ";
}
cout << endl << "value of keystream" << endl << endl;
	return 0;
}

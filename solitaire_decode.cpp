//============================================================================
// Name        : solitaire_decode.cpp
// Author      : Matthew McCormick
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <ctime> // for time
#include <cstdlib> // for rand
#include <string> // string functions
#include <cctype> // for punc check
#include <algorithm> // for remove_if
#include <fstream> // for file I/O
#include <sstream> // for stringstream output to file

using namespace std;

int deck[54] = {21, 27, 45, 5, 14, 43, 41, 42, 12, 25, 22, 7, 53, 18, 47, 34, 29, 13, 32, 52, 16, 39, 54, 3, 48, 23, 19, 8, 9, 31,
		15, 44, 46, 24, 30, 38, 10, 49, 35, 20, 40, 11, 6, 36, 51, 1, 2, 50, 33, 37, 26, 28, 4}; // used for decoding, fill with saved order

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
			if(deck[i] == 53) // check joker A position in deck
			{
				if(i == 53) // Joker A is last in deck
				{
					cout << "Joker A is last in deck, shifting to index 1" << endl;
					while((i-1) != 0) // moves joker A to index 1
					{
						int temp = deck[i-1];
						deck[i-1] = deck[i];
						deck[i] = temp;
						i--;
					}
				}
				else // joker A not last in deck, swap joker with next lower card
				{
					//cout << "Joker A not last, swapping with next card" << endl;
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
					//cout << "Joker B last in deck, moving to index 2" << endl;
					while((i-2) != 0) // Joker B in last, move to index 2
					{
						int temp = deck[i-1];
						deck[i-1] = deck[i];
						deck[i] = temp;
						i--;
					}
				}
				else if(i == 52) // check if joker B 2nd to last index
				{
					//cout << "Joker B second to last in deck, moving to index 1" << endl;
					while((i-1) != 0)// joker B in 2nd to last index, move to index 1
					{
						int temp = deck[i-1];
						deck[i-1] = deck[i];
						deck[i] = temp;
						i--;
					}

				}
				else // joker B not at index 52 or 53, shift joker B down two cards
				{
					//cout << "Joker B not last or second to last, shifting down two positions" << endl;
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

	if(deck[temp] == 53 || deck[temp] == 54) // card counted to from top card is joker, return 100 so this key is run again
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
		//cout << "Finding output key for letter " << i << endl;
		shiftJokers();

		TripleCut();

		CountCut();

		keys[i] = getOutput();

		if(keys[i] == 100) // card counted to was a joker, needs to be repeated
		{
			i--; // this sets loop back one iteration so no letters are lost
			//cout << "i = " << i << " output was a joker." << endl;
		}

		if(keys[i] > 26)
		{
			keys[i] -= 26;
		}

		//cout << keys[i] << " ";
	}
	//cout << endl;
}

int main() {

	ofstream outs;
	string input;

	outs.open("decoded.txt"); // output file in case you want to check
	if(outs.fail())
	{
		cout << "Output file opening failed." << endl;
		exit(1);
	}

	cout << "What is your message?" << endl; // prompts for message to be encoded
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
			//cout << input[i];
		}
	cout << endl;

	int encode[input.length()]; // creates an int array the same length as the message
	char send_this[input.length()]; // used for char array that is ouput to screen or file as encoded or decoded message

	for(unsigned int i = 0; i < input.length(); i++) // fills int array with the value of each letter of message
	{
		encode[i] = (int(input.at(i)) - 64);
		//cout << encode[i] << " ";
	}
	//cout << endl << "ASCII value of written message" << endl << "length of message is " << input.length() << endl << endl;

	int length = input.length(); // this is so I don't have to type input.length() anymore

	int keys[length];

	getKeystream(keys, length); // fills an int array the same length as message with keystream numbers

	for(int i = 0; i < length; i++) // adds keystream values to int version of message
	{
		int a = encode[i];
		int b = keys[i];
		if(a <= b)
		{
			a += 26;
			a = (a - b);
			encode[i] = a;
		}
		else
		{
			a = ((a - b) % 26);
			encode[i] = a;
		}
	}

	//for(int i = 0; i < length; i++) // for printing keystream and letters to screen if desired
	//{
	//	send_this[i] = (keys[i] + 64);
	//	cout << keys[i] << " " << send_this[i] << " ";
	//}

	for(int i = 0; i < length; i++) // for printing letters to screen if desired
	{
		send_this[i] = (encode[i] + 64);
		cout << send_this[i];
	}

	//cout << endl << "value of keystream" << endl << endl;

	for(int i = 0; i < length; i++) // for sending message to output file if desired
	{
		outs << send_this[i];
	}

	return 0;
}

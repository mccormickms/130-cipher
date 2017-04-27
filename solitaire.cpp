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

void shiftJokers(int cards[])
{
for(int i = 0; i < 54; i++)
	{
		if(cards[i] == 53)
		{
			if(i == 53)
			{
				while((i-1) != 0)
				{
					int temp = cards[i-1];
					cards[i-1] = cards[i];
					cards[i] = temp;
				}
			}
			else
			{
				int temp = cards[i+1];
				cards[i+1] = cards[i];
				cards[i] = temp;
				i++;
			}
		}
	}

for(int i = 0; i < 54; i++)
	{
		if(cards[i] == 54)
		{
			if(i == 53)
			{
				while((i-2) != 0)
				{
					int temp = cards[i-1];
					cards[i-1] = cards[i];
					cards[i] = temp;
				}
			}
			else if(i == 52)
			{
				while((i-1) != 0)
				{
					int temp = cards[i+1];
					cards[i+1] = cards[i];
					cards[i] = temp;
				}
				i++;
			}
			else
			{
				int temp = cards[i+1];
				cards[i+1] = cards[i];
				cards[i] = temp;
				i++;
				temp = cards[i+1];
				cards[i+1] = cards[i];
				cards[i] = temp;
				i++;
			}
		}
	}
}

void TripleCut(int cards[])
{
	int array[54];
	int above = 100, below;
	for(int i = 0; i < 54; i++)
	{
		if((cards[i] == 53) || (cards[i] == 54))
		{
			if(above == 100)
			{
				above = i;
			}
			else
			{
				below = i; cout << "below is " << below << endl << endl;
			}
		}
	}
	int swap = 0;
	while((below + swap + 1) != 54) // last section moves to front
	{
		array[swap] = cards[below + swap + 1];
		swap++;
	}

	for(int i = above; i <= below; i++) // joker to joker moved to middle
	{
		array[swap] = cards[i];
		swap++;
	}


	for(int i = 0; i < above; i++) // position zero to before first joker moves to end
	{
		array[swap] = cards[i];
		swap++;
	}

	for(int i = 0; i < 54; i++)
	{
		cards[i] = array[i];
	}

//	for (int c = 0; c < 54; c++) // prints post triple cut deck
//	{
//		cout << cards[c] << " ";
//	}
//
//	cout << endl << endl;
}

void getKeystream(int cards[], int keys[], int length)
{
	for (int i = 0; i < length; i++)
	{















	}
}

int main() {

	int deck[54]; // this represents the deck, with values from 1 to 52, with 53 and 54 being the jokers
	srand(time(0)); // seed random number
	string input, output, temp;
	//int encoded[]; // to store the number value of the message. will be manipulated and sent out.

	for (int i = 0; i < 54; i++) // fills array with "deck"
	{
		deck[i] = i+1;
		//cout << deck[i] << endl;
	}

	for (int i=0; i<(54-1); i++) // shuffles deck
	{
		int r = i + (rand() % (54-i)); // Random remaining position.
		int temp = deck[i]; deck[i] = deck[r]; deck[r] = temp;
	}

	for (int c = 0; c < 54; c++) // prints shuffled deck
	{
		cout << deck[c] << " ";
	}

cout << endl << endl;

shiftJokers(deck);




cout << "Shifted Jokers" << endl;
for (int c = 0; c < 54; c++) // prints shuffled deck
{
	cout << deck[c] << " ";
}
cout << endl << endl;

TripleCut(deck);

cout << "Triple Cut" << endl;
for (int c = 0; c < 54; c++) // prints shuffled deck
{
	cout << deck[c] << " ";
}
cout << endl << endl;

//cout << "What is your message?" << endl;
//getline (cin, input);
//
//for (int i = 0, len = input.size(); i < len; i++) // removes punctuation, whitspace and converts to all caps
//    {
//        if (ispunct(input[i]))
//        {
//            input.erase(i--, 1);
//            len = input.size();
//        }
//        if (isspace(input[i]))
//	    {
//		    input.erase(i--, 1);
//		    len = input.size();
//	    }
//        input.at(i) = toupper(input.at(i));
//    }

//cout << input << endl;

//int encode[input.length()]; // creates an int array the same length as the message
//
//for(int i = 0; i < input.length(); i++) // fills int array with the value of each letter of message
//{
//	encode[i] = (int(input.at(i)) - 64);
//	//cout << encode[i] << endl;
//}
//
//int keys[input.length()];




	return 0;
}

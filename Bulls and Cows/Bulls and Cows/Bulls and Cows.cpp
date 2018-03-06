#include "stdafx.h"
#include "std_lib_facilities.h"

vector<int>answers = { -1, -1, -1, -1 };	//-1 prevents any 0s being ignored when createAnswers() is first called
vector<int>guesses(4);
int a, b, c, d, bulls, cows, seed, score = 0;
bool keepPlaying = true;
string userContinue = " ";

void welcomeMessage()
{
	cout << "Okay, so, I'm thinking of 4 different integers between 0 - 9 \n" <<
		"If you guess the right number but in the wrong order you have 1 cow \n"
		"If you guess both the number and the order correctly you get 1 bull \n"
		"You need 4 bulls to win \n"
		"Enter you guesses like so: 1 2 3 4 \n"
		"Ready? \n... \n..... \nGO!\n";
	//"But first, please enter positive integer \n";
}
void createAnswers()
{
	bool valid_int;
	int temp;

	for (int x = 0; x < 4; x++)
	{
		temp = rand() % 10;
		valid_int = true;
		for (int y = 0; y < x; y++)		//This loop prevents two numbers appearing twice in the answer
		{
			if (temp == answers[y])
			{
				valid_int = false;

			}
		}
		if (valid_int == true) answers[x] = temp;
		else x--;
	}
}
void createGuesses()
//Precondition: Guesses must be valid integers
{
	cin >> a >> b >> c >> d;
	if (!cin) error("createGuesses() precondition");
	guesses[0] = a;
	guesses[1] = b;
	guesses[2] = c;
	guesses[3] = d;
}
void checkGuesses()
//Precondition: Guesses must be between 0 - 9 
{
	for (unsigned int i = 0; i < answers.size(); i++)
	{
		for (unsigned int j = 0; j < answers.size(); j++)
		{
			if (guesses[i] > 9 || guesses[i] < 0) error("checkGuesses() precondition");
			if (guesses[i] == answers[j])
			{
				if (i == j) bulls++;
				else cows++;
			}
		}
	}
}
void winningMessage()
{
	cout << "You win! \n"
		"Would you like to play again? Y = Yes, N = No\n";
	cin >> userContinue;
	if (userContinue == "N" || userContinue == "n")
	{
		keepPlaying = false;
		cout << "Thanks for playing! \n";
		if (score > 1) cout << "You won " << score << " rounds! \n";
		else cout << "You won " << score << " round! \n";
	}
	else if (userContinue == "Y" || userContinue == "y")
	{
		cout << "Fantastic! \n"; /* Before we start, please enter any random integer : \n";
								 cin >> seed;*/
		cout << "Ready? \n... \n..... \nGO!\n";
		createAnswers();
		bulls = 0;
		cows = 0;
	}
	else error("Invalid Input: winningMessage()");
}
void bullsAndCows()
//Numbers guessing game using a vector of guesses compared against a vector of answers selected at random however !random atm
{
	bulls = 0;
	cows = 0;
	createAnswers();
	while (keepPlaying == true)
	{
		createGuesses();
		checkGuesses();

		cout << bulls << " bull(s) and " << cows << " cow(s) \n";

		if (bulls == 4)
		{
			score++;
			winningMessage();
		}
		else
		{
			cout << "Please try again \n";
			bulls = 0;
			cows = 0;
		}
	}
}

int main()
{
	try
	{
		cout << "Please enter any random integer: ";
		cin >> seed;
		srand(seed);
		welcomeMessage();
		bullsAndCows();
	}

	catch (exception& e)
	{
		cerr << "Error: " << e.what() << '\n';
	}
	catch (...)
	{
		cerr << "Unknown error \n";
	}
}
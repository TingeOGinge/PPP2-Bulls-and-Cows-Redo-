#include "stdafx.h"
#include "std_lib_facilities.h"

vector<char>answers = { '!', '!', '!', '!' };	// used '!' to represent any answers that have failed to generate
vector<char>guesses(4);
int bulls = 0, cows = 0, score = 0;
bool keepPlaying = true;

void createAnswers()
//Creates 4 random, different letters and arranges them in a vector 
{
	bool valid_int;
	char result; 

	for (int x = 0; x < 4; x++){
		result = 'a' + rand() % 26;
		valid_int = true;
		for (int y = 0; y < x; y++){		//This loop prevents two numbers appearing twice in the answer
			if (result == answers[y]) valid_int = false;
		}
		if (valid_int == true) answers[x] = result;
		else x--;
	}
}
void createGuesses()
//Precondition: Guesses must letters between a - z
//User enters 
{
	char a;
	for (int x = 0; x < 4; x++){
		cin >> a;
		if (a > 122 || a < 97) error("checkGuesses() precondition");
		guesses[x] = a;
	}
}
void checkGuesses()
//Precondition: Guesses must be between a - z  
{
	for (unsigned int i = 0; i < answers.size(); i++)
	{
		for (unsigned int j = 0; j < answers.size(); j++)
		{
			if (guesses[i] > 122 || guesses[i] < 97) error("checkGuesses() precondition");
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
	string userContinue = " ";
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
		cout << "Fantastic! \n" 
		"Ready? \n... \n..... \nGO!\n";
		createAnswers();
		bulls = 0;
		cows = 0;
	}
	else error("Invalid Input: winningMessage()");
}
void bullsAndCows()
//Letters guessing game using a vector of guesses compared against a vector of answers selected at random however !random atm
{
	createAnswers();
	while (keepPlaying == true){
		createGuesses();
		checkGuesses();

		cout << bulls << " bull(s) and " << cows << " cow(s) \n";

		if (bulls == 4){
			score++;
			winningMessage();
		}
		else{
			cout << "Please try again \n";
			bulls = 0;
			cows = 0;
		}
	}
}

int main(){
	try{
		cout << "Please enter any random integer: ";
		int seed;
		cin >> seed;
		cout << "Okay, so, I'm thinking of 4 different letters between a - z \n" 
		"If you guess the right letter but in the wrong order you have 1 cow \n"
		"If you guess both the letter and the order correctly you get 1 bull \n"
		"You need 4 bulls to win \n"
		"Enter you guesses like so: 1 2 3 4 \n"
		"Ready? \n... \n..... \nGO!\n";
		srand(seed);
		welcomeMessage();
		bullsAndCows();
	}
	catch (exception& e){
		cerr << "Error: " << e.what() << '\n';
	}
	catch (...){
		cerr << "Unknown error \n";
	}
}

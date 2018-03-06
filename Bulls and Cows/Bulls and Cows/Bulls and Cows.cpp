#include "std_lib_facilities.h"

class ans_gues{
public:
	char answer;
	char guess; 
};
vector<ans_gues>game(4);
int bulls = 0, cows = 0, score = 0;
bool keepPlaying = true;

void createAnswers()
//Creates 4 random, different letters and arranges them in a vector 
{
	bool valid;
	char result; 

	for (int x = 0; x < 4; x++){
		result = 'a' + rand() % 26;
		valid = true;
		for (int y = 0; y < x; y++){		//This loop prevents two numbers appearing twice in the answer
			if (result == game[y].answer) valid = false;
		}
		if (valid == true) game[x].answer = result;
		else x--;
	}
}
void createGuesses()
//Precondition: Guesses must letters between a - z
//User enters 4 letters as their attempt to win 
{
	char a;
	for (int x = 0; x < 4; x++){
		cin >> a;
		if (a > 122 || a < 97) error("checkGuesses() precondition");
		game[x].guess = a;
	}
}
void checkGuesses()
//Precondition: Guesses must be between a - z  
{
	for (unsigned int i = 0; i < game.size(); i++){
		for (unsigned int j = 0; j < game.size(); j++){
			if (game[i].guess > 122 || game[i].guess < 97) error("checkGuesses() precondition");
			if (game[i].guess == game[j].answer){
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
	if (userContinue == "N" || userContinue == "n"){
		keepPlaying = false;
		cout << "Thanks for playing! \n";
		if (score == 1) cout << "You won " << score << " round! \n";
		else cout << "You won " << score << " rounds! \n";
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
		bullsAndCows();
	}
	catch (exception& e){
		cerr << "Error: " << e.what() << '\n';
	}
	catch (...){
		cerr << "Unknown error \n";
	}
}

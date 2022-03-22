#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string answer;

void ip_toupper(string& str)
{
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		str[i] = toupper(str[i]);
	}
}

string match(string guess)
{
    bool found = false;
    string match = "";
    for (int i=0; i<5; i++)
    {
        // If guess is correct
        if (guess[i] == answer[i])
        {
            match += guess[i];
            match += "! ";
        }
        else
        {
            found = false;
            for (int j=0; j<5; j++)  // For each letter in ANSWER
            {
                // Finds if letter is anywhere in ANSWER
                if (guess[i] == answer[j])
                {
                    match += guess[i];
                    match += "* ";
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                match += guess[i];
                match += "  ";
            }
        }
    }
    return match;
}

string randomWord(ifstream& wordstream)
{  
	string word;
	wordstream.clear();
	wordstream.seekg(0);
	int rn = rand() % 998;
	for (int i = 0; i < rn; i++)
	{
		getline(wordstream, word);
	}
    if (word.length() != 5) word = randomWord(wordstream);
    ip_toupper(word);
    return word;
}

int main() 
{ 
    ifstream wordstream;
    wordstream.open("eng_words_998.txt");
    answer = randomWord(wordstream);
  
    string guess;
    bool gameover = false;
    cout << "Enter guess: ";
    cin >> guess;
    ip_toupper(guess);
    while (guess != "QUIT" && !gameover)
    {    
        cout << match(guess) << endl;
        cout << endl << "Enter guess: ";
        cin >> guess;
        ip_toupper(guess);
        if (guess == answer)
        {
            gameover = true;
            cout << "You win! The answer is " << answer;
        }
    }
  
    wordstream.close();
    return 0;
}
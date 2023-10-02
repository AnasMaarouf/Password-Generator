#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>

#define First_Characrter_Is_Capital_Letter 0b0000000000000000000000000000000000000000000000000000000000000001
#define Ignore_Capital_Letters 0b0000000000000000000000000000000000000000000000000000000000000010
#define Ignore_Non_Capital_Letters 0b0000000000000000000000000000000000000000000000000000000000000100
#define Ignore_Special_Characters 0b0000000000000000000000000000000000000000000000000000000000001000
#define Ignore_Numbers 0b0000000000000000000000000000000000000000000000000000000000010000
std::string RandomPasswordGenerator(unsigned int length /*IN*/, uint64_t Arg_register /*IN*/);

using namespace std;

int main()
{
	srand(time(nullptr));

	ofstream file_containing_generated_passwords("passwords.txt");

	constexpr unsigned int Nr_of_passwords = 20;
	cout << "Random passwords:" << endl;
	for (size_t i = 0; i < Nr_of_passwords; i++) {
		string password = RandomPasswordGenerator(rand() % 3 + 25, 0);

		if (i >= 9) {
			cout << i + 1 << "." << setw(2) << " " << password << endl;
			file_containing_generated_passwords << i + 1 << "." << setw(2) << " " << password << endl;
		}
		else {
			cout << i + 1 << "." << setw(3) << " " << password << endl;
			file_containing_generated_passwords << i + 1 << "." << setw(3) << " " << password << endl;
		}
	}
	cout << endl;

	return 0;
}




std::string RandomPasswordGenerator(unsigned int length /*IN*/, uint64_t Arg_register /*IN*/) {
    std::mt19937 rng(time(nullptr));
    std::uniform_int_distribution<int> uni(0, 4);

    constexpr char NonCapitalLetters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

    constexpr char CapitalLetters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

    constexpr char SpecialCharacters[] = { '~', '!', '@', '#', '%', '^', '&', '*', '_', '-', '+', '=', '`', ' ',
                                 static_cast<char>(124), '(', ')', '{', '}', '[', ']', ':', ';', '<', '>', ',', '.', '?', '/', '$' };

    constexpr char Numbers[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    if ((Arg_register & Ignore_Numbers & Ignore_Special_Characters & Ignore_Non_Capital_Letters & Ignore_Capital_Letters))
        return "ERROR";

    std::string Password;

    for (unsigned int i = 0; i < length; i++) {
        const int Random_Category_Selector = uni(rng);
        
        if ((Arg_register & First_Characrter_Is_Capital_Letter) && i == 0) {    // First letter must be capital letter argument.
            Password += CapitalLetters[rand() % sizeof(CapitalLetters)];
        }

        switch (Random_Category_Selector)
        {
            case 0:
                if (!(Arg_register & Ignore_Capital_Letters)) {
                    Password += CapitalLetters[rand() % sizeof(CapitalLetters)];
                    break;
                }

            case 1:
                if (!(Arg_register & Ignore_Non_Capital_Letters)) {
                    Password += NonCapitalLetters[rand() % sizeof(NonCapitalLetters)];
                    break;
                }

            case 2:
                if (!(Arg_register & Ignore_Special_Characters)) {
                    Password += SpecialCharacters[rand() % sizeof(SpecialCharacters)];
                    break;
                }

            case 3:
                if (!(Arg_register & Ignore_Numbers)) {
                    Password += Numbers[rand() % sizeof(Numbers)];
                    break;
                }

            default:
                i--;
                break;
        }
    }

    return Password;
}

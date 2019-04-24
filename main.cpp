/*
 * File name:		Group Project 1
 * Name:				Bryan Poulson
 * Course:			COP 2224C at Valencia College
 * Instructor:		David Stendel
 * Description:		A group project that features various menu driven functions. The functions will 
 *                  perform various
 *					operations on a data arrays.
 * Team Members:		Eric Leitzke, Yamil Rivera, Jeffrey Herbeck, Anthony Pass
 * Date:				9/29/2014
 */

// Preprocessor Directives
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <locale>
#include <iomanip>
using namespace std;
#define CLS system ("cls")
//flush is knowledge from C. Works well to avoid keyboard buffer errors during inputs.
#define FLUSH fflush(stdin)
#define SIZE 100

// Prototypes
void alphabetizeTheLetters(char letters[], int counter);
void alphabetizeTheNames(vector<string>& name);
void checkAccount(vector<string> person, vector<double> &balance);
void displayMenu();
void displayTheNames(vector<string> name);
void displayTheArray(const char letters[], int counter);
void depositAccount(vector<double> &balance, int find);
void getCharFromUser(char letters[], int &counter);
void getNameFromUser(vector<string>& name);
bool isTheArrayPalindrome(const char letters[], int counter);
void mode(char letters[]);
void openAccount(vector<string> &person, vector<double> &balance);
void reverseAlphabetizeTheLetters(char letters[], int counter);
void searchForCharacter(char letters[], int counter);
bool switchEm(char letters[], int i);
void withdrawAccount(vector<double> &balance, int find);



/*
 * Name:				main()
 * Parameters:		None.
 * Processes:		Displays a menu of choices via displayMenu() for the user. Uses a switch with 
 *                  bleed-through cases to call various functions as desired by the user.
 * Return Value:	an integer representing an error code; if the program ends without error, zero
 *					will be returned to the calling program or operating system.
 */
int main()
{
    // Variables
    char letters[SIZE], choice;
    int counter = 0, accountTracker = 0;
    
    vector<string> name;
    vector<string> person;
    vector<double> balance;
    
    do
    {
        CLS;
        displayMenu();
        choice = cin.get();
        switch (choice){
            case 'i':
            case 'I':
                getCharFromUser(letters, counter);
                break;
            case 'a':
            case 'A':
                alphabetizeTheLetters(letters, counter);
                break;
            case 'c':
            case 'C':
                checkAccount(person, balance);
                break;
            case 'r':
            case 'R':
                reverseAlphabetizeTheLetters(letters, counter);
                break;
            case 's':
            case 'S':
                searchForCharacter(letters, counter);
                break;
            case 'd':
            case 'D':
                displayTheArray(letters, counter);
                break;
            case 'o':
            case 'O':
                openAccount(person, balance);
                break;
            case 'p':
            case 'P':
                isTheArrayPalindrome(letters, counter);
                break;
            case 'q':
            case 'Q':
                cout << "Good Bye!" << endl;
                break;
            case 'm':
            case 'M':
                mode(letters);
                break;
            case 'n':
            case 'N':
                getNameFromUser(name);
                break;
            case 'x':
            case 'X':
                alphabetizeTheNames(name);
                break;
            case 'y':
            case 'Y':
                displayTheNames(name);
                break;
            default:
                cout << "Please make a valid selection!" << endl;
                system("pause");
                cin.ignore();
        }
        cout << endl;
        system("pause");
    } while (choice != 'q' && choice != 'Q');
    
    return 0;
}

/*
 * Name:				alphabetizeTheLetters()
 * Parameters:		An array of characters of size that is determined by constant SIZE as defined 
 *                  in preprocessor directives. An int value is also used
 *					which is a counter variable; it is passed by value for this function.
 * Processes:		Compares the values in the array elements in sets of two. If the first is 
 *                  GREATER THAN the second, it calls switchEm() to order them numerically
 *					based on their ASCII values; also know as a "Bubble sort". Will error check for 
 *                  an empty array first, and let user know to enter in characters if need.
 * Return Value:		None.
 */
void alphabetizeTheLetters(char letters[], int counter)
{
    int i = 0;
    bool switchMade = false;
    int bottom = counter - 1;
    
    if (counter == 0){
        cout << "Please enter some characters into the array first." << endl;
        cin.ignore();
        
    }
    else if (counter != 0)
    {
        do
        {
            switchMade = false;
            for (i = 0; i < bottom; i++)
            {
                if (letters[i] > letters[i + 1])
                {
                    switchMade = switchEm(letters, i);
                }
            }
            
            bottom--;
        } while (switchMade == true);
        
        cout << "Array has been alphabetized!" << endl;
        FLUSH;
        
    }
}

/*
 * Name:				alphabetizeTheNames()
 * Parameters:		A vector of strings; it is passed by reference for this function.
 * Processes:		Checks for valid vector size. Uses sort function to sort strings alphabetically.
 * Return Value:		none.
 */
void alphabetizeTheNames(vector<string>& name)
{
    FLUSH;
    
    if(name.size() == 0)
    {
        cout << endl << "Names must be added first!" << endl;
    }
    else
    {
        sort (name.begin(), name.end());
        cout << endl << "This names have been alphabetized!" << endl;
    }
}

/*
 * Name:				checkAccount()
 * Parameters:		A vector of strings and a vector of doubles represent a bank customer's name 
 *                  and account balance; they are both passed by reference.
 * Processes:		Uses an int variable to reference an account number and a char variable to get
 *                  user input for a sub-menu. The int variable is subtracted
 *					by 1 to match the subcript in the vectors for the proper account owner and their 
 *                  balance and if it matches the user's input account number
 *					it display name and balance and presents sub-menu, else it informs the user the 
 *                  account does not exists and ends function. If the sub-menu
 *					was triggered, a switch handles user's selection, calling on either the 
 *                  depositAccount or withdrawAccount functions or quiting the sub-menu
 *					thus ending this function.
 * Return Value:		None.
 */
void checkAccount(vector<string> person, vector<double> &balance)
{
    int find;
    char choice = 'A';
    
    cout << endl << "Welcome, please enter your account number: ";
    cin >> find;
    --find;
    if (find < person.size() && find >= 0)
    {
        do
        {
            CLS;
            cout << endl << "Hello " << person[find] << ", your current balance is $" << balance[find];
            cout << endl << "Would you like to make a transaction?" << endl;
            cout << "(D)eposit" << endl;
            cout << "(W)ithdrawal" << endl;
            cout << "(Q)uit" << endl;
            cout << "Please state your choice: ";
            cin >> choice;
            FLUSH;
            switch(choice)
            {
                case 'd':
                case 'D':
                    depositAccount(balance, find);
                    break;
                    
                case 'q':
                case 'Q':
                    //Left intentionally blank
                    break;
                    
                case 'w':
                case 'W':
                    withdrawAccount(balance, find);
                    break;
                    
                default:
                    cout << "Invalid entry. Try again!" << endl;
                    system("pause");
                    cin.ignore();
            }
        } while (choice != 'Q' && choice != 'q');
    }
    else
    {
        cout << endl << "Sorry, no such account exists";
    }
    cout << endl << "Have a nice day!" << endl;
    FLUSH;
}

/*
 * Name:				displayMenu()
 * Parameters:		None.
 * Processes:		Multiple cout statements to relay a menu to the user.
 * Return Value:		None.
 */

void displayMenu()
{
    cout << "********************************" << endl;
    cout << "*          Main Menu           *" << endl;
    cout << "*    Sorting and Searching     *" << endl;
    cout << "*           Program            *" << endl;
    cout << "********************************" << endl;
    cout << "(I)nput characters to the array." << endl;
    cout << "(A)lphabetize the array. (Voids Palindrome)" << endl;
    cout << "(R)everse-alphabetize the array. (Voids Palindrome)" << endl;
    cout << "(S)earch for a character. (This will alphabetize the array first!)" << endl;
    cout << "(D)isplay the array." << endl;
    cout << "(P)alindrome?" << endl;
    cout << "(M)ost common letter. (Mode)" << endl;
    cout << "(N) Add names to the vector." << endl;
    cout << "(X) Alphabetize the names in the vector." << endl;
    cout << "(Y) Display the names in the vector." << endl;
    
    cout << "(O)pen new bank account." << endl;
    cout << "(C)heck bank account." << endl;
    
    cout << "(Q)uit." << endl;
    cout << "Please make a selection:";
}

/*
 * Name:				displayTheArray()
 * Parameters:		An array of characters of size that is determined by constant SIZE as defined 
 *                  in preprocessor directives. An int value is also used
 *					which is a counter variable; it is passed by value for this function.
 * Processes:		Error checks for an empty array via the counter variable. If the array is not 
 *                  empty, it will use a for loop to loop through and display the contents of the 
 *                  character array in a VERTICAL fashion. Const used to prevent unintended array 
 *                  changes.
 * Return Value:		None.
 */

void displayTheArray(const char letters[], int counter)
{
    int i = 0;
    
    FLUSH;
    
    if (counter == 0)
    {
        cout << "Please enter some characters into the array first." << endl;
        
    }
    else
    {
        cout << "The letters are: ";
        
        for (i = 0; i < counter; i++)
        {
            cout << letters[i] //<< endl;
            ;
        }
        
        // system("pause");
        //
    }
    
}

/*
 * Name:				displayTheNames()
 * Parameters:		A vector of strings; it is passed by reference for this function.
 * Processes:		Checks for valid vector size. Uses for loop to display strings contained in 
 *                  vector.
 * Return Value:		none.
 */

void displayTheNames(vector<string> name)
{
    FLUSH;
    if(name.size() == 0)
    {
        cout << endl << "Names must be added first!" << endl;
    }
    else
    {
        cout << endl << "Names:" << endl;
        for(int i = 0; i < name.size(); i++)
        {
            cout << name[i] << endl;
        }
    }
}

/*
 * Name:				depositAccount()
 * Parameters:		A vector of doubles represents a customer's account balance while and int 
 *                  variable represents the vector subscript, the vector is passed
 *					by reference, while the variable is passed by value.
 * Processes:		Uses a temp variable to hold user's input for the transaction amount. The temp 
 *                  amount is added to the current balance on the vector.
 * Return Value:		None.
 */

void depositAccount(vector<double>&balance, int find)
{
    int tempAmount;
    
    cout << endl << "State the amount you wish to deposit: $";
    cin >> tempAmount;
    balance[find] = balance[find] + tempAmount;
    cout << endl << "Deposit successful!" << endl;
    system("pause");
}

/*
 * Name:				getCharFromUser()
 * Parameters:		An array of characters of size that is determined by constant SIZE as defined 
 *                  in preprocessor directives. An int value is also used
 *					which is a counter variable; it is passed by REFERENCE for this function.
 * Processes:		Counter variable passed by reference is incremented for each letter entered 
 *                  into the character array. A while loop determines that as
 *					long as "ENTER" is not read from the keyboard, add the input to the array by 
 *                  using cin.get() and uses toupper() to convert all inputs into capital letters. 
 *                  Also uses a while loop to discard any extra characters over the size of the 
 *                  array as allowed by the defined constant SIZE in the preprocessor directives.
 * Return Value:		None.
 */

void getCharFromUser(char letters[], int &counter)
{
    char letter;
    counter = 0;
    
    cout << "Enter up to " << SIZE << " characters for the array. Any extras will be discarded!" << endl;
    
    FLUSH;
    
    //The && *counter < SIZE logic gate discards the extra characters that would otherwise flood
    //out of array/display function.
    //Example: if SIZE is 10, for some reason you can type in 15 characters and it will display
    //them all and you could search for hidden characters.
    while ((letter = cin.get()) != '\n' && counter < SIZE)
    {
        letters[counter] = toupper(letter);
        counter = counter + 1;
    }
    
    
}

/*
 * Name:				getNameFromUser()
 * Parameters:		A vector of strings; it is passed by reference for this function.
 * Processes:		Uses temp string variable to check for ESC character; also a temporary location 
 *                  for toupper() function. At which point if found valid, inserts string at end of 
 *                  vector.
 * Return Value:		None.
 */

void getNameFromUser(vector<string>& name)
{
    
    string temp = "";
    locale loc;
    
    cout << endl << "Please insert a name to be alphabatized: " << endl << "press Q to quit!" << endl << endl;
    FLUSH;
    
    while(temp != "Q")
    {
        cin >> temp;
        
        for(int i = 0; i < temp.length(); i++)
        {
            temp[i] = toupper(temp[i],loc);
        }
        if(temp != "Q")
        {
            name.insert(name.end(), temp);
            cout << temp << " has been added!" << endl << endl;
        }
        
    }
    FLUSH;
}

/*
 * Name:			    isTheArrayPalindrome()
 *                   written by Jeffrey Herbeck
 * Parameters:		An array of characters of size that is determined by constant SIZE as defined 
 *                  in preprocessor directives. An int value is also used
 *					which is a counter variable; it is passed by value for this function.
 * Processes:		Compares the values in the array elements in a set. It compares first to last 
 *                  value to last to first value  based on their ASCII values
 * Return Value:	    true if is a palindrome and false if it is not.
 */

bool isTheArrayPalindrome(const char letters[], int counter)
{
    int i = 0, index = 0;
    bool isPala = true;
    FLUSH;
    
    if (counter == 0)
    {
        cout << "Please enter some characters into the array first." << endl;
    }
    else
    {
        for (index = counter - 1 ; i < counter; --index)
        {
            if (letters[i] != letters[index]){
                isPala = false;
            }
            i++;
        }
        if (isPala)
        {
            displayTheArray(letters, counter);
            cout <<  ". They are a palindrome!" << endl;
            
        }
        else
        {
            displayTheArray(letters, counter);
            cout << ". They are not a palindrome." << endl;
        }
        
        return isPala;
    }
}

/*
 * Name:				mode(char letters[])
 * Parameters:		An array of characters represents user input. It is passed by reference.
 * Processes:		Uses an array initialzed to zero to count each instance of a letter by passing 
 *                  the user input through the empty array and using ASCII values. Which ever 
 *                  character is used the most will then be displayed.
 * Return Value:		None.
 */

void mode(char letters[])
{
    int alpha[255] = {0};
    char index;
    int i, max;
    
    // Counts each letter
    for(i = 0; letters[i] != 0; i++)
    {
        ++alpha[letters[i]];
    }
    // Find Mode
    max = alpha[0];
    index = 0;
    for(i = 0; letters[i] != 0; i++)
    {
        if( alpha[i] > max)
        {
            max = alpha[i];
            index = i;
        }
    }
    cout << "The most common letter is: " << (char)index << "\n";
    FLUSH;
}

/*
 * Name:				openAccount()
 * Parameters:		A vector of strings and a vector of doubles represent a bank customer's name 
 *                  and account balance; they are both passed by reference.
 * Processes:		Uses seperate temporary variables to hold input that is then passed to string 
 *                  and double vectors respectively. Runs temp string variable
 *					through toupper() functions for uniformity of name input before passing the name 
 *                  string to the string vector.
 * Return Value:		None.
 */

void openAccount(vector<string> &person, vector<double> &balance)
{
    string tempName;
    double tempAmount;
    locale loc;
    
    cout << endl << "Enter account applicant's name: ";
    cin >> tempName;
    FLUSH;
    for(int i = 0; i < tempName.length(); i++)
    {
        tempName[i] = toupper(tempName[i],loc);
    }
    person.push_back(tempName);
    cout << endl << "Welcome " << tempName << endl;
    cout << "Please input your initial balance: $";
    cin >> tempAmount;
    balance.push_back(tempAmount);
    cout << endl << "Thank you " << tempName << ", your account is now open.\n";
    cout << "Your account number is " << setfill('0') << setw(4) << person.size() <<endl;
    FLUSH;
}

/*
 * Name:				reverseAlphabetizeTheLetters()
 * Parameters:		An array of characters of size that is determined by constant SIZE as defined 
 *                  in preprocessor directives. An int value is also used
 *					which is a counter variable; it is passed by value for this function.
 * Processes:		Compares the values in the array elements in sets of two. If the first is 
 *                  LESS THAN the second, it calls switchEm() to order them numerically backwards
 *					based on their ASCII values; also know as a "Bubble sort", just backwards. Will 
 *                  error check for an empty array first, and let user know to enter in characters 
 *                  if need.
 * Return Value:		None.
 */

void reverseAlphabetizeTheLetters(char letters[], int counter)
{
    int i;
    bool switchMade = false;
    int bottom = counter - 1;
    
    if (counter == 0)
    {
        cout << "Please enter some characters into the array first." << endl;
        FLUSH;
    }
    
    else if (counter != 0)
    {
        do
        {
            switchMade = false;
            
            for (i = 0; i < bottom; i++)
            {
                if (letters[i] < letters[i + 1])
                {
                    switchMade = switchEm(letters, i);
                }
            }
            
            bottom--;
            
        } while (switchMade == true);
        
        cout << "Array has been reverse-alphabetized!" << endl;
        
        FLUSH;
        
    }
}

/*
 * Name:				searchForCharacter()
 * Parameters:		An array of characters of size that is determined by constant SIZE as defined 
 *                  in preprocessor directives. An int value is also used
 *					which is a counter variable; it is passed by value for this function.
 * Processes:		Error checks for an empty array. Utilizes a binary search to search for a 
 *                  letter indicated by the user via ASCII values. For this to work, this function 
 *                  calls switchEm() and alphabetizes the array first. The one lapse is the use of 
 *                  a break statement if the searched-for value is found; this will allow it to 
 *                  drop out of the while loop. A line comment is used at this break statement.
 * Return Value:		None.
 */

void searchForCharacter(char letters[], int counter)
{
    int first = 0, i = 0;
    int last = counter - 1;
    int middle = (first + last) / 2;
    int bottom = counter - 1;
    char search;
    bool switchMade = false;
    
    FLUSH;
    
    if (counter == 0)
    {
        cout << "Please enter some characters into the array first." << endl;
    }
    
    else if (counter != 0)
    {
        cout << "Enter a character to search for:" << endl;
        search = toupper(cin.get());
        FLUSH;
        
        do
        {
            switchMade = false;
            for (i = 0; i < bottom; i++)
            {
                if (letters[i] > letters[i + 1])
                {
                    switchMade = switchEm(letters, i);
                }
            }
            bottom--;
        } while (switchMade == true);
        
        while (first <= last)
        {
            if (letters[middle] < search)
            {
                first = middle + 1;
            }
            else if (letters[middle] == search)
            {
                cout << search << " found at location " << middle + 1 << endl;
                
                break;
            }
            else
            {
                last = middle - 1;
            }
            middle = (first + last) / 2;
        }
        if (first > last)
        {
            cout << "Not found! " << search << " is not in the array." << endl;
        }
        FLUSH;
    }
    
}

/*
 * Name:				switchEm()
 * Parameters:		An array of characters of size that is determined by constant SIZE as defined 
 *                  in preprocessor directives. An int value is also used
 *					which is a counter variable; it is passed by value for this function.
 * Processes:		Uses a three step process and a temporary char variable to save and swap values 
 *                  in adjacent indexes of an array.
 * Return Value:	A boolean value to indicate that this function was called and executed.
 *                  This value is used in various loops in alphabetizeTheLetters(),
 *					reverseAlphabetizeTheLetters() searchForCharacter().
 */

bool switchEm(char letters[], int i)
{
    char temp = letters[i];
    letters[i] = letters[i + 1];
    letters[i + 1] = temp;
    
    return true;
}

/*
 * Name:				withdrawAccount()
 * Parameters:		A vector of doubles represents a customer's account balance while and int 
 *                  variable represents the vector subscript, the vector is passed
 *					by reference, while the variable is passed by value.
 * Processes:		Uses a temp variable to hold user's input for the transaction amount. The temp 
 *                  amount is substracted from the current balance on the vector
 *					if it does not exceed it, else it informs the user that their withdrawal amount 
 *                  exceeds the balance.
 * Return Value:        None.
 */

void withdrawAccount(vector<double>&balance, int find)
{
    int tempAmount;
    
    cout << endl << "State the amount you wish to withdraw: $";
    cin >> tempAmount;
    if (tempAmount <= balance[find])
    {
        balance[find] = balance[find] - tempAmount;
        cout << endl << "Withdrawal successful!" << endl;
    }
    else
    {
        cout << endl << "Your request exceeds your balance!" << endl;
    }
    system("pause");
}



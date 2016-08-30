#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Login.h"
#include "OpenCV.h"

using namespace std;


//initiates variables for class
vector<User> program_users;
string name = "";
int day = 0;
int month = 0;
int year = 0;
int feet = 0;
int inches = 0;
string gender = "";
string color = "";
OpenCV* recognizer = new OpenCV();

int main()
{
    
    //////////////////////////////////////
    ///Initializes reading the csv file///
    //////////////////////////////////////
    
    //opens the cv file
    ifstream myFile("user.csv");
    string line;
    //initializes the line which will be the line it is located on
    
    while (getline(myFile, line))
    //goes through the different lines in the csv file
    
    {
        string a,b,c,d,e;
        //All the parameters of the user class
        
        istringstream s(line);
        string field;
        while (getline(s, field,','))
        //divides the csv file and finds it's parameters by separating through commas
        
        {
            
            
            
            a = field;
            // a = name
            
            while (getline(s, field,','))
            {
                //makes the strings initialized in the beginning all of the characteristics of the user
                
                if (b == "")
                {
                    b = field;
                    // b = birthdate
                    
                }
                else if (b != "" && c == "" && d == "")
                {
                    c = field;
                    // c = height
                    
                }
                else if (b != "" && c!= "" && d == "")
                {
                    d = field;
                    // d = gender
                    
                }
                else{
                    e = field;
                    // e = favorite color
                    
                }
            }
            
        }
        User* temp = new User(a,b,c,d,e);
        // creates a new user on a new line in the csv file
        program_users.push_back(*temp);
        
    }
    
    
    ////////////////////////////
    //////////Sorting//////////
    //////////////////////////

    
    sort( program_users.begin( ), program_users.end( ), [ ]( const User& lhs, const User& rhs )
    {
        return lhs.name < rhs.name;
    });

    
    
    ////////////////////////////
    ///Initializes Main Menu///
    //////////////////////////
    
    cout << "=====================================================================";
    cout << endl;
    cout << endl;
    //All of the '==' will be used to separate the menus for easier viewing
    
    cout << "Welcome to the Computer Vision Recognition System Acquisition Mission";
    // Title of the project
    
    
    // Main Menu
    
    cout << endl;
    cout << endl;
    cout << "1. Login";
    cout << endl;
    cout << "2. Add User";
    cout << endl;
    cout << "3. Exit";
    cout << endl;
    cout << endl;
    cout << "================================";
    cout << endl;
    cout << endl;
    
    ////////////////////////////
    //do while loop for main menu//
    //////////////////////////
    
    bool statement = true;
    //do while loop
    do {
        cout << "Choose an option: ";
        cout << endl;
        int n;
        
        // The user should not be able to input anything but
        //      an integer and this method should check for it
        
        // Note : also add to other options where an integer
        //      is inputted as an option
        
        
        /////////////////////////////
        ///checks menu input/////////
        ////////////////////////////
        
        while(true)
        {
            
            cin >> n;
            cout << endl;
            //checks for letters
            if(cin.fail())
            {
                
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter a number that is related to a menu choice";
                cout << endl;
                continue;
                
            }
            
            //checks for range
            
            if(n < 1 || n > 3)
            {
                
                cout<< "Please enter a number that is related to a menu choice";
                cout << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
                
            }
            
            //double checks for decimals and leaves while with proper input
            else
            {
                false;
                break;
            }
            
            
        }
        if (n == 1)
        {
            cout << "================================";
            cout << endl;
            cout << "Login";
            cout << endl;
            cout << "1. Recognize"; 
            //Open OpenCV once they figure out how to implement it
            
            cout << endl;
            cout << "2. Exit";
            cout << endl;
            cout << "Choose an option: ";
            int n;
            cin >> n;
            cout << endl;
            
            
            if (n == 1)
                //facial recognition would pop up instead of asking for the username
            {
                
                string user = recognizer->recognize(program_users);
                //This would take all of the pictures and associate it with a user
                
                // There should be a total of 49 pictures taken
                
                // Make sure to keep a straight face and not have anyone else in the
                //      field of view of the webcam!
                
                if (user == "No User Found")
                {
                    cout << "No User was Found." << endl;
                    
                    //Restarts the main menu if it doesn't recognize the face
                    
                    cout << "=====================================================================\n\n";
                    cout << "Computer Vision Recognition System Acquisition Mission Menu\n\n";
                    cout << "1. Login\n";
                    cout << "2. Add User\n";
                    cout << "3. Exit\n\n";
                    cout << "================================\n\n";
                    continue;
                }
                else
                // If the user is found
                
                {
                    vector<User>::iterator it;
                    // Scan through the vector of users
                    
                    
                    for(it = program_users.begin(); it < program_users.end(); it++){
                        if (it->getName() == user) {
                            it->print();
                        }
                    }
                }
                

                // ifstream myFile("user.csv");
                // string line;
                // while (getline(myFile, line))
                // {
                //     std::istringstream s(line);
                //     std::string field;
                //     while (getline(s, field,','))
                //     {
                //         cout << field << "\t";
                //         cout << endl;
                //     }
                // }
                
            } else if (n == 2){
                cout << "=====================================================================\n\n";
                cout << "Computer Vision Recognition System Acquisition Mission Menu\n\n";
                cout << "1. Login\n";
                cout << "2. Add User\n";
                cout << "3. Exit\n\n";
                cout << "================================\n\n";
                continue;
            }
        }
        
        else if (n == 2)
        {
            User* users = new User();
            cout << "Ready to create a new user!" << endl;
            cout << "Please type in a username that is between 1 and 15 characters inclusive: ";
            cout << endl;
            cin >> name;
            cout << endl;
            while(name.length() > 15)
            {
                //check for username already being used?
                if(name.length() > 15)
                {
                    //lets user know that they need a shorter name
                    cout << "That username is too long!";
                    cout << endl;
                    //re-asks user for appropriate name
                    cout << "Please type in a username that is between 1 and 15 characters inclusive: ";
                    cout << endl;
                    cin >> name;
                    cin.clear();
                    cout << endl;
                }
                else
                {
                    //lets user know that they need a longer name
                    cout << "That username is too short!";
                    cout << endl;
                    //re-initiates username request
                    cout << "Please type in a username that is between 1 and 15 characters inclusive: ";
                    cout << endl;
                    cin >> name;
                    cin.clear();
                    cout << endl;
                }
                
            }
            
            users->setName(name);
            cin.clear();
            ////////////////////////////
            //checks for day of birth//
            ///////////////////////////
            cout << "Please type the day you were born";
            cout << endl;
            //gives ecample of input to user
            cout << "\tFor example, a person born on the 22nd day of the month would enter the number 22";
            cout << endl;
            
            
            while(true)
            {
                
                cin >> day;
                cout << endl;
                //checks for letters
                if(cin.fail())
                {
                    
                    cin.clear();
                    cin.ignore(1000, '\n');
                    
                    //asks user for month
                    cout << "Please enter a number that is a day of the month" << endl;
                    continue;
                    
                }
                
                
                //checks for range
                n = day;
                
                if(n < 1 || n > 31)
                {
                   
                    //re-iterates request
                    cout<< "Please enter a number that is a day of the month";
                    cout << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                    
                }
                
                //double checks for decimals and leaves while with proper input
                else
                {
                    
                    //breaks out of loop
                    n = day;
                    false;
                    break;
                }
                
                
            }
            
            ///////////////////////////
            ////asks user for month////
            //////////////////////////
            
            cout << "Please enter the numeric value of the month you were born in";
            cout << endl;
            cout << "\tFor example, a user born in April would enter the number 4: ";
            cout << endl;
            true;
            while(true)
            {
                
                cin >> month;
                //checks for letters
                cout << endl;
                if(cin.fail())
                {
                    
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Please enter a number that is between 1 and 12 inclusive" << endl;
                    continue;
                    
                }
                
                //checks for decimals
                
                n = month;
                
                if(n < 1 || n > 12)
                {
                    
                    cout<< "Please enter a number that is between 1 and 12 inclusive";
                    cout << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                    
                }
                
                //double checks for decimals and leaves while with proper input
                else
                {
                    n = month;
                    false;
                    break;
                }
            }
            
            cout << endl;
            
            
            ////////////////
            ///check year///
            ////////////////
            
            
            cout << "Please enter the year you were born in using 4 digits";
            cout << endl;
            cout << "\tFor example, a user born in 1998 would enter 1998 ";
            cout << endl;
            true;
            while(true)
            {
                
                cin >> year;
                
                //checks for letters
                
                cout << endl;
                if(cin.fail())
                {
                    
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Please enter the year you were born in using 4 digits" << endl;
                    continue;
                    
                }
                //checks for decimals
                
                n = year;
                
                if(n < 1900 || n > 2016)
                {
                    
                    if(n < 1900)
                    {
                        
                        //checks that age isnt riduculously old
                        cout << "There's now way you can be over 116 years old!" << endl;
                        cout<< "Please enter the year you were born in using 4 digits";
                        cout << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        continue;
                    }
                    else
                    {
                        //checks that year isnt too far into the future
                        cout << "Are you from the future?";
                        cout << endl;
                        cout<< "Please enter the year you were born in using 4 digits";
                        cout << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        continue;
                        
                    }
                    
                    
                }
                
                //double checks for decimals and leaves while with proper input
                else
                {
                    //breaks from loop
                    n = year;
                    false;
                    break;
                }
            }
            
            //sets day for user
            users->setDay(day);
            
            //sets month for user
            users->setMonth(month);
            
            //sets year for user
            users->setYear(year);
            
            //puts birthday info of user into string format
            string birthday = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
            //////////////////
            ///check height///
            //////////////////
            
            
            //asks for height
            cout << "Please enter your height in feet and inches";
            cout << endl;
            
            //gives example of height
            cout << "\tFor example, a user who is exactly 5 feet would enter 5 for feet and 0 inches";
            cout << endl;
            true;
            while(true)
            {
                cout << "Feet: " << endl;
                
                cin >> feet;
                //checks for letters
                if (cin.fail()) 
                {
                    
                    cin.clear();
                    cin.ignore(1000, '\n');
                    
                    //re-iterates question
                    cout << "Please enter your height in feet and inches" << endl;
                    continue;
                    
                }
                //checks for decimals
                
                n = feet;
                
                if (n < 0 || n > 10) 
                {
                    
                    //re-asks for height
                    cout << "Please enter a reasonable height";
                    cout << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }
                
                //double checks for decimals and leaves while with proper input
                else 
                {
                    
                    //breaks from loop
                    n = feet;
                    false;
                    break;
                }
            }
            
            ////////////////////////////
            ////gets inches of height///
            ///////////////////////////
            
            
            true;
            while(true)
            {
                //asks for inches
                cout << "Inches: " << endl;
                
                cin >> inches;
                //checks for letters
                
                cout << endl;
                if(cin.fail())
                {
                    
                    cin.clear();
                    cin.ignore(1000, '\n');
                    
                    //re-iterates inches request
                    cout << "Please enter a number that is between 0 and 11 inclusive" << endl;
                    continue;
                    
                }
                //checks for decimals
                
                n = inches;
                
                if(n < 0 || n > 11)
                {
                    
                    //re-iterates request
                    cout<< "Please enter a number that is between 0 and 11 inclusive";
                    cout << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                    
                }
                
                //double checks for decimals and leaves while with proper input
                else
                {
                    
                    //breaks from loop
                    n = inches;
                    false;
                    break;
                }
                
            }
            
            //sets user feet
            users->setFeet(feet);
            
            //sets user inches
            users->setInches(inches);
            
            //creates string height with feet and inches
            string height = to_string(feet) + "\'"  + to_string(inches) + "\"";
            
            //asks for gender
            cout << "Please enter your gender as \"Male\", \"Female\", or \"Other\"";
            cout << endl;
            cin >> gender;
            cin.clear();
            while(true)
            {
                cout << endl;
                
                //checks that user entered one of the options
                if(gender != "Male" && gender != "Female" && gender != "Other" && gender != "male" &&
                   gender != "female" && gender != "other")
                {
                    //re0iterates question for gender
                    cout << "Please enter your gender as \"Male\", \"Female\", or \"Other\"";
                    cout << endl;
                    cin >> gender;
                    cin.clear();
                }
                else
                {
                    //breaks from loop
                    false;
                    break;
                }
            }
            
            //sets gedner info for user
            users->setGender(gender);
            cout << endl;
            
            /////////////////////////
            ////asks for color//////
            ////////////////////////
            cout << "Please enter your favorite color: ";
            cout << endl;
            cin >> color;
            cin.clear();
            
            
            cout << endl;
            
            //sets color for user
            users->setColor(color);
            
            User* temp = new User(name, birthday, height, gender, color);
            
            program_users.push_back(*temp);
            
            
            sort( program_users.begin( ), program_users.end( ), [ ]( const User& lhs, const User& rhs )
            {
                    return lhs.name < rhs.name;
            });
            
            recognizer->addNewUser(name, program_users);
            
            //cout<<(program_users.back()).name<<endl;
            
            //writes user and user info to csv file for openCV/records to be re-outputed when recognized
            //by the camera
            users->writeToFile();
            
            
            //re prints menu options
            cout << "=====================================================================\n\n";
            
            cout << "Computer Vision Recognition System Acquisition Mission Menu\n\n";
            cout << "1. Login\n";
            cout << "2. Add User\n";
            cout << "3. Exit\n\n";
            
            cout << "================================\n\n";
            
            
        }
        else if (n == 3)
        {
            
            //prints out end message
            cout << "================================";
            cout << endl;
            cout << endl;
            cout << "Thanks for coming! See you next time!";
            cout << endl;
            cout << endl;
            cout << "=====================================================================";
            cout << endl;
            
            //exits overall loop thus ending code and program
            statement = false;
        }
    } while (statement == true);
    
    
    return 0;
}

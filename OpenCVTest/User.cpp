//
//  User.cpp
//  OpenCVTest
//
//  Created by Archit Rathi on 4/17/16.
//  Copyright © 2016 Archit Rathi. All rights reserved.
//

#include <iostream>
#include "User.h"
#include <string>

using namespace std;

User::User()
{
    
}


//////////////////////////
///Creates the new User///
//////////////////////////

User::User(string name, string birthday, string height, string gender, string color){
    this->name = name;
    this->birthday = birthday;
    this->height = height;
    this->gender = gender;
    this->color = color;
}


///////////////////////////////////////////////////////
///Print the user information after being recognized///
///////////////////////////////////////////////////////

void User::print(){
    cout<<"Name: "<<this->name<<'\n';
    cout<<"Birthday: "<<this->birthday<<'\n';
    cout<<"Height: "<<this->height<<'\n';
    cout<<"Gender: "<<this->gender<<'\n';
    cout<<"Color: "<<this->color<<'\n';
    
}


///////////////////////////////////
///Creates Username for new user///
///////////////////////////////////

void User::setName(string name)
{
    this->name = name;
}


// retrieving user name

string User::getName()
{
    return this->name;
}


///////////////////////////////////
///Creates Birhtday for new User///
///////////////////////////////////

void User::setBirthday(int day, int month, int year)
{
    // turn ints into strings in order to write in csv file
    
    this->birthday = to_string(day) + "/" + to_string(month) + "/" + to_string(month);
}


//retrieving user birthday

string User::getBirthday()
{
    return this->birthday;
}


//////////////////////////
///Creates user Height///
//////////////////////////

void User::setHeight(int feet, int inches)
{
    this->height = to_string(feet) + "\'"  + to_string(inches) + "\"";
}


//retrieving user birthday

string User::getHeight()
{
    return this->height;
}


/////////////////////////////
///Sets the Gender of User///
/////////////////////////////

void User::setGender(string gender)
{
    this->gender = gender;
}


// retrieves user gender

string User::getGender()
{
    return this->gender;
}


/////////////////////////////////////
///Sets the favorite color of User///
/////////////////////////////////////

void User::setColor(string color)
{
    this->color = color;
}


// retrieves user's favorite color

string User::getColor()
{
    return this->color;
}


//retrieves the day the user was born

int User::getDay()
{
    return this->day;
}


//retrieves to month the user was born

int User::getMonth()
{
    return this->month;
}


// sets the month the user was born

void User ::setMonth(int month)
{
    this->month = month;
}


// sets the day the user was born

void User::setDay(int day)
{
    this->day=day;
}


// sets the year the user was born

void User::setYear(int year)
{
    this->year=year;
}


// gets the first part of the height, the feet

int User::getFeet()
{
    return this->feet;
}


// gets the second part of the height, the inches

int User::getInches()
{
    return this->inches;
}


// sets the feet part of the height when being askes

void User::setFeet(int feet)
{
    this->feet=feet;
}


// sets the inches part of the height when being asked

void User::setInches(int inches)
{
    this->inches=inches;
}


/////////////////////////////////////////////
///Writes the information of the file////////
///Includes facial recognition information///
/////////////////////////////////////////////

void User::writeToFile()
{
    ofstream myfile;
    myfile.open("user.csv", ofstream :: app);
    myfile << '\n';
    myfile << this->name <<",";
    myfile << this->day << "/" << this->month << "/" << this->year << ",";
    myfile << this->feet << "\' " << this->inches << "\"" << ",";
    myfile << this->gender << ",";
    myfile << this->color << "\n";
    
    myfile.close();
    
}

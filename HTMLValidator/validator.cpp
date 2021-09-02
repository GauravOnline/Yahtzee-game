//validator.cpp
//Description: this program allows us to check if an input file is valid html file or not
//Author : Gaurav Shienhmar
//Date modified : 06/05/21
#include <fstream>
#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

void check(string &str, Stack<string> &st);
bool isTagname(string &tagname);
bool isOpeningTag(string &s);
bool isClosingTag(string &s);
bool isEmptyTag(string &s);


int linecount = 0;//keeping track of lines in the file



int main(){


	string filename;
	ifstream file;

	cout<<"Enter filename : ";
	cin>>filename;

    file.open(filename);
	if (!file) {
		cout << "No such file";
	}
	else {

		string str, line;
		Stack<string> st;
		int x,y;

		while(getline(file, line)){

			linecount++;


			x = line.find('<');
			y = line.find('>');

			while(!(x == -1 && y == -1) ){  				//It means run the loop till I get index for both '<' and '>'

				if(x!= -1 && y!= -1){     					//I found both the indexes in the same line
					str = line.substr(x + 1, y - x - 1);

					check(str,st);    						//extract the tagname and check what kind of tag it is
					line = line.substr(y+1); 				//updating the line to look forward
					x = line.find('<');
					y = line.find('>');
				}

				else if(y == -1){              				//I found the opening bracket but not the closing one in the line
					str = line.substr(x + 1);

					while(y== -1 && getline(file, line)){   //read and store in the str till I get closing bracket 
						linecount++;
						y = line.find('>');

						if(y!= -1){
							str += line.substr(0,y);
						}

						else{
							str+= line;
						}

					}

					check(str,st);                         //send the str to check what kind of tag is it
					line = line.substr(y+1);               //updating the line to look forward    
					x = line.find('<');
					y = line.find('>');
				}

				else if( y!= -1){                         //I got a closing bracket but not opening. So it is invalid
					cout<<"\nInvalid tag  Error at line "<<linecount;
					exit(1);
				}
		    }
		    
	    }

		if(st.isEmpty()){
			cout<<"\n VALID HTML FILE";

		}
		else{
			cout<<"Invalid HTML file";
		}

		
		
	}
}

//input a string with reference containing the tag without the opening and closing bracket
//we look for the starting and ending postion in the string where we have something other than space
//we extract this part as a subtring and store it in string tagname
//we check if the tagname is valid or not
//This will allow us to check whter its an opening tag or not

bool isOpeningTag(string &s){

	int pos1, pos2;
	string tagname;
	pos1 = s.find_first_not_of(' ');
	pos2 = s.find_last_not_of(' ');


	tagname = s.substr(pos1, (pos2 - pos1 + 1));


	if(isTagname(tagname)){
		s = tagname;
		return true;
	}

	else{
		return false;
	}

}

//input a string with reference containing the tag without the opening and closing bracket
//We now check that the first char of this string is '/'. If not, we return false
//if the first char is '/', we extract a substring without this '/'
//we look for the starting and ending postion in the string where we have something other than space
//we extract this part as a subtring and store it in string tagname
//we check if the tagname is valid or not
//if valid, we change the string s to this trimmed version only and return true.
//else we return false

bool isClosingTag(string &s){

	if(s.at(0) != '/'){
		return false;
	}

	int pos1, pos2;
	string tagname, substring;
	substring = s.substr(1,s.size() - 1);
	pos1 = substring.find_first_not_of(' ');
	pos2 = substring.find_last_not_of(' ');

	tagname = substring.substr(pos1, (pos2 - pos1 + 1));

	if(isTagname(tagname)){
		s = tagname;
		return true;
	}

	else{
		return false;
	}


}


//input a string with reference containing the tag without the opening and closing bracket
//We now check that the last char of this string is '/'. If not, we return false
//if the last char is '/', we extract a substring without this '/'
//we look for the starting and ending postion in the string where we have something other than space
//we extract this part as a subtring and store it in string tagname
//we check if the tagname is valid or not
//if valid, we creturn true, else we return false.

bool isEmptyTag(string &s){

	if(s.at(s.size() - 1) != '/'){
		return false;
	}

	int pos1, pos2;
	string tagname, substring;
	substring = s.substr(0,s.size() - 1);
	pos1 = substring.find_first_not_of(' ');
	pos2 = substring.find_last_not_of(' ');

	tagname = substring.substr(pos1, (pos2 - pos1 + 1));

	return isTagname(tagname);

}

//input a string tagname with reference
//we check if this tagname is an actual html tagname or not
bool isTagname(string &tagname){

	if(tagname == "html" || tagname == "head" || tagname == "body" || tagname == "p" || tagname == "br" || tagname == "li"  || tagname == "h1"  || tagname == "h2"  || tagname == "ul"  || tagname == "ol"){
		return true;
	}

	else{
		return false;
	}

}
			
//input string str with reference and stack st with reference
//we check the type of the str
//if it is an opening tag, we push it into the stack
//if closing tag, we pop a tag out of the stack and compare with this tag. If they do not match, we show the error
//if it is empty tag, we dont need any action
//if it is not any of the tag, we shoe error.
void check(string &str, Stack<string> &st){


	if(isOpeningTag(str)){
		//cout<<"\n goint "<<str;
		st.push(str);
	}

	else if(isClosingTag(str)){


		if(st.isEmpty()){
			cout<<"No opening tag for "<<str<<"Error at line "<<linecount;
			exit(1);
		}
				

		if(st.pop() != str){
			cout<<"Tag missing Error at line "<<linecount;
			exit(1);
		}


	}

	else if(isEmptyTag(str)){

	}

	else{
		cout<<"Invalid tag Error at line "<<linecount;
		exit(1);
	}

}

		


	







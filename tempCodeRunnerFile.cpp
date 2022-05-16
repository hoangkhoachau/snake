#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(void)
{
     string data;           // file contains an undermined number of integer values
     ifstream fin;     // declare stream variable name

     fin.open("test.txt",ios::in);    // open file   
     fin >> data;        // get first number from the file (priming the input statement)
                              // You must attempt to read info prior to an eof( ) test.
     while (!fin.eof( ))      //if not at end of file, continue reading numbers
     {
          cout<<data<<endl;    //print numbers to screen
          fin >> data;               //get next number from file
     }
     fin.close( );       //close file
     return 0;
}
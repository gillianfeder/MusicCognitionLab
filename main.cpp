/*
 * main.cpp
 *
 * Music Cognition Lab
 * 
 * Purpose: 
 * by Gillian Feder, February 2022
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector> 


#include "SequenceGenerator.h"
using namespace std;

void makeAndPrintSequence(vector <float> arrayOfJitRanges, string varied, float inductionLen, ostream &output);

template <typename streamtype>
void open_or_quit(streamtype &stream, string fileName);

int main()
{

    vector <float> arrayOfJitRanges1;
    //arrayOfJitRanges.push_back(5.0);      //fill according to article, as percentages (whole nums)
    //arrayOfJitRanges.push_back(10.0);      //fill according to article, as percentages (whole nums)
    arrayOfJitRanges1.push_back(10.0);      //fill according to article, as percentages (whole nums)
    //arrayOfJitRanges.push_back(37.5);      //fill according to article, as percentages (whole nums)
    arrayOfJitRanges1.push_back(25.0);      //fill according to article, as percentages (whole nums)
    
    ofstream outputFile;
    open_or_quit(outputFile, "output.txt");

    
    //makeAndPrintSequence(arrayOfJitRanges1, "Varied", 5, outputFile); //Induction of 5, Varied
    //makeAndPrintSequence(arrayOfJitRanges1, "Varied", 0, outputFile); //No Induction, Varied
    makeAndPrintSequence(arrayOfJitRanges1, "Fixed", 8, outputFile); //Induction of 5, Fixed
    makeAndPrintSequence(arrayOfJitRanges1, "Fixed", 0, outputFile); //No Induction, Fixed

    outputFile.close();
    
    return 0;
}

void makeAndPrintSequence(vector <float> arrayOfJitRanges, string varied, float inductionLen, ostream &output)
{
    for (int i = 0; i < (int)arrayOfJitRanges.size(); i++) //Induction of 5, Fixed
    {
        float inductionLength = inductionLen;
        SequenceGenerator next(arrayOfJitRanges[i], inductionLength);
        next.buildMet1();

        if(varied == "Varied"){
            next.buildMet2Varied();
            next.printToOutputFile(output, varied, arrayOfJitRanges[i], inductionLen, i+1);

        }
        else {
            
            next.buildMet2Fixed(); //jitter exactly the jit range every time
            next.printToOutputFile(output, varied, arrayOfJitRanges[i], inductionLen, i+1);
        }
        next.mergeMetronomes();

        string vec = next.printVector();
        cout << "Jitter Range: " << arrayOfJitRanges[i] << "%, " << varied << ", "<< "Induction Length: " << inductionLength 
        << "\n" << vec << endl;
        cout<<endl;
    }
}

template <typename streamtype>
void open_or_quit(streamtype &stream, string fileName)
{
    stream.open(fileName);
    if (! stream.is_open())
    {
        cerr << fileName << " cannot be opened.";
        exit(EXIT_FAILURE);
    }
}
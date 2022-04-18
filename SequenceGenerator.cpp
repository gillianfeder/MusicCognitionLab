/* 
 * SequenceGenerator.cpp
 * 
 * Music Cognition Lab
 * by Gillian Feder, February 2022
 * 
 * Purpose:
 * 
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include "SequenceGenerator.h"
using namespace std;

SequenceGenerator::SequenceGenerator()
{
    jitRange = 0;
    InductionLength = 0;
}

SequenceGenerator::SequenceGenerator(float jitterRange, float induction)
{
    jitRange = jitterRange;
    InductionLength = induction;
}

SequenceGenerator::~SequenceGenerator(){}

//Builds the vector of new notes of regular rhythm 
void SequenceGenerator:: buildMet1()
{
    for (int i = 0; i < InductionLength; i++)
    {
        Note newNote;
        newNote.representation = '|';
        newNote.distFromMidpoint = 0;
        newNote.distFromStart = MET_1_REGULARITY*i;
        newNote.percentJitter = 0;
        meter1.push_back(newNote);
    }
    for(int i = 0; i <= VECTOR_LENGTH; i++)
    {
        Note newNote;
        newNote.representation = '|';
        newNote.distFromMidpoint = 0;
        newNote.distFromStart = (MET_1_REGULARITY*i)+(InductionLength*MET_1_REGULARITY);
        newNote.percentJitter = 0;
        meter1.push_back(newNote);
    }
}

//builds a vector or notes within a certain jitter range 
void SequenceGenerator:: buildMet2Varied()                        
{
    //set seed time to 0 every time the program is run
    srand(time(0));
    
    for (int i = 0; i < VECTOR_LENGTH; i++)
    {                       //rand returns an int: how to do make it into a float so i can work with decimals (percentage as numbers??)
        int randInJitRange = rand()%(int)jitRange + 1; //generates a random  number between 0 and jitRange
        //float randInJitRange = (float)randInJitRangeInt;
        if (randInJitRange%2 != 0) { //if even, add it (delay), if odd make it come early by being negative
            randInJitRange *= -1;
        }
        float randInJitRangeDECIMAL = (randInJitRange/100.0)*MIDPOINT; //converting to <1 second 

        Note newNote;
        newNote.representation = '!';
        newNote.distFromMidpoint = randInJitRangeDECIMAL;
        newNote.percentJitter = randInJitRange;
        newNote.distFromStart = (MET_1_REGULARITY*i)+(MIDPOINT+randInJitRangeDECIMAL)+(InductionLength*MET_1_REGULARITY);
        meter2.push_back(newNote);
    }
    
}

//bbuilds a vector of notes at a certain constant distance off center from where they should go
void SequenceGenerator:: buildMet2Fixed()
{
    //set seed time to 0 every time the program is run
    srand(time(0));
    
    for (int i = 0; i < VECTOR_LENGTH; i++)
    {    
        int staticJitter = jitRange;    
        int oddOrEven = rand()%2; //determines whether delay or early onset tone
         
        if (oddOrEven%2 != 0) { //if even, add it (delay), if odd make it come early by being negative
            staticJitter *= -1;
        }
        float staticJitDecimal = (staticJitter/100.0)*MIDPOINT; //converting to <1 second 
        Note newNote;
        newNote.representation = '!';
        newNote.distFromMidpoint = staticJitDecimal;
        newNote.percentJitter = staticJitter;
        newNote.distFromStart = (MET_1_REGULARITY*i)+(MIDPOINT+staticJitDecimal)+(InductionLength*MET_1_REGULARITY);
        meter2.push_back(newNote);
    }
    
}

//combines the first and second metronomes into one sequence, always ends with metronome 1
void SequenceGenerator:: mergeMetronomes(){
    for (int i = 0; i < InductionLength; i++)
    {
        completeSequence.push_back(meter1[i]);
    }
    for (int i = 0 ; i < VECTOR_LENGTH; i++)
    {
        completeSequence.push_back(meter1[i+InductionLength]);
        completeSequence.push_back(meter2[i]);
    }
    completeSequence.push_back(meter1.back());
}

//transforms the sequence vector to a string with distinctive parameters included
string SequenceGenerator::printVector(){
    string sequence = "Metronome 1 Regularity: ";
    sequence += to_string(MET_1_REGULARITY);
    sequence += "\n";
    sequence+="Sequence: {";
    for(Note m: completeSequence){
        string k  = to_string(m.distFromStart);
        sequence += k;
        sequence += "\n ";
    }
    sequence[sequence.length()-2]= '}';
    return sequence;
}

//prints the second metronome statistics and specifications to output.txt
void SequenceGenerator::printToOutputFile(ostream &output, string varied, int jitMax, float inductionLen, int sequenceNum)
{
    output << "Metronome 2 Jitter Report: " << endl;
    output << "Sequence Number: " << sequenceNum << endl;
    output << "Jitter Max = "<< jitMax << "%, " << varied << ", "<< "Induction Length: " << inductionLen << endl;
    for (int i = 0; i < VECTOR_LENGTH; i++)
    {
        output << "Node " << i << ": Percent Jitter = ";
        output << meter2[i].percentJitter;
        output << " Distance from Midpoint = ";
        output << " " << meter2[i].distFromMidpoint << endl;
    }
}

//from vector to string --CURRENTLY UNUSED
string SequenceGenerator:: toString(){
    string total = "";
    int lastSpot = 0;
    for (int i = 0; i < SEQUENCE_LENGTH; i++)
    {
        total += meter1[i].representation; //concat the meter 1 
        lastSpot = total.length()-1; //update last index of string
        for(int k = 0; k < meter2[i].distFromStart-lastSpot; k++){ //add number of spaces that occur prior to meter2[i]-the current length of the string
            total += " ";
        }
        
        total += meter2[i].representation; //add meter2
        lastSpot = total.length()-1; //update last index of string
        for (int j = 0; j < meter1[i].distFromStart-lastSpot; j++) { //prep for adding next note in meter1
            total += " ";
        }
    }
    return total;
}

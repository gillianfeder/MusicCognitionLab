/* 
 * SequenceGenerator.h
 * 
 * Music Cognition Lab 
 * by Gillian Feder, February 2022
 * 
 * Interface of the SequenceGenerator class that includes the constructors, 
 * functions, and private data variable completeSequence, a vector of Notes.
 * 
 */
 
 #ifndef SEQUENCE_GENERATOR_H
 #define SEQUENCE_GENERATOR_H
 
 #include <iostream>
 #include <vector>
 #include <fstream>

 class SequenceGenerator {
 public:
     const int SEQUENCE_LENGTH = 50;   //if want to change anything, just change sequence length and/or MET_1_REGULARITY
     const float VECTOR_LENGTH = SEQUENCE_LENGTH/2;
     const float MET_1_REGULARITY = 0.5;
     const float MIDPOINT = MET_1_REGULARITY/2;
     
     //default constructor 
     SequenceGenerator();
     
     //constructor to take in a range (percentage) of jitter for meter two
     SequenceGenerator(float jitterRange, float induction);
     ~SequenceGenerator();
     
     void buildMet1();
     void buildMet2Varied();
     void buildMet2Fixed();
     void mergeMetronomes();
     std::string toString();
     std::string printVector();
     void printToOutputFile(std::ostream &output, std::string varied, int jitMax, float inductionLen, int sequenceNum);

 private:
    struct Note {
        char representation;
        float distFromMidpoint;
        float distFromStart; //or dist from prev? fixed in toString
        int percentJitter;
    };
    float jitRange;
    std::vector <Note> meter1;
    std::vector <Note> meter2;
    std::vector <Note> completeSequence;
    float InductionLength; 
};
 #endif
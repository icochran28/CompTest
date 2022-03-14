// Isabelle Cochran and Emily Richardson
// COMP 3500, Introduction to Operating Systems Homework 1
// IsabelleCochranHW1.cpp
// We Used the PowerPoint lecture slides and class textbook for help writing the parent and child messages
// We used stack overflow for help on how to store the data in a list
// We used help from stack overflow for help on how to implement a sort method
// g++ IsabelleCochranHW1.cpp

#include <stdio.h>
#include <unistd.h>
#include<ctype.h>
#include<iostream>
using namespace std;
#define NUM_LETTERS 26
#include<vector>
#include<fstream>



 struct list{
      int procid;
      int lettercount;
      int linenum;
   } ;

// create list of values
   vector<list> values;


 //creation of compare method

 bool compareList(list l1, list l2)  {
      return(l1.lettercount < l2.lettercount);
   }


int main() {

   ifstream infile;
   ofstream outfile;
   infile.open ("file.txt");
   outfile.open("outfile.txt");
   int total = 0;

   //declaration of variables

   int linenum;
   int max;
   int maxInd;
   string line;
   char c;

   while(getline(infile, line)){

      linenum++;
      pid_t pid;

      /* fork a child process */
      pid = fork();

      if (pid <0) { /* error */
         fprintf(stderr, "Fork Failed");
         return 1;

      }


      else if (pid ==0) { /* parent/child process, child created */

      execlp("/bin/ls","ls",NULL);

         for(int i = 0; i < line.size(); i++) {
            if('A' <= c && c <= 'Z'|| 'a' <= c && c <= 'z') {
               c++;
            }

         }


   }

   else{
     /* parent waiting on child to complete */
      wait(NULL);
      printf("Child Complete");

   }


   int count = 0;
   for(int i = 0; i < line.length(); i++) {
      if(isalpha(line[i])) {
         total++;
         count++;
      }

   }

      if(count > max) {
         max = count;
         maxInd = linenum;
      }

      list list1;
      list1.lettercount = count;
      list1.procid = getpid();
      list1.linenum = linenum;
      values.push_back(list1);



   }

   sort(values.begin(), values.end(), compareList);



   for(int i = 0; i < values.size(); i++) {
      outfile << "Process ID: " << values[i].procid << endl;
      outfile << "Line Number: " << values[i].linenum << endl;
      outfile << "Letter Count: " << values[i].lettercount << endl;
      outfile << "\n" << endl;

   }


      outfile << "Character Total: " << line << total;


   //organize data and print out to a new file
   return 0;

}

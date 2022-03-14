// Isabelle Cochran and Emily Richardson
// Introduction to Operating Systems Homework 1 Part 2
// IsabelleCochranHW1pt2.cpp
// We Used the PowerPoint lecture slides from class and the class textbook for help writing the threads
// I used stack overflow for help on how to store the data in a list
// I used help from stack overflow for help on how to implement a sort method
// g++ IsabelleCochranHW1pt2.cpp


#include <stdio.h>
#include <unistd.h>
#include<ctype.h>
#include<iostream>
using namespace std;
#define NUM_LETTERS 26
#include<vector>
#include<fstream>


struct list{
      pthread_t procid;
      int lettercount;
      int linenum;
   } ;

   vector<list> values;

   int linenum = 0;
   int total = 0;

bool compareList(list l1, list l2)  {

    return(l1.lettercount < l2.lettercount);
 }

void*letter_count(void*line){
        linenum++;

        string l = *static_cast<string*>(line);


        int count = 0;
        for(int i = 0; i < l.size(); i++) {
            if(isalpha(l[i])) {
                total++;
                count++;
            }
        }

        list list1;
        list1.lettercount = count;
        list1.procid = pthread_self();
        list1.linenum = linenum;
        values.push_back(list1);

    pthread_exit(0);

}

int main() {

    string line;
    ifstream infile;
    ofstream outfile;
    infile.open ("file.txt");
    outfile.open("outfile2.txt");


    while(getline(infile, line)){

        linenum++;
        int count = 0;

        /* the thread identifier */
        pthread_t tid;

        /* set of thread attributes */
        pthread_attr_t attr;

        /* set the default attributes of the attribute */
        pthread_attr_init(&attr);

        /* create the thread */
        pthread_create(&tid, &attr, &letter_count, &line);

        /* wait for the thread to exit */
        pthread_join(tid,NULL);

    }

    //sorts the list
    sort(values.begin(), values.end(), compareList);


    for(int i = 0; i < values.size(); i++) {
        outfile << "Line Number: " << values[i].linenum << endl;
        outfile << "Letter Count: " << values[i].lettercount << endl;
        outfile << "\n" << endl;
    }


    outfile << "Character Total: " << line << total;
    return 0;


}

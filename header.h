#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
using namespace std;

bool readFile(string filename, int LF1[17], int LF2[17], int &exp1, int &exp2, int &t1, int &t2, int &E);
int gatherForce(int LF1[17], int LF2[17]);
string determineRightTarget(string target);
string decodeTarget(string message, int exp1, int exp2);
void manageLogistics(int LF1, int LF2, int exp1, int exp2, int &t1, int &t2, int e);
int planAttack(int LF1, int LF2, int exp1, int exp2, int t1, int t2, int battleField[10][10]);
int resupply(int shortfall, int supply[5][5]);

#endif

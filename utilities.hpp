#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <map>
using namespace std;

class Course {
public:
    string name;
    int key;
    int credits;
    vector<int> prereqs; //Courses that this course need
    vector<int> unlocks; //Courses that this course unlock
    Course (string name, int credits, int key): name(name), credits(credits), key(key) {}
    void setPrereq(int prereq);
    void setUnlock(int unlock);
    int getInDegree();
};

class Curricula {
public:
    int periods;
    int minLoad;
    int maxLoad;
    int minCourses;
    int maxCourses;
    vector<Course *> courses;
    map<string, int> courseKeys;
    vector<vector<int> > coursesByPeriod;
    Curricula(vector<int> params);
    void setCourses(vector<string> names, vector<int> credits);
    void setPrereqsAndUnlocks(vector<pair<string, string> > pre);
    vector<vector<int> > topologicalSort(); //Kinda Greedy algorithm
};

Curricula * inputHandler(string filename);

#endif
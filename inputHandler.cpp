#include "utilities.hpp"

void Course::setPrereq(int prereq) {
    prereqs.push_back(prereq);
}

void Course::setUnlock(int unlock) {
    unlocks.push_back(unlock);
}

Curricula::Curricula(vector<int> params) {
    periods = params[0];
    minLoad = params[1];
    maxLoad = params[2];
    minCourses = params[3];
    maxCourses = params[4];
}

void Curricula::setCourses(vector<string> names, vector<int> credits) {
    courses.assign(names.size(), NULL);
    for (int i = 0; i < names.size(); i++) {
        cout << names[i] << endl;
        courses[i] = new Course(names[i], credits[i], i);
        courseKeys[names[i]] = i;
    }
}

void Curricula::setPrereqsAndUnlocks(vector<pair<string, string> > pre) {
    for (int i = 0; i < pre.size(); i++) {
        //cout << ":)" << pre[i].first << " " << pre[i].second << endl;
        int key1 = courseKeys[pre[i].first];
        int key2 = courseKeys[pre[i].second];
        courses[key1]->setPrereq(key2);
        courses[key2]->setUnlock(key1);
    }
}

Curricula * inputHandler(string filename) {
    ifstream file(filename);
    string line;
    vector<int> params(5);
    vector<string> courses;
    vector<int> credits;
    vector<pair<string, string> > pre;
    if (file) {
        //Parameters
        string chParams[] = {"p", "a", "b", "c", "d"};
        for (int i = 0; i < params.size(); i++) {
            regex rgx(chParams[i]+" ?= ?(\\d+) ?;");
            std::smatch match;
            getline(file, line);
            while (!regex_search(line, match, rgx)) {
                getline(file, line);
            }
            params[i] = stoi(match[1]);
        }
        
        //Courses
        regex rgx_courses("(\\w+) ?[,}]");
        std::smatch match_courses;
        getline(file, line);
        while (!regex_search(line, match_courses, rgx_courses)) {
            getline(file, line);
        }
        while (regex_search(line, match_courses, rgx_courses)) {
            courses.push_back(match_courses[1]);
            getline(file, line);
        }

        //Credits
        regex rgx_credits("(\\d+) ?,?");
        std::smatch match_credits;
        getline(file, line);
        while (!regex_search(line, match_credits, rgx_credits)) {
            getline(file, line);
        }
        while (regex_search(line, match_credits, rgx_credits)) {
            credits.push_back(stoi(match_credits[1]));
            getline(file, line);
        }

        cout << credits.size() << " " << courses.size() << endl;

        //Pre-requirements
        regex rgx_pre("< ?(\\w+) ?, ?(\\w+) ?> ?,");
        std::smatch match_pre;
        getline(file, line);
        while (!regex_search(line, match_pre, rgx_pre)) {
            getline(file, line);
        }
        while (regex_search(line, match_pre, rgx_pre)) {
            pre.push_back(pair<string, string>(match_pre[1], match_pre[2]));
            getline(file, line);
        }

        //Checking

        /*for (int i = 0; i < params.size(); i++) {
            cout << params[i] << endl;
        }

        for (int i = 0; i < courses.size(); i++) {
            cout << courses[i] << "-" << credits[i] <<  endl;
        }

        for (int i = 0; i < pre.size(); i++) {
            cout << pre[i].first << "-" << pre[i].second << endl;
        }*/

        //Setting the Curricula
        Curricula * curricula = new Curricula(params);
        curricula->setCourses(courses, credits);
        curricula->setPrereqsAndUnlocks(pre);
        file.close();
        return curricula;
    }

    file.close();
    return NULL;
}

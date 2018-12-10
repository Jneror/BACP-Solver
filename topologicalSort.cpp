#include "utilities.hpp"

int Course::getInDegree() {
    return prereqs.size();
}

vector<vector <int>> Curricula::topologicalSort() {
    vector<vector <int> > topologicalCourses;
    //Get all in degrees
    vector<int> inDegrees(courses.size());
    for (int i = 0; i < inDegrees.size(); i++) {
        inDegrees[i] = courses[i]->getInDegree();
    }

    int assignedCourses = 0;
    while (assignedCourses < inDegrees.size()) {
        cout << assignedCourses << " " << inDegrees.size() << endl;
        //Check if there are courses with 0 in degrees
        vector<int> currentPeriod;
        for (int i = 0; i < inDegrees.size(); i++) {
            if (inDegrees[i] == 0) {
                currentPeriod.push_back(i);
                inDegrees[i] = -1; //This course is already handled
                assignedCourses++;
                cout << "zero " <<  i << endl;
            }
        }

        for (int i = 0; i < currentPeriod.size(); i++) {
            vector<int> currUnlocks = courses[currentPeriod[i]]->unlocks;
            for (int j = 0; j < currUnlocks.size(); j++) {
                int key = currUnlocks[j];
                inDegrees[key]--;
            }
        }
        
        topologicalCourses.push_back(currentPeriod);
        cout << endl;
    }
    return topologicalCourses;
}
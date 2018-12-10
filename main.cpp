#include "utilities.hpp"
using namespace std;

int main() {
    Curricula * curricula = inputHandler("bacp8.txt");
    vector<vector<int> > tc = curricula->topologicalSort();
    for (int i = 0; i < tc.size(); i++) {
        for (int j = 0; j < tc[i].size(); j++) {
            cout << tc[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
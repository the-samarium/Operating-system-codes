#include <iostream>
#include <vector>
using namespace std;

// FCFS Disk Scheduling Algorithm
int FCFS(int start, const vector<int> &req) {
    int seek = 0;
    for (int i = 0; i < req.size(); i++) {
        int diff = req[i] - start;
        if (diff < 0) diff = diff * -1;  // manually take positive difference
        seek += diff;
        start = req[i]; // move head to current request
    }
    return seek;
}

int main() {
    vector<int> req = {82, 170, 43, 140, 24, 16, 190};
    int start = 50;
    
    int seek = FCFS(start, req);
    
    cout << "Sequence of requests: ";
    for (int r : req) cout << r << " ";
    
    cout << "\nInitial head position: " << start;
    cout << "\nTotal seek distance: " << seek << " tracks\n";
    
    return 0;
}

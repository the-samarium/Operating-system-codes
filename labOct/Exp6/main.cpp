#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
using namespace std;

void FCFS(vector<int> req, int head) {
    int seek = 0;
    cout << "\n--- FCFS Disk Scheduling ---\n";
    cout << "Sequence: " << head;
    for (int r : req) {
        seek += abs(r - head);
        head = r;
        cout << " -> " << r;
    }
    cout << "\nTotal Seek Time: " << seek;
    cout << "\nAverage Seek Time: " << (float)seek / req.size() << "\n";
}

void SSTF(vector<int> req, int head) {
    int seek = 0;
    vector<int> visited(req.size(), 0);
    cout << "\n--- SSTF Disk Scheduling ---\n";
    cout << "Sequence: " << head;
    for (int i = 0; i < req.size(); i++) {
        int minDist = INT_MAX, index = -1;
        for (int j = 0; j < req.size(); j++) {
            if (!visited[j]) {
                int dist = abs(req[j] - head);
                if (dist < minDist) {
                    minDist = dist;
                    index = j;
                }
            }
        }
        visited[index] = 1;
        seek += minDist;
        head = req[index];
        cout << " -> " << req[index];
    }
    cout << "\nTotal Seek Time: " << seek;
    cout << "\nAverage Seek Time: " << (float)seek / req.size() << "\n";
}

void SCAN(vector<int> req, int head, int disk_size, string direction) {
    int seek = 0;
    req.push_back(head);
    sort(req.begin(), req.end());
    int pos = find(req.begin(), req.end(), head) - req.begin();
    cout << "\n--- SCAN Disk Scheduling (" << direction << ") ---\n";
    cout << "Sequence: " << head;

    if (direction == "left") {
        for (int i = pos; i > 0; i--) {
            seek += abs(req[i] - req[i - 1]);
            cout << " -> " << req[i - 1];
        }
        seek += req[0]; // move to start
        cout << " -> 0";
        if (pos != req.size() - 1) {
            seek += req.back();
            cout << " -> " << req.back();
        }
    } else {
        for (int i = pos; i < req.size() - 1; i++) {
            seek += abs(req[i + 1] - req[i]);
            cout << " -> " << req[i + 1];
        }
        seek += (disk_size - 1 - req.back());
        cout << " -> " << disk_size - 1;
        if (pos != 0) {
            seek += (disk_size - 1 - req[0]);
            cout << " -> " << req[0];
        }
    }

    cout << "\nTotal Seek Time: " << seek;
    cout << "\nAverage Seek Time: " << (float)seek / (req.size() - 1) << "\n";
}

void CSCAN(vector<int> req, int head, int disk_size) {
    int seek = 0;
    req.push_back(head);
    sort(req.begin(), req.end());
    int pos = find(req.begin(), req.end(), head) - req.begin();
    cout << "\n--- C-SCAN Disk Scheduling ---\n";
    cout << "Sequence: " << head;

    for (int i = pos; i < req.size() - 1; i++) {
        seek += abs(req[i + 1] - req[i]);
        cout << " -> " << req[i + 1];
    }
    // Jump from end to start
    seek += (disk_size - 1 - req.back());
    seek += (disk_size - 1);
    cout << " -> 0";
    for (int i = 0; i < pos; i++) {
        seek += abs(req[i + 1] - req[i]);
        cout << " -> " << req[i + 1];
    }

    cout << "\nTotal Seek Time: " << seek;
    cout << "\nAverage Seek Time: " << (float)seek / (req.size() - 1) << "\n";
}

int main() {
    int n, head, disk_size;
    cout << "Enter number of requests: ";
    cin >> n;
    vector<int> req(n);
    cout << "Enter request sequence: ";
    for (int i = 0; i < n; i++) cin >> req[i];
    cout << "Enter initial head position: ";
    cin >> head;
    cout << "Enter disk size: ";
    cin >> disk_size;

    FCFS(req, head);
    SSTF(req, head);
    SCAN(req, head, disk_size, "right");
    CSCAN(req, head, disk_size);

    return 0;
}

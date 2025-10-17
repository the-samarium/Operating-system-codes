#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
struct Process {
    int pid, at, bt, ct, tat, wt, priority;
    int remaining_bt;
};

void disp(vector<Process> &p, int n) {
   

 float avgWT = 0, avgTAT = 0;
    cout << "\nPID\tAT\tBT\tPri\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" 
             << p[i].priority << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }
    cout << "\nAverage WT = " << (avgWT / n);
    cout << "\nAverage TAT = " << (avgTAT / n) << "\n";
}


void fcfs(vector<Process> p, int n) {
    cout << "fcfs\n";
    sort(p.begin(), p.end(), [](Process a, Process b){ return a.at < b.at; });

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    disp(p, n);
}

void sjf(vector<Process> p, int n) {
    cout << "sjf\n";
    int completed = 0, time = 0;
    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1, minBT = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = true;
        completed++;
    }
    disp(p, n);
}

void prioritySch(vector<Process> p, int n) {
    cout << "Priority Scheduling (Non-Preemptive) \n";
    int completed = 0, time = 0;
    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1, bestPriority = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].priority < bestPriority) {
                bestPriority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = true;
        completed++;
    }
    disp(p, n);
}


void rr(vector<Process> p, int n, int tq) {
    cout << "Round Robin (RR) \n";
    int time = 0, completed = 0;
    queue<int> q;
    vector<bool> inQueue(n, false);

    for (int i = 0; i < n; i++) p[i].remaining_bt = p[i].bt;
    sort(p.begin(), p.end(), [](Process a, Process b){ return a.at < b.at; });

    q.push(0);
    inQueue[0] = true;
    time = p[0].at;

    while (!q.empty()) {
        int idx = q.front(); q.pop();
        inQueue[idx] = false;

        if (p[idx].remaining_bt > tq) {
            time += tq;
            p[idx].remaining_bt -= tq;
        } else {
            time += p[idx].remaining_bt;
            p[idx].remaining_bt = 0;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining_bt > 0 && !inQueue[i]) {
                q.push(i);
                inQueue[i] = true;
            }
        }
        if (p[idx].remaining_bt > 0) {
            q.push(idx);
            inQueue[idx] = true;
        }
    }
    disp(p, n);
}

int main() {
    int n;
    cout << "Enter no. of prces: ";
    cin >> n;
    vector<Process> prces(n);

    for (int i = 0; i < n; i++) {
        prces[i].pid = i+1;
        cout << "\nProcess " << i+1 << ":\n";
        cout << "Arrival Time: "; cin >> prces[i].at;
        cout << "Burst Time: ";   cin >> prces[i].bt;
        cout << "Priority (lower = higher priority): "; cin >> prces[i].priority;
    }

    int choice, tq;
    do {
        cout << "\n CPU Scheduling Menu \n";
        cout << "1. First Come First Serve (fcfs)\n";
        cout << "2. Shortest Job First (sjf)\n";
        cout << "3. Priority Scheduling\n";
        cout << "4. Round Robin (RR)\n";
        cout << "5. Exit\n";
        cout << "Enter : ";
        cin >> choice;

        switch(choice) {
            case 1: fcfs(prces, n); break;
            case 2: sjf(prces, n); break;
            case 3: prioritySch(prces, n); break;
            case 4: 
                cout << "Enter Time Quantum: ";
                cin >> tq;
                rr(prces, n, tq);
                break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 5);

    return 0;
}



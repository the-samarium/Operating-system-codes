#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// FIFO Page Replacement
void FIFO(vector<int> pages, int framesCount) {
    queue<int> q;
    vector<int> frames;
    int pageFaults = 0;

    cout << "\n--- FIFO Page Replacement ---\n";
    for (int page : pages) {
        auto it = find(frames.begin(), frames.end(), page);

        if (it == frames.end()) { // page fault
            if (frames.size() < framesCount) {
                frames.push_back(page);
                q.push(page);
            } else {
                int old = q.front();
                q.pop();
                q.push(page);
                replace(frames.begin(), frames.end(), old, page);
            }
            pageFaults++;
        }
    }

    int pageHits = pages.size() - pageFaults;
    cout << "\nTotal Page Faults (FIFO): " << pageFaults;
    cout << "\nTotal Page Hits (FIFO): " << pageHits << "\n";
}

// LRU Page Replacement
void LRU(vector<int> pages, int framesCount) {
    vector<int> frames;
    int pageFaults = 0;

    cout << "\n--- LRU Page Replacement ---\n";
    for (int page : pages) {
        auto it = find(frames.begin(), frames.end(), page);

        if (it == frames.end()) { // Page not found
            if (frames.size() < framesCount)
                frames.push_back(page);
            else
                frames.erase(frames.begin()), frames.push_back(page);
            pageFaults++;
        } else { // Page found → move to most recent position
            frames.erase(it);
            frames.push_back(page);
        }
    }

    int pageHits = pages.size() - pageFaults;
    cout << "\nTotal Page Faults (LRU): " << pageFaults;
    cout << "\nTotal Page Hits (LRU): " << pageHits << "\n";
}

int main() {
    int n, framesCount;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter reference string: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> framesCount;

    FIFO(pages, framesCount);
    LRU(pages, framesCount);

    return 0;
}

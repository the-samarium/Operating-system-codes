#include <iostream>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    int Alloc[n][m], Max[n][m], Need[n][m], Avail[m];
    int Finish[n] = {0}, SafeSeq[n];

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> Alloc[i][j];

    cout << "Enter Maximum Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> Max[i][j];

    cout << "Enter Available Resources:\n";
    for (int j = 0; j < m; j++)
        cin >> Avail[j];

    // Step 3: Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Alloc[i][j];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (Finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++)
                    if (Need[i][j] > Avail[j])
                        break;

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        Avail[k] += Alloc[i][k];
                    SafeSeq[count++] = i;
                    Finish[i] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is in an UNSAFE STATE.\n";
            return 0;
        }
    }

    cout << "\nSystem is in a SAFE STATE.\nSafe sequence: ";
    for (int i = 0; i < n; i++)
        cout << "P" << SafeSeq[i] << " ";
    cout << endl;

    return 0;
}

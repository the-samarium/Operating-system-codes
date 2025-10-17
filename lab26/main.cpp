// sept 19 friday os lab
// implementing best fit, first fit and worst fit algos on gives spaces and processes array
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int data, Node *next)
    {
        this->data = data;
        this->next = next;
    }
};

void FFbyll()
{
    int x = 0;
    Node *dummyNode = new Node(0, nullptr);
    Node *curr = dummyNode;

    cout << "Enter the number of blocks:-";
    cin >> x;

    for (int i = 0; i < x; i++)
    {
        int blockSize;
        cout << "Enter size of block " << i + 1 << ": ";
        cin >> blockSize; // Read the size of the new block
        Node *newNode = new Node(blockSize, nullptr);
        curr->next = newNode;
        curr = curr->next;

    }
    // After the loop, the actual start of your list is:
    Node* head = dummyNode->next;
    delete dummyNode;

}

void bestfit(vector<int> s, vector<int> p, int n, int m)
{
    // bestfit finds best spot for process acc to size. has to traverse whole array
    int uti = 0;
    int total = 0;

    int allocation[m];
    int allocated[n];
    for (int i = 0; i < m; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        total += s[i];
        allocated[i] = 0;
    }

    vector<int> cpy = s;

    for (int i = 0; i < m; i++)
    {
        int mini = INT_MAX;
        int process = p[i];
        int index = -1;
        for (int j = 0; j < n; j++)
        {
            if (s[j] >= process)
            {
                if (s[j] <= mini)
                {
                    mini = s[j];
                    index = j;
                }
            }
        }
        if (index != -1)
        {
            uti += process;
            s[index] -= process;
            allocation[i] = index; // add block no allocated to process i
            allocated[index] = 1;  // mark block as used
        }
    }

    // Print
    for (int i = 0; i < m; i++)
    {
        if (allocation[i] == -1)
            cout << "P" << i << " of size " << p[i] << " -> Not allocated\n";
        else
            cout << "P" << i << " of size " << p[i]
                 << " -> allocated to block " << allocation[i] + 1
                 << " of size " << cpy[allocation[i]] << "\n";
    }

    double perc = (double)uti / total;
    cout << "Memory utilization Best fit: " << perc * 100 << " %" << endl;
    cout << endl;
}

void firstfit(vector<int> s, vector<int> p, int n, int m)
{
    // firstfit finds first spot for process acc to size. does not has to traverse whole array
    int uti = 0;
    int total = 0;
    int allocation[m];
    int allocated[n];
    for (int i = 0; i < m; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        total += s[i];
        allocated[i] = 0;
    }

    vector<int> cpy = s;

    for (int i = 0; i < m; i++)
    {
        int process = p[i]; // store the process to which sppot is to be found
        for (int j = 0; j < n; j++)
        {
            if (allocated[j] == 0 && s[j] >= process)
            {
                uti += process;    // add up to utilized memory
                s[j] -= process;   // change the actual size after occupied by the process
                allocation[i] = j; // add block no allocated to process i
                allocated[j] = 1;  // mark block as used
                break;
            }
        }
    }

    // Print allocation
    for (int i = 0; i < m; i++)
    {
        if (allocation[i] == -1)
            cout << "P" << i << " of size " << p[i] << " -> Not allocated\n";
        else
            cout << "P" << i << " of size " << p[i]
                 << " -> allocated to block " << allocation[i] + 1
                 << " of size " << cpy[allocation[i]] << "\n";
    }

    double perc = (double)uti / total;
    cout << "Memory utilization First fit: " << perc * 100 << " %" << endl;
    cout << endl;
}

void worstfit(vector<int> s, vector<int> p, int n, int m)
{
    // worstfit finds largets spot for process acc to order. means first process gets largets spot acc to size of the spot
    int uti = 0;
    int total = 0;

    int allocation[m];
    int allocated[n];
    for (int i = 0; i < m; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        total += s[i];
        allocated[i] = 0;
    }

    vector<int> cpy = s;

    for (int i = 0; i < m; i++)
    {
        int maxi = INT_MIN;
        int process = p[i];
        int index = -1;
        for (int j = 0; j < n; j++)
        {
            if (s[j] >= process)
            {
                if (s[j] >= maxi)
                {
                    maxi = s[j];
                    index = j;
                }
            }
        }
        if (index != -1)
        {
            uti += process;
            s[index] -= process;
            allocation[i] = index; // add block no allocated to process i
            allocated[index] = 1;  // mark block as used
        }
    }

    // Print allocation results
    for (int i = 0; i < m; i++)
    {
        if (allocation[i] == -1)
            cout << "P" << i << " of size " << p[i] << " -> Not allocated\n";
        else
            cout << "P" << i << " of size " << p[i]
                 << " -> allocated to block " << allocation[i] + 1
                 << " of size " << cpy[allocation[i]] << "\n";
    }

    double perc = (double)uti / total;
    cout << "Memory utilization Worst fit: " << perc * 100 << " %" << endl;
    cout << endl;
}

int main()
{
    vector<int> Siz = {100, 500, 200, 300, 600};
    vector<int> Prs = {212, 417, 112, 426};
    int n = Siz.size();
    int m = Prs.size();
    // firstfit(Siz, Prs, n, m);
    // bestfit(Siz, Prs, n, m);
    // worstfit(Siz, Prs, n, m);
    while (true)
    {
        int x = 0;
        cout << "<---Menu Driven program for Dynamic storage allocation algorithms--->\n";
        cout << "Select an alogrithm to run:\n1.Best-Fit\n2.First-Fit\n3.Worst-fit\n\n:-";
        cin >> x;
        //refered
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number (1, 2, or 3).\n";
            cin.clear();             // Clear the fail state flags
            cin.ignore(10000, '\n'); // Discard the bad input up to the newline character
            // The program should then ideally jump to the start of the loop
            // or set a flag to repeat the menu.
        }
        else
        {
            switch (x)
            {
            case 1:
                bestfit(Siz, Prs, n, m);
                break;
            case 2:
                firstfit(Siz, Prs, n, m);
                break;
            case 3:
                worstfit(Siz, Prs, n, m);
                break;
            default:
                cout << "Enter a valid input\n\n";
                break;
            }
        }
    }

    return 0;
}
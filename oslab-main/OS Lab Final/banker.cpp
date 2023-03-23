#include <bits/stdc++.h>
#define pb push_back
using namespace std;
// Milan Mundhra 20JE0564
//.cpp file run on linux

int n, m;
bool banker(vector<vector<int>> &allocation, vector<vector<int>> &need, vector<int> &available)
{
    vector<int> work;
    work = available;
    vector<bool> finish(n, false);
    vector<int> safeSequence;
    while (true)
    {
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == m)
                {
                    finish[i] = true;
                    safeSequence.push_back(i);
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    flag = 1;
                }
            }
        }
        if (!flag)
            break;
    }

    bool safe = 1;
    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            safe = 0;
            break;
        }
    }

    if (safe)
    {
        cout << "System is in safe state and following sequence satisfies safety requirements: "
             << "\n";
        for (auto x : safeSequence)
            cout << "P" << x << " ";
        cout << "\n";
    }
    else
        cout << "System is in unsafe state"
             << "\n";

    return safe;
}

int main()
{
    cout << "Enter number of process: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;
    vector<bool> finish(n, 0);
    vector<int> sum(m, 0);
    vector<vector<int>> allocation(n);
    cout << "Enter allocation for the processes: "
         << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process: " << i << "\n";
        for (int j = 0; j < m; j++)
        {
            int x;
            cin >> x;
            allocation[i].push_back(x);
            sum[j] += x;
        }
    }
    vector<vector<int>> maximum(n);
    cout << "Enter maximum claim of resources for the processes: "
         << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process: " << i << "\n";
        for (int j = 0; j < m; j++)
        {
            int x;
            cin >> x;
            maximum[i].push_back(x);
        }
    }

    vector<vector<int>> need(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i].pb(maximum[i][j] - allocation[i][j]);
        }
    }
    vector<int> totalResources(m);
    cout << "Enter the total instances of resources: ";
    for (int i = 0; i < m; i++)
        cin >> totalResources[i];

    vector<int> available(m);
    for (int i = 0; i < m; i++)
        available[i] = totalResources[i] - sum[i];

    cout << "Considering the need matrix"
         << "\n";
    if (!banker(allocation, need, available))
        return 0;

    vector<int> request(m);

    int process;
    cout << "Enter the process no for the request: ";
    cin >> process;

    cout << "Enter request of resources for the process " << process << "\n";

    bool claim_error = 0, wait = 0;

    for (int i = 0; i < m; i++)
    {

        cin >> request[i];

        if (request[i] > need[process][i])
            claim_error = 1;
        if (request[i] > available[i])
            wait = 1;
    }

    if (claim_error)
        cout << "Process :" << process << " has exceeded its maximum claim"
             << "\n";
    else if (wait)
        cout << "Process :" << process << " must wait since resources are not available"
             << "\n";
    else
    {
        for (int k = 0; k < m; k++)
        {
            available[k] -= request[k];
            allocation[process][k] += request[k];
            need[process][k] -= request[k];
        }
        bool safe = banker(allocation, need, available);
        cout << "Request for process :" << process;
        cout << (safe ? " can" : " cannot") << " be granted"
             << "\n";
    }

    return 0;
}

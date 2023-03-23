// for deadlock prevention
// Milan Mundhra 20JE0564
//.cpp file run in linux
#include <bits/stdc++.h>
using namespace std;

int n, m;
void deadlock_check(vector<vector<int>> &allocation, vector<vector<int>> &request, vector<int> &availibility, vector<bool> &finish)
{
    vector<int> process;
    vector<int> deadlock;
    while (true)
    {
        bool flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (request[i][j] > availibility[j])
                        break;
                }
                if (j == m)
                {
                    finish[i] = true;
                    process.push_back(i);
                    for (int k = 0; k < m; k++)
                    {
                        availibility[k] += allocation[i][k];
                    }
                    flag = 1;
                }
            }
        }
        if (!flag)
        {
            int i;
            for (i = 0; i < n; i++)
            {
                if (!finish[i])
                {
                    finish[i] = true;
                    deadlock.push_back(i);
                    for (int k = 0; k < m; k++)
                    {
                        availibility[k] += allocation[i][k];
                    }
                    break;
                }
            }
            if (i == n)
                break;
        }
    }

    if (deadlock.size() == 0)
    {
        cout << "No deadlock detected"
             << "\n";
        cout << "Processes executed in the following order"
             << "\n";
        for (auto x : process)
            cout << x << " ";
    }
    else
    {
        cout << "Deadlock prevented"
             << "\n";
        cout << "Following processes were aborted: ";
        for (int i = 0; i < deadlock.size(); i++)
            cout << deadlock[i] << " ";
        cout << "\n"
             << "Processes executed in the following order"
             << "\n";
        for (auto x : process)
            cout << x << " ";
    }
}

int main()
{
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;
    vector<bool> finish(n, 0);
    vector<vector<int>> allocation(n);
    cout << "Enter allocation for the processes"
         << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process P" << i << ":"
             << "\n";
        for (int j = 0; j < m; j++)
        {
            int x;
            cin >> x;
            allocation[i].push_back(x);
        }
    }

    vector<vector<int>> request(n);
    cout << "Enter requests for the processes"
         << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Process P" << i << ":"
             << "\n";
        for (int j = 0; j < m; j++)
        {
            int x;
            cin >> x;
            request[i].push_back(x);
        }
    }

    vector<int> availability(m);
    cout << "Enter current availability of resources: ";
    for (int i = 0; i < m; i++)
        cin >> availability[i];

    cout << "\n";
    deadlock_check(allocation, request, availability, finish);
    cout << "\n";

    return 0;
}

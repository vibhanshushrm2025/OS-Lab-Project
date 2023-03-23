// Milan Mundhra
// 20JE0564
//.cpp file run in linux
#include <bits/stdc++.h>
using namespace std;
int main()
{
    cout << "Enter the no of Memory Blocks: ";
    int m;
    cin >> m;
    cout << "Enter hole sizes of the Memory Blocks--\n";
    vector<int> memory(m);
    for (int i = 0; i < m; i++)
        cin >> memory[i];

    cout << "Enter the no of processes: ";
    int n;
    cin >> n;
    cout << "Enter memory occupied by each process--\n";
    vector<int> required(n);
    for (int i = 0; i < n; i++)
        cin >> required[i];

    vector<int> used(m, 0);
    vector<int> fin(n, -1);
    sort(memory.begin(), memory.end());
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (memory[j] - used[j] >= required[i])
            {
                used[j] += required[i];
                fin[i] = j;
                break;
            }
        }
    }
    cout << "\nProcess allocation is as follows--\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << " with memory ";
        if (fin[i] == -1)
            cout << required[i] << "K could not be allocated due to external Fragmentation\n";
        else
            cout << required[i] << "K is allocated to block " << fin[i] + 1 << " with memory " << memory[fin[i]] << "\n";
    }
    return 0;
}

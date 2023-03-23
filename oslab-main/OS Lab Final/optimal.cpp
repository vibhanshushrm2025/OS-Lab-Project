#include <bits/stdc++.h>
using namespace std;
// Milan Mundhra
// 20JE0564
//.cpp file run in linux
int main()
{
    cout << "Enter the number of page references: ";
    int n;
    cin >> n;
    cout << "Enter the number of page frames: ";
    int m;
    cin >> m;

    cout << "Enter the page references--\n";
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> b;
    int miss = 0, hit = 0;
    for (int i = 0; i < n; i++)
    {
        bool found = 0;
        for (int j = 0; j < b.size(); j++)
        {
            if (b[j] == a[i])
            {
                found = 1;
                hit++;
                break;
            }
        }
        if (!found)
        {
            cout << a[i] << " missed\n";
            miss++;
            if (b.size() < m)
                b.push_back(a[i]);
            else
            {
                map<int, int> mp;
                int maxi = i + 1;
                for (int j = 0; j < b.size(); j++)
                {
                    int k;
                    for (k = i + 1; k < n; k++)
                    {
                        if (b[j] == a[k])
                        {
                            mp[j] = k;
                            maxi = max(maxi, k);
                            break;
                        }
                    }
                    if (k == n)
                    {
                        mp[j] = n;
                        maxi = n;
                    }
                }
                for (int j = 0; j < b.size(); j++)
                {
                    if (mp[j] == maxi)
                    {
                        b[j] = a[i];
                        break;
                    }
                }
            }
        }
        else
            cout << a[i] << " hit\n";
    }
    cout << "Total hits = " << hit << "\n";
    cout << "Total miss = " << miss << "\n";
    cout << "Hit ratio = " << (double)hit / n * 100 << "%\n";
    cout << "Miss ratio = " << (double)miss / n * 100 << "%\n";
}

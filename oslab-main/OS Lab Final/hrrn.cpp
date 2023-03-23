// highest response ratio next
//.cpp code in c++
// Milan Mundhra
// 20JE0564
#include <bits/stdc++.h>
using namespace std;
struct process
{
    int pid;
    int at;
    int bt;
    int vis;
    double rr;
};

bool cmp(process a, process b)
{
    if (a.at == b.at)
    {
        if (a.bt == b.bt)
        {
            return a.pid < b.pid;
        }
        return a.bt > b.bt;
    }
    return a.at < b.at;
}
struct comparator
{
    bool operator()(process const &p1, process const &p2)
    {

        if (p1.rr == p2.rr)
        {
            return p1.at > p2.at;
        }
        return p1.rr < p2.rr;
    }
};
int main()
{
    int n;
    cout << "Enter number of processes" << endl;
    cin >> n;
    vector<process> p(n);
    vector<int> pid(n);
    vector<int> at(n);
    vector<int> bt(n);
    vector<int> ct(n);
    vector<int> tat(n);
    vector<int> wt(n);
    int tat_sum = 0;
    int wt_sum = 0;
    cout << "Enter processes in the format AT BT" << endl;
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i;
        p[i].vis = 0;
        cout << "process: " << i + 1 << endl;
        cin >> p[i].at >> p[i].bt;
        at[i] = p[i].at;
        bt[i] = p[i].bt;
        pid[i] = p[i].pid;
    }
    priority_queue<process, vector<process>, comparator> q;
    sort(p.begin(), p.end(), cmp);

    p[0].vis = 1;
    int t = p[0].at;
    q.push(p[0]);

    while (!q.empty())
    {
        auto x = q.top();
        q.pop();

        if (x.at <= t)
            t += x.bt;
        else
            t = x.at + x.bt;
        ct[x.pid] = t;
        p[x.pid].vis = 1;

        while (!q.empty())
            q.pop();

        for (int i = 0; i < n; i++)
        {
            if (!p[i].vis && p[i].at <= t)
            {
                p[i].rr = (t - p[i].at + p[i].bt) * 1.0 / p[i].bt;
                q.push(p[i]);
            }
        }

        if (q.empty())
        {
            for (int i = 0; i < n; i++)
            {

                if (!p[i].vis)
                {
                    p[i].rr = (t - p[i].at + p[i].bt) * 1.0 / p[i].bt;
                    q.push(p[i]);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        int id = p[i].pid;
        tat[id] = ct[id] - p[i].at;
        wt[id] = ct[id] - (p[i].at + p[i].bt);
        tat_sum += tat[id];
        wt_sum += wt[id];
    }

    cout << "PNO.\tAT\tBT\tCT\tTAT\tWT\t" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << pid[i] + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }
    cout << "Sum of TAT: " << tat_sum << endl;
    cout << "Sum of WT: " << wt_sum << endl;
    cout << "Avg TAT: " << tat_sum / double(n) << endl;
    cout << "Avg WT: " << wt_sum / double(n) << endl;
    return 0;
}

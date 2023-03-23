// multilevel feedback queue
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
    int wt;
    int ct;
    int tat;
};
int tat_sum, wt_sum;
bool cmp(process p1, process p2)
{
    if (p1.at == p2.at)
    {
        return p1.pid < p2.pid;
    }
    return p1.at < p2.at;
}
bool cmpid(process p1, process p2)
{

    return p1.pid < p2.pid;
}

vector<process> fin;
int rr(vector<process> &pro, vector<int> &bt, int tq, int st)
{
    vector<process> p;
    queue<process> ready;
    for (int i = 0; i < pro.size(); i++)
    {

        if (pro[i].bt > 0)
            p.push_back(pro[i]);
    }
    sort(p.begin(), p.end(), cmp);
    int i = 0;

    int n = p.size();

    while (i < n && p[i].at <= st)
    {

        ready.push(p[i]);
        i++;
    }

    while (!ready.empty() || i < n)
    {

        bool emp = false;
        int req = tq;
        process u;
        if (ready.empty())
        {

            emp = true;
            req = p[i].at;
        }
        else
        {
            u = ready.front();
            ready.pop();

            req = min(req, u.bt);
            u.bt -= req;
            pro[u.pid].bt -= req;
            st += req;
        }

        while (i < n && p[i].at <= st)
        {

            ready.push(p[i]);
            i++;
        }

        if (!emp && u.bt == 0)
        {
            u.ct = st;
            u.tat = u.ct - u.at;
            u.bt = bt[u.pid];
            u.wt = u.tat - u.bt;
            fin.push_back(u);
            tat_sum += u.tat;
            wt_sum += u.wt;
        }
        else if (!emp)
        {

            ready.push(u);
        }

        if (u.pid == p[n - 1].pid)
            return st;
    }
}

void fcfs(vector<process> &pro, vector<int> &bt, int st)
{
    vector<process> p;
    for (int i = 0; i < pro.size(); i++)
    {

        if (pro[i].bt > 0)
            p.push_back(pro[i]);
    }
    sort(p.begin(), p.end(), cmp);
    int n = p.size();

    int last = st;

    for (int i = 0; i < n; i++)
    {
        last = max(last, p[i].at) + p[i].bt;

        process u;
        u = p[i];
        u.bt = bt[u.pid];
        u.ct = last;
        u.tat = last - u.at;
        u.wt = last - (u.at + u.bt);
        fin.push_back(u);
        tat_sum += u.tat;
        wt_sum += u.wt;
    }
}
int main()
{
    int n;
    cout << "Enter number of processes" << endl;
    cin >> n;
    vector<process> p(n);
    vector<int> bt(n);

    cout << "Enter processes in the format AT BT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "process: " << i + 1 << endl;
        p[i].pid = i;
        cin >> p[i].at >> p[i].bt;
        bt[i] = p[i].bt;
    }

    cout << "Enter the time quantum for Q1: ";
    int tq1;
    cin >> tq1;
    sort(p.begin(), p.end(), cmp);
    int st = p[0].at;

    cout << "Enter the time quantum for Q2: ";
    int tq2;
    cin >> tq2;
    st = rr(p, bt, tq1, st);

    st = rr(p, bt, tq2, st);

    fcfs(p, bt, st);
    sort(fin.begin(), fin.end(), cmpid);

    cout << "PNO.\tAT\tBT\tCT\tTAT\tWT\t" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << fin[i].pid + 1 << "\t" << fin[i].at << "\t" << fin[i].bt << "\t" << fin[i].ct << "\t" << fin[i].tat << "\t" << fin[i].wt << endl;
    }
    cout << "Sum of TAT: " << tat_sum << endl;
    cout << "Sum of WT: " << wt_sum << endl;
    cout << "Avg TAT: " << tat_sum / double(n) << endl;
    cout << "Avg WT: " << wt_sum / double(n) << endl;
    return 0;
}

// multi-level queue
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
    int rt;
    int qno;
};
bool comp(process p1, process p2)
{
    return (p1.at < p2.at) || ((p1.at == p2.at) && (p1.pid < p2.pid));
}
bool cmpid(process p1, process p2)
{
    return p1.pid < p2.pid;
}
int main()
{
    int n;
    cout << "Enter number of processes" << endl;
    cin >> n;

    vector<process> queue1, queue2;
    cout << "Enter processes in the format AT BT QNo." << endl;
    for (int k = 0; k < n; k++)
    {
        process p;
        p.pid = k + 1;
        cin >> p.at >> p.bt >> p.qno;
        p.rt = p.bt;
        if (p.qno == 1)
        {
            queue1.push_back(p);
        }
        else if (p.qno == 2)
        {
            queue2.push_back(p);
        }
    }

    cout << "Enter the time quantum for Q1: ";
    int tq;
    cin >> tq;

    sort(queue1.begin(), queue1.end(), comp);
    sort(queue2.begin(), queue2.end(), comp);

    int curr = min(queue1[0].at, queue2[0].at);
    vector<process> p;
    queue<process> q;
    int tot_tat = 0, tot_wt = 0;
    int i = 0, j = 0;
    int s = queue1.size(), u = queue2.size();
    while (i < s && j < u)
    {
        if (queue1[i].at <= curr || queue1[i].at < queue2[j].at)
        {
            curr = max(queue1[i].at, curr);
            while (i < s && queue1[i].at <= curr)
            {
                q.push(queue1[i]);
                i++;
            }
            while (!q.empty())
            {
                process t = q.front();
                q.pop();
                int diff = min(tq, t.rt);
                t.rt -= diff;
                curr += diff;
                while (i < s && queue1[i].at <= curr)
                {
                    q.push(queue1[i]);
                    i++;
                }
                if (t.rt == 0)
                {
                    t.ct = curr;
                    t.tat = t.ct - t.at;
                    t.wt = t.tat - t.bt;
                    p.push_back(t);
                    tot_tat += t.tat;
                    tot_wt += t.wt;
                }
                else
                {
                    q.push(t);
                }
            }
        }
        else
        {
            int prev = max(curr, queue2[j].at);
            curr = max(curr, queue2[j].at) + queue2[j].rt;
            if (curr > queue1[i].at)
            {
                curr = queue1[i].at;
            }
            int interval = curr - prev;
            queue2[j].rt -= interval;
            if (queue2[j].rt == 0)
            {
                queue2[j].ct = curr;
                queue2[j].tat = queue2[j].ct - queue2[j].at;
                queue2[j].wt = queue2[j].tat - queue2[j].bt;
                tot_tat += queue2[j].tat;
                tot_wt += queue2[j].wt;
                p.push_back(queue2[j]);
                j++;
            }
        }
    }
    while (i < s)
    {
        curr = max(queue1[i].at, curr);
        while (i < s && queue1[i].at <= curr)
        {
            q.push(queue1[i]);
            i++;
        }
        while (i < s || !q.empty())
        {
            process t = q.front();
            q.pop();
            int diff = min(tq, t.rt);
            t.rt -= diff;
            curr += diff;
            while (i < s && queue1[i].at <= curr)
            {
                q.push(queue1[i]);
                i++;
            }
            if (t.rt == 0)
            {
                t.ct = curr;
                t.tat = t.ct - t.at;
                t.wt = t.tat - t.bt;
                p.push_back(t);
                tot_tat += t.tat;
                tot_wt += t.wt;
            }
            else
            {
                q.push(t);
            }
        }
    }

    while (j < u)
    {
        curr = max(curr, queue2[j].at) + queue2[j].rt;
        queue2[j].ct = curr;
        queue2[j].tat = queue2[j].ct - queue2[j].at;
        queue2[j].wt = queue2[j].tat - queue2[j].bt;
        tot_tat += queue2[j].tat;
        tot_wt += queue2[j].wt;
        p.push_back(queue2[j]);
        j++;
    }

    cout << "\nPNO.\tAT\tBT\tCT\tAT\tWT\tQNo" << endl;
    sort(p.begin(), p.end(), cmpid);

    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct
             << "\t" << p[i].tat << "\t" << p[i].wt << "\t" << p[i].qno << endl;
    }

    cout << "Sum of TAT: " << tot_tat << endl;
    cout << "Sum of WT: " << tot_wt << endl;
    cout << "Avg TAT: " << tot_tat / double(n) << endl;
    cout << "Avg WT: " << tot_wt / double(n) << endl;
    return 0;
}

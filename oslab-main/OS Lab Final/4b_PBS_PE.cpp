#include <bits/stdc++.h>
using namespace std;

struct process{
    int pid;
    int AT;
    int BT;
    int pr;
    int vis;
};

struct cmp {
    bool operator()(process const& p1, process const& p2)
    {
        if(p1.pr==p2.pr){
            return p1.AT>p2.AT;
        }
        return p1.pr<p2.pr;
    }
};
int main()
{
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    vector <process> p(n);
    vector<int> AT(n);
    vector <int> BT(n);
    vector <int> ct(n);
    vector <int> tat(n);
    vector <int> wt(n);
    vector<int> pr(n);
    priority_queue<process, vector<process>, cmp> ready;
    int tat_sum=0;
    int wt_sum=0;
     cout<<"Enter the process in the format--\n";
	cout<<"Priority\tAT\tBT\n";
    for(int i=0;i<n;i++){
        cout<<"process: "<<i+1<<"\n";
        p[i].pid=i;
        p[i].vis=0;

         cin>>p[i].pr;
        cin>>p[i].AT;

        cin>>p[i].BT;

        AT[i]=p[i].AT;
        BT[i]=p[i].BT;
        pr[i]=p[i].pr;
    }
    int time=0;
    bool isComplete=false;
    while(!isComplete){
        isComplete=true;
        for(auto x:p){
            if(x.AT==time){
                ready.push(x);
            }
        }
        if(!ready.empty()){
            process x=ready.top();

            ready.pop();
            p[x.pid].BT--;
            x.BT--;
            if(x.BT==0){
                int ind=x.pid;
                ct[ind]=time+1;
            }else{
                ready.push(x);
            }
        }
        for(auto x:p){
            if(x.BT>0){
                isComplete=false;
            }
        }
        time++;
    }
    for(int i=0;i<n;i++){
	    int id=p[i].pid;
		tat[id]=ct[id]-p[i].AT;
		wt[id]=ct[id]-(p[i].AT+BT[id]);
		tat_sum+=tat[id];
		wt_sum+=wt[id];
	}
	cout<<"Priority\tPNo\tAT\tBT\tCT\tTAT\tWT\n";

    for(int i=0;i<n;i++)
    {
        cout<<pr[i]<<"\t\t"<<i+1<<"\t"<<AT[i]<<"\t"<<BT[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\n";

    }
	 cout<<"Total TAT="<<tat_sum<<"\n";
    cout<<"Total WT="<<wt_sum<<"\n";

	cout<<"Avg TAT= "<<tat_sum/double(n)<<"\n";
	cout<<"Avg WT= "<<wt_sum/double(n)<<"\n";
    return 0;
}

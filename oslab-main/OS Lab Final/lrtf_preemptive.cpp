#include <bits/stdc++.h>
using namespace std;

struct process{
    int pid;
    int at;
    int bt;
    int vis;
};
struct cmp {
    bool operator()(process const& p1, process const& p2)
    {
        if(p1.bt==p2.bt){
            return p1.at>p2.at;
        }
        return p1.bt<p2.bt;
    }
};
int main()
{
    int n;
    cout<<"Enter number of processes"<<endl;
    cin>>n;
    vector <process> p(n);
	vector <int> pid(n);
	vector <int> at(n);
    vector <int> bt(n);
    vector <int> ct(n);
    vector <int> tat(n);
    vector <int> wt(n);
    priority_queue<process, vector<process>, cmp> ready;
    int tat_sum=0;
    int wt_sum=0;
    cout<<"Enter processes in the format AT BT"<<endl;
    for(int i=0;i<n;i++){
        cout<<"process: "<<i+1<<endl;
        p[i].pid=i;
        p[i].vis=0;
        cin>>p[i].at>>p[i].bt;
        bt[i]=p[i].bt;
        at[i]=p[i].at;
        pid[i]=p[i].pid;
    }
    int time=0;
    bool isComplete=false;
    while(!isComplete){
        isComplete=true;
        for(auto x:p){
            if(x.at==time){
                ready.push(x);
            }
        }
        if(!ready.empty()){
            process x=ready.top();

            ready.pop();
            p[x.pid].bt--;
            x.bt--;
            if(x.bt==0){
                int ind=x.pid;
                ct[ind]=time+1;
            }else{
                ready.push(x);
            }
        }
        for(auto x:p){
            if(x.bt>0){
                isComplete=false;
            }
        }
        time++;
    }
    for(int i=0;i<n;i++){
	    int id=p[i].pid;
		tat[id]=ct[id]-p[i].at;
		wt[id]=ct[id]-(p[i].at+bt[id]);
		tat_sum+=tat[id];
		wt_sum+=wt[id];
	}
	cout<<"PNO.\tAT\tBT\tCT\tTAT\tWT\t"<<endl;
	for(int i=0;i<n;i++){
	    cout<<pid[i]+1<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<endl;
	}
	cout<<"Sum of TAT: "<<tat_sum<<endl;
	cout<<"Sum of WT: "<<wt_sum<<endl;
	cout<<"Avg TAT: "<<tat_sum/double(n)<<endl;
	cout<<"Avg WT: "<<wt_sum/double(n)<<endl;
    return 0;
}

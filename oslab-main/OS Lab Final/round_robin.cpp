#include <bits/stdc++.h>
using namespace std;

struct process{
    int pid;
    int at;
    int bt;
    int wt;
    int ct;
    int tat;
};

bool cmp(process p1,process p2){
   if(p1.at==p2.at){
            return p1.pid<p2.pid;
        }
        return p1.at<p2.at;
}
bool cmpid(process p1,process p2){

        return p1.pid<p2.pid;
}
int main()
{
    int n;
    cout<<"Enter number of processes"<<endl;
    cin>>n;
    vector <process> p(n);

    queue<process> ready;
    vector<process> fin;
    int tat_sum=0;
    int wt_sum=0;
    cout<<"Enter processes in the format AT BT"<<endl;
    for(int i=0;i<n;i++){
        cout<<"process: "<<i+1<<endl;
        p[i].pid=i;
        cin>>p[i].at>>p[i].bt;

    }
      sort(p.begin(),p.end(),cmp);

    cout<<"Enter the time quantum: ";
    int tq;
    cin>>tq;

    int i=0;
    int st=p[0].at;

    while(i<n && p[i].at==st)
    {

        ready.push(p[i]);
        i++;
    }

    while(!ready.empty()||i<n){

            bool emp=false;
            int req=tq;
            process u;
            if(ready.empty())
            {

                emp=true;
                req=p[i].at;

            }
            else
            {
                u=ready.front();
                ready.pop();

                req = min(req,u.bt);
                u.bt-=req;
                st+=req;

            }




            while(i<n && p[i].at<=st)
            {

                ready.push(p[i]);
                i++;
            }

            if(!emp&&u.bt==0)
            {
                u.ct=st;
                u.tat=u.ct-u.at;
                u.bt=p[u.pid].bt;
                u.wt=u.tat-u.bt;
                fin.push_back(u);
                tat_sum+=u.tat;
                wt_sum+=u.wt;
            }
            else if(!emp)
            {

                ready.push(u);
            }


    }

    sort(fin.begin(),fin.end(),cmpid);




	cout<<"PNO.\tAT\tBT\tCT\tTAT\tWT\t"<<endl;
	for(int i=0;i<n;i++){
	    cout<<fin[i].pid+1<<"\t"<<fin[i].at<<"\t"<<fin[i].bt<<"\t"<<fin[i].ct<<"\t"<<fin[i].tat<<"\t"<<fin[i].wt<<endl;
	}
	cout<<"Sum of TAT: "<<tat_sum<<endl;
	cout<<"Sum of WT: "<<wt_sum<<endl;
	cout<<"Avg TAT: "<<tat_sum/double(n)<<endl;
	cout<<"Avg WT: "<<wt_sum/double(n)<<endl;
    return 0;
}

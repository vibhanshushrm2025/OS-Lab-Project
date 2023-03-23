#include <bits/stdc++.h>
using namespace std;
struct node{
	int PNo;
	int AT;
	int BT;

};
struct temp{
    int PNo;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};
bool cmp(node x, node y)
{

    if(x.AT==y.AT)
        return x.PNo<y.PNo;

    return x.AT<y.AT;
}

int main()
{
	int n;
	cout<<"Enter the no of tasks:";
	cin>>n;

	vector<node> a(n);
		vector<temp> ans(n+1);

		cout<<"Enter the process in the format--\n";
	cout<<"AT\tBT\n";

	for(int i=0;i<n;i++)
	{
	     cout<<"process: "<<i+1<<"\n";
		 node tem;
        tem.PNo=i+1;

		cin>>tem.AT;

		cin>>tem.BT;


		a[i]=tem;


	}

	sort(a.begin(),a.end(),cmp);

	int last=a[0].AT+a[0].BT;
	int tot_tat=last-a[0].AT;
	int tot_wt=last-(a[0].AT+a[0].BT);
	ans[a[0].PNo].PNo=a[0].PNo;
	ans[a[0].PNo].AT=a[0].AT;
	ans[a[0].PNo].BT=a[0].BT;
	ans[a[0].PNo].CT=last;
	ans[a[0].PNo].TAT=last-a[0].AT;
	ans[a[0].PNo].WT=last-(a[0].AT+a[0].BT);






	for(int i=1;i<n;i++)
	{
	    last=max(last,a[i].AT)+a[i].BT;

		tot_tat+=last-a[i].AT;
		tot_wt+=last-(a[i].AT+a[i].BT);

		 ans[a[i].PNo].PNo=a[i].PNo;
	ans[a[i].PNo].AT=a[i].AT;
	ans[a[i].PNo].BT=a[i].BT;
	ans[a[i].PNo].CT=last;
	ans[a[i].PNo].TAT=last-a[i].AT;
	ans[a[i].PNo].WT=last-(a[i].AT+a[i].BT);
	}

	 cout<<"PNo\tAT\tBT\tCT\tTAT\tWT\n";

    for(int i=1;i<=n;i++)
    {
        cout<<ans[i].PNo<<"\t"<<ans[i].AT<<"\t"<<ans[i].BT<<"\t"<<ans[i].CT<<"\t"<<ans[i].TAT<<"\t"<<ans[i].WT<<"\n";

    }

    cout<<"Total TAT="<<tot_tat<<"\n";
    cout<<"Total WT="<<tot_wt<<"\n";

	double tat_avg=tot_tat*1.0/n;
	double wt_avg=tot_wt*1.0/n;

	cout<<"Average TAT="<<tat_avg<<"\n";
	cout<<"Average WT="<<wt_avg<<"\n";



}

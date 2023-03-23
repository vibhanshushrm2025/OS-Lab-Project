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
bool rev_sort(node a,node b)
{
   if(a.AT == b.AT)
   {
      return a.BT > b.BT;
   }
   return a.AT > b.AT;
}

int main()
{
	int n;
	cout<<"Enter the no of tasks:";
	cin>>n;

	vector<node> a;
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
		a.push_back(tem);


	}

	sort(a.begin(),a.end(),rev_sort);
	int last=a[n-1].AT+a[n-1].BT;
	ans[a[n-1].PNo].PNo=a[n-1].PNo;
	ans[a[n-1].PNo].AT=a[n-1].AT;
	ans[a[n-1].PNo].BT=a[n-1].BT;
	ans[a[n-1].PNo].CT=last;





	int tot_tat=last-a[n-1].AT;
	int tot_wt=last-(a[n-1].AT+a[n-1].BT);
	ans[a[n-1].PNo].TAT=last-a[n-1].AT;
	ans[a[n-1].PNo].WT=last-(a[n-1].AT+a[n-1].BT);

	a.pop_back();



	while(a.size())
    {
        int sz=a.size();
        sort(a.begin(),a.end(),rev_sort);
        if(last<=a[sz-1].AT)
        {

            last=a[sz-1].AT+a[sz-1].BT;
        }
        else
        {
            int mini=INT_MAX;
            int pos=0;
            for(int i=0;i<sz;i++)
            {

                if(a[i].AT<=last&&a[i].BT<=mini)
                {
                    mini=a[i].BT;
                    pos=i;
                }

            }

            swap(a[sz-1],a[pos]);

            last=last+a[sz-1].BT;
        }
        ans[a[sz-1].PNo].PNo=a[sz-1].PNo;
	ans[a[sz-1].PNo].AT=a[sz-1].AT;
	ans[a[sz-1].PNo].BT=a[sz-1].BT;
	ans[a[sz-1].PNo].CT=last;


		tot_tat+=last-a[sz-1].AT;
		tot_wt+=last-(a[sz-1].AT+a[sz-1].BT);
		ans[a[sz-1].PNo].TAT=last-a[sz-1].AT;
	ans[a[sz-1].PNo].WT=last-(a[sz-1].AT+a[sz-1].BT);

		a.pop_back();



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

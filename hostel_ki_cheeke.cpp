#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long int t;
    cin>>t;
    while(t--)
    {
        long long int n,y;
        cin>>n>>y;
        long long int a[n];
        for (int i=0;i<n;i++)cin>>a[i];
        int counter=0,y_check=y;
        for (int i=0;i<n;i++)
        {
            if (a[i]==y)y_check=y;
            if (a[i]==y_check)y_check--;
            else y_check=y;
            if (y_check==0)counter++,y_check=y;
        }
        cout<<counter<<endl;
    }
    return 0;
}
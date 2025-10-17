#include <iostream>
using namespace std;
int main(){
    //cpp program to implement bankers algorithm
    int n,m;
    cout<<"entr no. of processes: ";
    cin>>n;
    cout<<"enter no. of resources: ";
    cin>>m;
    //declaring matrices 2d
    int alloc[20][20], maxNeed[20][20], need[20][20], total[20], avail[20];
    cout<<"Enter alloction matrix(n x m): ";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            //n rows m columns
            cout<<"\nEnter element "<<i<<","<<j<<"(row,column): ";
            cin>>alloc[i][j];
        }
    }
     cout<<"Enter maximum matrix(n x m): ";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            //n rows m columns
            cout<<"\nEnter element "<<i<<","<<j<<"(row,column): ";
            cin>>maxNeed[i][j];
        }
    }
    cout<<"Enter the elements of 1d array Total of size m: ";
    for(int i=0;i<m;i++){
        cout<<"Element "<<i<<": ";
        cin>>total[i];
    }

    for(int j=0;j<m;j++){
        //col fix row changing
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=alloc[i][j];
        }
        avail[j]=total[j]-sum;
    }

    cout<<"\nAll elements of available array are: ";
    for(int i=0;i<m;i++){
        cout<<avail[i]<<" ,";
    }

    //calc need matrix
    cout<<"\nNow calculating the Need matrix(n x m) by maxneed - alloc: ";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j]= maxNeed[i][j]-alloc[i][j];
        }
    }

    cout<<"\nNeed matrix is as follows: "<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<need[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
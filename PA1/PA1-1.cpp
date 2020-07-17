#include <iostream>
#include <string.h>
using namespace std;
int a[500005], b[500005], c[500005];
int d[500005];

int main(){
    int n, k;
    int o = 0, p = 0, q = 0;
    cin>>n;
    memset(d,-1,sizeof(d));
    for (int i = 0;i < n;i++){
        cin>>a[i];
    }
    for (int i = 0;i < n;i++){
        cin>>b[i];
    }
    for (int i = 0;i < n;i++){
        cin>>c[i];
    }
    cin>>k;
    for(int i = 0;i < n;){
        while((d[a[o]] != -1) && (o < n)){
            o++;
        }
        if (o<n){
            d[a[o]] = 1;
            i++;
        }    
        while((d[b[p]] != -1) && (p < n)){
            p++;
        }
        if (p<n){
            d[b[p]] = 2;
            i++;
        }
        while((d[c[q]] != -1) && (q < n)){
            q++;
        }
        if (q<n){
            d[c[q]] = 3;
            i++;
        }
    }
    switch(d[k])
    {
        case 1:
            cout<<"A"<<endl;
            break;
        case 2:
            cout<<"B"<<endl;
            break;
        case 3:
            cout<<"C"<<endl;
            break;
        default:
            cout<<"error"<<endl;
    }
    return 0;
}
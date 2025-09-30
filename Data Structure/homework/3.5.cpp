void removeEle(int arr[],int &n,int K){
    int j=0;
    for(int i=0;i<n;i++){
        if(arr[i]!=K){
            arr[j]=arr[i];
            j++;
        }
    }
    n=j;
}
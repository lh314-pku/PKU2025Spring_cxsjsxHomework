#include <stdio.h>
int main(){
    int n = 0;
    scanf("%d", &n);
    float sum = 0.0 , a[100000], min = 15.0, max = -1.0;
    for(int i = 0; i < n; i++){
        scanf("%f", &a[i]);
        sum += a[i];
        if(a[i] < min)
            min = a[i];
        if(a[i] > max)
            max = a[i];
    }
    printf("%.2f", (sum - max - min)/(n-2));
    return 0;
}
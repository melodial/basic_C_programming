#include<stdio.h>

void swab(int *x , int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
	
}

void insertionSort(int arr[],int panjang){
	int i,j,index=0,temp;
	for(i=1;i<panjang;i++){
		temp = arr[i];
		for(j=i-1;j>=0;j--){
			if(temp < arr[j]){
				swab(&arr[j],&arr[j+1]);
				index = j;
			}else{
				break;
			}
			arr[index] = temp;
		}
	}
}


int main(){
	int arr[] = {1,4,2,64,7,5,8,98,0,2};
	int panjang = sizeof(arr)/sizeof(arr[0]);
	int i;
	insertionSort(arr,panjang);
	for(i=0;i<panjang;i++){
		printf("%d ",arr[i]);
	}
	return 0;
}

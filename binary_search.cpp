#include<stdio.h>

int binarySearch(int arr[],int left,int right,int target){
	while(left<=right){
		int mid = left + (right - left)/2;
		if(arr[mid] == target){
			return mid;
		}
		if(arr[mid] < target){
			left = mid + 1;
		}else{
			right = mid - 1;
		}
	}
	return -1;
}
int main(){
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	int panjang = sizeof(arr)/sizeof(arr[0]);
	int index;
	index = binarySearch(arr,0,panjang-1,10);
	
	if(index != -1){
		printf("Angka ketemu di index %d, yaitu %d",index,arr[index]);
	}else{
		printf("angka tidak ketemu");
	}
}

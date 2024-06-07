#include<stdio.h>

int partition(int arr[],int left,int right){
	int pivot,temp,i,n;
	pivot = arr[right];
	i = left - 1;
	
	for(n=left;n<right;n++){
		if(arr[n] < pivot){
			i++;
			temp = arr[i];
			arr[i] = arr[n];
			arr[n] = temp;
		}
	}
	
	i++;
	temp = arr[i];
	arr[i] = arr[right];
	arr[right] = temp;
	return i;
}

void quickSort(int arr[],int left, int right){
	if(left >= right){
		return;
	}
	int p = partition(arr,left,right);
	quickSort(arr,left,p-1);
	quickSort(arr,p+1,right);
}

int binarySearch(int arr[],int left,int right, int target){
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
	int arr[] = {1,32,4,53,6,4,3,4,7,8,65,34,52,334};
	int size = sizeof(arr)/sizeof(arr[0]);
	int i,index;
	quickSort(arr,0,size-1);
	for(i=0;i<size;i++){
		printf("%d ",arr[i]);
	}
	
	 index = binarySearch(arr,0,size-1,65);
	if(index != -1){
		printf("Angka ketemu di index %d, yaitu %d",index,arr[index]);
	}else{
		printf("tidak ada");
	}
	return 0;
}

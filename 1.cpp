#include<stdio.h>
#include<string.h>

struct nama{
	char nama[31];
	char alamat[31];
};
void inputData(struct nama *list){
	int i;
	for(i=0;i<5;i++){
		printf("input nama: ");
		scanf("%[^\n]",list[i].nama);
		getchar();
		printf("input alamat: ");
		scanf("%[^\n]",list[i].alamat);
		getchar();
	}
}
void printData(struct nama *list){
	int i;
	for(i=0;i<5;i++){
		printf("nama: %s \n",list[i].nama);
		printf("alamat: %s \n",list[i].alamat);
	}
}
void bubbleSort(struct nama *list){
	int i,j,n=5;
	struct nama temp;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-1-i;j++){
			if(strcmp(list[j].nama,list[j+1].nama)>0){
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

void insertionSort(struct nama *list){
	int i,j,n=5;
	struct nama temp;
	for(i=1;i<n;i++){
		temp = list[i];
		j = i-1;
		while(j>=0 && strcmp(list[j].nama,temp.nama)>0){
			list[j+1] = list[j];
			j--;
		}
		list[j+1] = temp;
	}
}
int partition(struct nama *list,int left,int right){
	int n;
	int i;
	struct nama pivot;
	struct nama temp;
	pivot = list[right];
	i = left - 1;
	
	for(n=left; n<=right-1; n++){
		if(strcmp(list[n].nama,pivot.nama) < 0){
			i++;
			temp = list[i];
			list[i] = list[n];
			list[n] = temp;
		}
	}
	
	temp = list[i+1];
	list[i+1] = list[right];
	list[right] = temp;
	return (i+1);
}
void quickSort(struct nama *list,int left,int right){
	if(left < right){
	int p =partition(list,left,right);
	quickSort(list,left,p-1);
	quickSort(list,p+1,right);
	}

}
void menu(){
	printf("===============================\n");
	printf("Sort By name program\n ");
	printf("===============================\n");
	printf("1.bubble sort\n");
	printf("2.insertion sort\n");
	printf("3.Quick sort\n");
	printf("4.Exit\n");
}
int main(){
	int pilihan;
	struct nama list[5];
	inputData(list);
	printf("=========================================\n");
	printData(list);
	printf("\n");
	do{
		menu();
		printf("pilihan: ");
		scanf("%d",&pilihan);
		switch(pilihan){
			
			case 1:
				bubbleSort(list);
				printData(list);
				printf("sort by BubleSort berhasil!\n");
				break;
				
				case 2:
					insertionSort(list);
					printData(list);
					printf("sort by insertionSort berhasil!\n");
					break;
					
					case 3:
						quickSort(list,0,5-1);
						printData(list);
						printf("sort by quickSort berhasil!\n");
						break;
		}
	}while(pilihan != 4);
	
}

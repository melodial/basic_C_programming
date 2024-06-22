#include<stdio.h>

struct anime{
	char id[12];
	char judul[31];
	char genre[31];
	int rating;
};

void scanTheData(struct anime *unit,int n){
	int i;
	for(i=0;i<n;i++){
		printf("inputkan ID anime: ");
		scanf("%s",unit[i].id);
		getchar();
		printf("inputkan judul anime: ");
		scanf("%[^\n]",unit[i].judul);
		getchar();
		printf("inputkan genre anime: ");
		scanf("%[^\n]",unit[i].genre);
		getchar();
		printf("inputkan rating anime(1-10): ");
		scanf("%d",&unit[i].rating);
	}
}

void printToFile(FILE *fp,struct anime *unit,int n){
	int i;
	fp = fopen("myAnimeList.txt","w");
	for(i=0;i<n;i++){
		fprintf(fp,"%s#%s#%s#%d\n",unit[i].id,unit[i].judul,unit[i].genre,unit[i].rating);
	}
	fclose(fp);
}
void readFromFile(FILE *fp,struct anime *unit,int n){
	int i;
	char line[100];
	fp = fopen("myAnimeList.txt","r");
	i=0;
	while(fgets(line,sizeof(line),fp)){
		sscanf(line,"%[^#]#%[^#]#%[^#]#%d",unit[i].id,unit[i].judul,unit[i].genre,&unit[i].rating);
		i++;
	}
	fclose(fp);
}
void printToConsole(struct anime *unit, int n){
	int i;
	for(i=0;i<n;i++){
		printf("ID anime: %s\n",unit[i].id);
		printf("judul anime: %s\n",unit[i].judul);
		printf("genre anime: %s\n",unit[i].genre);
		printf("rating anime: %d\n",unit[i].rating);
	}
}

void list(){
	printf("=========================================== \n");
	printf("selamat datang di animelist: \n");
	printf("=========================================== \n");
	printf("1.input anime: \n");
	printf("2.dispay anime yang sudah di input: \n");
	printf("3.Exit\n");
	printf("pilihan: ");
}

int main(){
	FILE *fp;
	
	int n;
	printf("masukkan jumlah data input: ");
	scanf("%d",&n);
	struct anime unit[n];
	
	int pilihan;
	
	do{
	list();
	scanf("%d",&pilihan);
	
	switch(pilihan){
	case 1:
	scanTheData(unit,n);
	printToFile(fp,unit,n);
	printf("data anime berhasil diinput: \n");
	break;
	case 2:
		readFromFile(fp,unit,n);
		printf("anime yang telah diinput: \n");
		printToConsole(unit,n);
		break;
	}
	
 }while(pilihan != 3);
 
 return 0;
}

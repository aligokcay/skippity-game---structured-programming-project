#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// proje anlatým videosu:
// https://drive.google.com/file/d/1mr2Fh9FOgCMUuJw72aokveF1b9h9SDSs/view?usp=sharing

int ekraniYazdir(char** matris, int N, int user1[5],int user2[5], int mod){
	system("cls");
	int i, j, puan1=user1[0], puan2=user2[0];
	char isim[11];
	if(mod==1){
		strcpy(isim, "user2");
	}else{
		strcpy(isim, "bilgisayar");
	}
	printf("           user 1        		          %s                \n",isim);
	printf("----------------------------		----------------------------\n");
	printf("| \033[0;34mA\033[0m | \033[0;32mB\033[0m | \033[1;35mC\033[0m | \033[0;33mD\033[0m | \033[0;31mE\033[0m | Puan |		| \033[0;34mA\033[0m | \033[0;32mB\033[0m | \033[1;35mC\033[0m | \033[0;33mD\033[0m | \033[0;31mE\033[0m | Puan |\n");
	printf("----------------------------		----------------------------\n");
	for(i=0;i<5;i++){
		printf("|%2d ",user1[i]);
		if(user1[i]<puan1){
			puan1 = user1[i];
		}
	}
	printf("|  %2d  |		",puan1);
	for(i=0;i<5;i++){
		printf("|%2d ",user2[i]);
		if(user2[i]<puan2){
			puan2 = user2[i];
		}
	}
	printf("|  %2d  |\n----------------------------		----------------------------\n\n\n   ",puan2);

	for(j=0; j<4*N+1; j++){
		if((j+2)%4==0){
			printf("%d", ((j+5)/4)%10);
		}else{
			printf(" ");
		}
        
    }
    printf("\n   ");
	for(j=0; j<4*N+1; j++){
        printf("-");
    }
    printf("\n");
    for(i=0; i<N; i++){
    	printf("%2d ",i+1);
        for(j=0; j<N; j++){
        	if(matris[i][j] == 'A'){
        		printf("| \033[0;34m%c \033[0m", matris[i][j]);
			}else if(matris[i][j] == 'B'){
        		printf("| \033[0;32m%c \033[0m", matris[i][j]);
			}else if(matris[i][j] == 'C'){
        		printf("| \033[1;35m%c \033[0m", matris[i][j]);
			}else if(matris[i][j] == 'D'){
        		printf("| \033[0;33m%c \033[0m", matris[i][j]);
			}else if(matris[i][j] == 'E'){
        		printf("| \033[0;31m%c \033[0m", matris[i][j]);
			}else{
				printf("| %c ", matris[i][j]);
			}    
        }
        printf("|\n   ");
        for(j=0; j<4*N+1; j++){
            printf("-");
        }
        printf("\n");
    }
}

char** gameBoard(int N) {
    int i, j, sayac[5] = {0};
    char harfler[] = {'A', 'B', 'C', 'D', 'E'};
    char** matris = (char**)calloc(N, sizeof(char*));
    if (matris == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (i = 0; i < N; i++) {
        matris[i] = (char*)calloc(N, sizeof(char));
        if (matris[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
        	if(((i == N/2-1 || i == N/2) && (j == N/2-1 || j == N/2))){
        		matris[i][j] = ' ';
			}else{
				int rastgele = rand() % 5;
            	while(sayac[rastgele] >= N*N/5){
                	rastgele = rand() % 5;
            	}
            	matris[i][j] = harfler[rastgele];
            	sayac[rastgele]++;
			}
        }
    }
    return matris;
}

void save(char** matris, int N, int user1[5],int user2[5], int mod, int sira){
	int i,j;
	FILE *file = fopen("saveData.txt","w");
	if(file == NULL){
		perror("Dosya açýlamadý");
		return;
	}
	
	fprintf(file, "%d\n%d\n%d\n",N,mod,sira);
	for (i = 0; i < 5; i++) {
        fprintf(file, "%d ", user1[i]);
    }
    fprintf(file, "\n");
    for (i = 0; i < 5; i++) {
        fprintf(file, "%d ", user2[i]);
    }
    fprintf(file, "\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
        	if(matris[i][j]==' '){
        		fprintf(file, "%c ", '0');
			}else{
				fprintf(file, "%c ", matris[i][j]);
			}
            
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void hamle(char** matris, int N, int user1[5],int user2[5],int mod, int sira){
	int harfIlk[2], harfSon[2], yon, flag=0, i, j, bittiMi=0,undo,redo,devam,a;
	char deleted;
	while(bittiMi==0){
		undo=-1;
		while(flag==0 && sira==1){
			printf("Hamle sirasi user1'de.\n");
			harfIlk[0]=N+1;harfIlk[1]=N+1;harfSon[0]=N+1;harfSon[1]=N+1;
			while(harfIlk[0]>N || harfIlk[1]>N || harfSon[0]>N || harfSon[1]>N){
				printf("Hareket ettirmek istediginiz harfin konumunu giriniz: ");
				scanf("%d %d", &harfIlk[0],&harfIlk[1]);
				if(harfIlk[0]==0 && harfIlk[1]==0){
					save(matris, N, user1, user2, mod, 1);
					exit(0);
				}
				printf("Hareket ettirmek istediginiz konumu giriniz: ");
				scanf("%d %d", &harfSon[0], &harfSon[1]);
				if(harfSon[0]==0 && harfSon[1]==0){
					save(matris, N, user1, user2, mod, 1);
					exit(0);
				}
				if(harfIlk[0]>N || harfIlk[1]>N || harfSon[0]>N || harfSon[1]>N){
					ekraniYazdir(matris, N, user1, user2,mod);
					printf("Gecerli konumlar giriniz!\n");
				}
			}
			harfIlk[0]--;harfIlk[1]--;harfSon[0]--;harfSon[1]--;
			if((abs(harfIlk[0]-harfSon[0])==2 && abs(harfIlk[1]-harfSon[1])==0) || (abs(harfIlk[0]-harfSon[0])==0 && abs(harfIlk[1]-harfSon[1])==2)){
				if(matris[harfIlk[0]][harfIlk[1]] != ' ' && matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] != ' ' && matris[harfSon[0]][harfSon[1]] == ' '){
					matris[harfSon[0]][harfSon[1]] = matris[harfIlk[0]][harfIlk[1]];
					deleted = matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2];
					user1[deleted - 'A']++;
					matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = ' ';
					matris[harfIlk[0]][harfIlk[1]] = ' ';
					ekraniYazdir(matris, N, user1, user2,mod);
					undo++;
					flag=1;
				}else{
					ekraniYazdir(matris, N, user1, user2,mod);
					printf("Sectiginiz konumlar, tasin hedefe ulasmasi icin uygun degil!\n");			
				}
			}else{
				ekraniYazdir(matris, N, user1, user2,mod);
				printf("Sadece iki kare ileriye atlayabilirsiniz!\n");			
			}

			if(undo==0){  // sadece 1 kere undo hakký vermek için
				printf("Undo yapmak istiyor musunuz? (1- Evet / 2 - Hayir) : ");
				scanf("%d",&undo);
				if(undo==1){
					matris[harfIlk[0]][harfIlk[1]] = matris[harfSon[0]][harfSon[1]];
					user1[deleted - 'A']--;
					matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = deleted;
					matris[harfSon[0]][harfSon[1]] = ' ';
					ekraniYazdir(matris, N, user1, user2,mod);
					flag=0;
					printf("Redo yapmak istiyor musunuz? (1- Evet / 2 - Hayir) : ");
					scanf("%d",&redo);
					if(redo==1){
						matris[harfSon[0]][harfSon[1]] = matris[harfIlk[0]][harfIlk[1]];
						user1[deleted - 'A']++;
						matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = ' ';
						matris[harfIlk[0]][harfIlk[1]] = ' ';
						ekraniYazdir(matris, N, user1, user2,mod);
						flag=1;
					}
				}else{
					ekraniYazdir(matris, N, user1, user2,mod);
				}
			}

			a = -2,devam=0;
	        while (a < 3 && devam == 0) {
	            if (harfSon[1] + a >= 0 &&  harfSon[1] + a < N) {
	                if (matris[harfSon[0]][harfSon[1] + a/2] != ' ' && matris[harfSon[0]][harfSon[1] + a] == ' '){
						devam=1;
	                }
	            }
	            if (harfSon[0] + a >= 0 && harfSon[0] + a < N) {
	                if (matris[harfSon[0] + a/2][harfSon[1]] != ' ' && matris[harfSon[0] + a][harfSon[1]] == ' '){
	                	devam=1;
	                }
	            }
	            a += 4;
	        }
	        
			while((flag>0) && devam==1){
				printf("Devam etmek istiyor musunuz? (1- Evet / 2 - Hayir) : ");
				scanf("%d",&devam);
				if(devam==1){
					harfIlk[0]=harfSon[0];harfIlk[1]=harfSon[1];					
					harfSon[0]=N+1;harfSon[1]=N+1;
					while(harfSon[0]>N || harfSon[1]>N){
						printf("Hareket ettirmek istediginiz konumu giriniz: ");
						scanf("%d %d", &harfSon[0], &harfSon[1]);
						if(harfSon[0]>N || harfSon[1]>N){
							ekraniYazdir(matris, N, user1, user2,mod);
							printf("Gecerli konumlar giriniz!\n");
						}
					}
					harfSon[0]--;harfSon[1]--;
					if((abs(harfIlk[0]-harfSon[0])==2 && abs(harfIlk[1]-harfSon[1])==0) || (abs(harfIlk[0]-harfSon[0])==0 && abs(harfIlk[1]-harfSon[1])==2)){
						if(matris[harfIlk[0]][harfIlk[1]] != ' ' && matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] != ' ' && matris[harfSon[0]][harfSon[1]] == ' '){
							matris[harfSon[0]][harfSon[1]] = matris[harfIlk[0]][harfIlk[1]];
							deleted = matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2];
							user1[deleted - 'A']++;
							matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = ' ';
							matris[harfIlk[0]][harfIlk[1]] = ' ';
							ekraniYazdir(matris, N, user1, user2,mod);
							flag=2;
						}else{
							ekraniYazdir(matris, N, user1, user2,mod);
							printf("Sectiginiz konumlar, tasin hedefe ulasmasi icin uygun degil!\n");			
						}
					}else{
						ekraniYazdir(matris, N, user1, user2,mod);
						printf("Sadece iki kare ileriye atlayabilirsiniz!\n");			
					}
					if(undo==2 && flag==2){  // sadece 1 kere undo hakký vermek için
						printf("Undo yapmak istiyor musunuz? (1- Evet / 2 - Hayir) : ");
						scanf("%d",&undo);
						if(undo==1){
							matris[harfIlk[0]][harfIlk[1]] = matris[harfSon[0]][harfSon[1]];
							user1[deleted - 'A']--;
							matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = deleted;
							matris[harfSon[0]][harfSon[1]] = ' ';
							ekraniYazdir(matris, N, user1, user2,mod);
							flag=0;
							printf("Redo yapmak istiyor musunuz? (1- Evet / 2 - Hayir) : ");
							scanf("%d",&redo);
							if(redo==1){
								matris[harfSon[0]][harfSon[1]] = matris[harfIlk[0]][harfIlk[1]];
								user1[deleted - 'A']++;
								matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = ' ';
								matris[harfIlk[0]][harfIlk[1]] = ' ';
								ekraniYazdir(matris, N, user1, user2,mod);
								flag=1;
							}
						}else{
							ekraniYazdir(matris, N, user1, user2,mod);
						}
					}
					
					if(devam==1){
						devam=0;
						a = -2,devam=0;
				        while (a < 3 && devam == 0) {
				            if (harfSon[1] + a >= 0 &&  harfSon[1] + a < N) {
				                if (matris[harfSon[0]][harfSon[1] + a/2] != ' ' && matris[harfSon[0]][harfSon[1] + a] == ' '){
									devam=1;
				                }
				            }
				            if (harfSon[0] + a >= 0 && harfSon[0] + a < N) {
				                if (matris[harfSon[0] + a/2][harfSon[1]] != ' ' && matris[harfSon[0] + a][harfSon[1]] == ' '){
				                	devam=1;
				                }
				            }
				            a += 4;
				        }
					}
				}
			}
		}
		flag=0,i=0,bittiMi=1;
		while(i<N && bittiMi==1){  // oyunun bitip bitmedigini kontrol ediyorum. while kullanarak
			j=0;				  // daha verimli bir kontrol yapmayý amaçladým.
			while(j<N && bittiMi==1){
				a = -2;
		        while (a < 3 && flag == 0) {
		            if (matris[i][j] != ' ' && j + a >= 0 && j + a < N) {
		                if (matris[i][j + a/2] != ' ' && matris[i][j + a] == ' '){
							bittiMi=0;
		                }
		            }
		            if (matris[i][j] != ' ' && i + a >= 0 && i + a < N) {
		                if (matris[i + a/2][j] != ' ' && matris[i + a][j] == ' '){
		                	bittiMi=0;
		                }
		            }
		            a += 4;
		        }
				j++;
			}
			i++;
		}
		sira=2;
		if(mod==1){
			undo=-1,devam=1;
			while(flag==0 && bittiMi==0 && sira == 2){
				printf("Hamle sirasi user2'de.\n");
				harfIlk[0]=N+1;harfIlk[1]=N+1;harfSon[0]=N+1;harfSon[1]=N+1;
				while(harfIlk[0]>N || harfIlk[1]>N || harfSon[0]>N || harfSon[1]>N){
					printf("Hareket ettirmek istediginiz harfin konumunu giriniz: ");
					scanf("%d %d", &harfIlk[0],&harfIlk[1]);
					if(harfIlk[0]==0 && harfIlk[1]==0){
						save(matris, N, user1, user2, mod, 2);
						exit(0);
					}
					printf("Hareket ettirmek istediginiz konumu giriniz: ");
					scanf("%d %d", &harfSon[0], &harfSon[1]);
					if(harfSon[0]==0 && harfSon[1]==0){
						save(matris, N, user1, user2, mod, 2);
						exit(0);
					}
					if(harfIlk[0]>N || harfIlk[1]>N || harfSon[0]>N || harfSon[1]>N){
						ekraniYazdir(matris, N, user1, user2,mod);
						printf("Gecerli konumlar giriniz!\n");
					}
				}
				harfIlk[0]--;harfIlk[1]--;harfSon[0]--;harfSon[1]--;
				if((abs(harfIlk[0]-harfSon[0])==2 && abs(harfIlk[1]-harfSon[1])==0) || (abs(harfIlk[0]-harfSon[0])==0 && abs(harfIlk[1]-harfSon[1])==2)){
					if(matris[harfIlk[0]][harfIlk[1]] != ' ' && matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] != ' ' && matris[harfSon[0]][harfSon[1]] == ' '){
						matris[harfSon[0]][harfSon[1]] = matris[harfIlk[0]][harfIlk[1]];
						deleted = matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2];
						user2[deleted - 'A']++;
						matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = ' ';
						matris[harfIlk[0]][harfIlk[1]] = ' ';
						ekraniYazdir(matris, N, user1, user2,mod);
						undo++;
						flag=1;
					}else{
						ekraniYazdir(matris, N, user1, user2,mod);
						printf("Sectiginiz konumlar, tasin hedefe ulasmasi icin uygun degil!\n");			
					}
				}else{
					ekraniYazdir(matris, N, user1, user2,mod);
					printf("Sadece iki kare ileriye atlayabilirsiniz!\n");			
				}
				if(undo==0){  // sadece 1 kere undo hakký vermek için
					printf("Undo yapmak istiyor musunuz? (1- Evet / 2 - Hayir) : ");
					scanf("%d",&undo);
					if(undo==1){
						matris[harfIlk[0]][harfIlk[1]] = matris[harfSon[0]][harfSon[1]];
						user2[deleted - 'A']--;
						matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = deleted;
						matris[harfSon[0]][harfSon[1]] = ' ';
						ekraniYazdir(matris, N, user1, user2,mod);
						flag=0;
						printf("Redo yapmak istiyor musunuz? (1- Evet / 2 - Hayir) : ");
						scanf("%d",&redo);
						if(redo==1){
							matris[harfSon[0]][harfSon[1]] = matris[harfIlk[0]][harfIlk[1]];
							user2[deleted - 'A']++;
							matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = ' ';
							matris[harfIlk[0]][harfIlk[1]] = ' ';
							ekraniYazdir(matris, N, user1, user2,mod);
							flag=1;
						}
					}else{
						ekraniYazdir(matris, N, user1, user2,mod);
					}
				}
				a = -2,devam=0;
		        while (a < 3 && devam == 0) {
		            if (harfSon[1] + a >= 0 &&  harfSon[1] + a < N) {
		                if (matris[harfSon[0]][harfSon[1] + a/2] != ' ' && matris[harfSon[0]][harfSon[1] + a] == ' '){
							devam=1;
		                }
		            }
		            if (harfSon[0] + a >= 0 && harfSon[0] + a < N) {
		                if (matris[harfSon[0] + a/2][harfSon[1]] != ' ' && matris[harfSon[0] + a][harfSon[1]] == ' '){
		                	devam=1;
		                }
		            }
		            a += 4;
		        }
		        
				while((flag>0) && devam==1){
					printf("Devam etmek istiyor musunuz? (1- Evet / 2 - Hayir) : ");
					scanf("%d",&devam);
					if(devam==1){
						harfIlk[0]=harfSon[0];harfIlk[1]=harfSon[1];
						harfSon[0]=N+1;harfSon[1]=N+1;
						while(harfSon[0]>N || harfSon[1]>N){
							printf("Hareket ettirmek istediginiz konumu giriniz: ");
							scanf("%d %d", &harfSon[0], &harfSon[1]);
							if(harfSon[0]>N || harfSon[1]>N){
								ekraniYazdir(matris, N, user1, user2,mod);
								printf("Gecerli konumlar giriniz!\n");
							}
						}
						harfSon[0]--;harfSon[1]--;
						if((abs(harfIlk[0]-harfSon[0])==2 && abs(harfIlk[1]-harfSon[1])==0) || (abs(harfIlk[0]-harfSon[0])==0 && abs(harfIlk[1]-harfSon[1])==2)){
							if(matris[harfIlk[0]][harfIlk[1]] != ' ' && matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] != ' ' && matris[harfSon[0]][harfSon[1]] == ' '){
								matris[harfSon[0]][harfSon[1]] = matris[harfIlk[0]][harfIlk[1]];
								deleted = matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2];
								user2[deleted - 'A']++;
								matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = ' ';
								matris[harfIlk[0]][harfIlk[1]] = ' ';
								ekraniYazdir(matris, N, user1, user2,mod);
								flag=2;
							}else{
								ekraniYazdir(matris, N, user1, user2,mod);
								printf("Sectiginiz konumlar, tasin hedefe ulasmasi icin uygun degil!\n");			
							}
						}else{
							ekraniYazdir(matris, N, user1, user2,mod);
							printf("Sadece iki kare ileriye atlayabilirsiniz!\n");			
						}
						if(undo==2 && flag==2){  // sadece 1 kere undo hakký vermek için
							printf("Undo yapmak istiyor musunuz? (1- Evet / 2 - Hayir) : ");
							scanf("%d",&undo);
							if(undo==1){
								matris[harfIlk[0]][harfIlk[1]] = matris[harfSon[0]][harfSon[1]];
								user2[deleted - 'A']--;
								matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = deleted;
								matris[harfSon[0]][harfSon[1]] = ' ';
								ekraniYazdir(matris, N, user1, user2,mod);
								flag=0;
								printf("Redo yapmak istiyor musunuz? (1- Evet / 2 - Hayir) : ");
								scanf("%d",&redo);
								if(redo==1){
									matris[harfSon[0]][harfSon[1]] = matris[harfIlk[0]][harfIlk[1]];
									user2[deleted - 'A']++;
									matris[(harfIlk[0]+harfSon[0])/2][(harfIlk[1]+harfSon[1])/2] = ' ';
									matris[harfIlk[0]][harfIlk[1]] = ' ';
									ekraniYazdir(matris, N, user1, user2,mod);
									flag=1;
								}
							}else{
								ekraniYazdir(matris, N, user1, user2,mod);
							}
						}
						if(devam==1){
							devam=0;
							a = -2,devam=0;
					        while (a < 3 && devam == 0) {
					            if (harfSon[1] + a >= 0 &&  harfSon[1] + a < N) {
					                if (matris[harfSon[0]][harfSon[1] + a/2] != ' ' && matris[harfSon[0]][harfSon[1] + a] == ' '){
										devam=1;
					                }
					            }
					            if (harfSon[0] + a >= 0 && harfSon[0] + a < N) {
					                if (matris[harfSon[0] + a/2][harfSon[1]] != ' ' && matris[harfSon[0] + a][harfSon[1]] == ' '){
					                	devam=1;
					                }
					            }
					            a += 4;
					        }
						}
					}
				}
			}
		}else{
			while(flag==0 && bittiMi==0){
				int max1=user1[0],max2=user2[0],min1=user1[0],min2=user2[0],min1Index=0,min2Index=0;
				printf("Hamle sirasi bilgisayarda.\n");
				for(i=0;i<5;i++){
					if(max1<user1[i]){
						max1=user1[i];
					}
					if(max2<user2[i]){
						max2=user2[i];
					}
					if(min1>user1[i]){
						min1=user1[i];
						min1Index=i;
					}
					if(min2>user2[i]){
						min2=user2[i];
						min2Index=i;
					}
				}
				if(max1-min1>1){ // bilgisayarin ilk amaci rakibinin puanini artirmasini engellemek
					i=0;
					while(i<N && flag==0){
						j=0;
						while(j<N && flag==0){
							a = -2;
					        while (a < 3 && flag == 0) {
					            if (matris[i][j] != ' ' && j + a >= 0 && j + a < N) {
					                if (matris[i][j + a/2] == min1Index+'A' && matris[i][j + a] == ' '){
					                    matris[i][j + a] = matris[i][j];
					                    user2[matris[i][j + a/2] - 'A']++;
					                    matris[i][j + a/2] = ' ';
					                    matris[i][j] = ' ';
					                    flag = 1;
					                    harfSon[0]=i;
					                    harfSon[1]=j+a;
					                    
					                    printf("Bilgisayar oynuyor");
					                    int t;
					                    for(t=0;t<3;t++){
					                    	usleep(400000);
					                    	printf(".");
										}
										usleep(400000);
					                    ekraniYazdir(matris, N, user1, user2,mod);
					                }
					            }
					            if (matris[i][j] != ' ' && i + a >= 0 && i + a < N) {
					                if (matris[i + a/2][j] == min1Index+'A' && matris[i + a][j] == ' '){
					                    matris[i + a][j] = matris[i][j];
					                    user2[matris[i + a/2][j] - 'A']++;
					                    matris[i + a/2][j] = ' ';
					                    matris[i][j] = ' ';
					                    flag = 1;
					                    harfSon[0]=i+a;
					                    harfSon[1]=j;
					                    
					                    printf("Bilgisayar oynuyor");
					                    int t;
					                    for(t=0;t<3;t++){
					                    	usleep(400000);
					                    	printf(".");
										}
										usleep(400000);
					                    ekraniYazdir(matris, N, user1, user2,mod);
					                }
					            }
					            a += 4;
					        }
							j++;
						}
						i++;
					}
				}
				if(max2-min2>1 && flag==0){ // bilgisayarin ikinci amaci en düsük oldugu  harfi artirabilmek
					i=0,flag=0;
					while(i<N && flag==0){
						j=0;
						while(j<N && flag==0){
							a = -2;
					        while (a < 3 && flag == 0) {
					            if (matris[i][j] != ' ' && j + a >= 0 && j + a < N) {
					                if (matris[i][j + a/2] == min2Index+'A' && matris[i][j + a] == ' '){
					                    matris[i][j + a] = matris[i][j];
					                    user2[matris[i][j + a/2] - 'A']++;
					                    matris[i][j + a/2] = ' ';
					                    matris[i][j] = ' ';
					                    flag = 1;
					                    harfSon[0]=i;
					                    harfSon[1]=j+a;
					                    
					                    printf("Bilgisayar oynuyor");
					                    int t;
					                    for(t=0;t<3;t++){
					                    	usleep(400000);
					                    	printf(".");
										}
										usleep(400000);
					                    ekraniYazdir(matris, N, user1, user2,mod);
					                }
					            }
					            if (matris[i][j] != ' ' && i + a >= 0 && i + a < N) {
					                if (matris[i + a/2][j] == min2Index+'A' && matris[i + a][j] == ' '){
					                    matris[i + a][j] = matris[i][j];
					                    user2[matris[i + a/2][j] - 'A']++;
					                    matris[i + a/2][j] = ' ';
					                    matris[i][j] = ' ';
					                    flag = 1;
					                    harfSon[0]=i+a;
					                    harfSon[1]=j;
					                    
					                    printf("Bilgisayar oynuyor");
					                    int t;
					                    for(t=0;t<3;t++){
					                    	usleep(400000);
					                    	printf(".");
										}
										usleep(400000);
					                    ekraniYazdir(matris, N, user1, user2,mod);
					                }
					            }
					            a += 4;
					        }
							j++;
						}
						i++;
					}
				}
				i=0;
				while (i < N && flag == 0) {
				    j = 0;
				    while (j < N && flag == 0) {
				        a = -2;
				        while (a < 3 && flag == 0) {
				            if (matris[i][j] != ' ' && j + a >= 0 && j + a < N) {
				                if (matris[i][j + a/2] != ' ' && matris[i][j + a] == ' '){
				                    matris[i][j + a] = matris[i][j];
				                    user2[matris[i][j + a/2] - 'A']++;
				                    matris[i][j + a/2] = ' ';
				                    matris[i][j] = ' ';
				                    flag = 1;
				                    harfSon[0]=i;
					                harfSon[1]=j+a;
					                
					                printf("Bilgisayar oynuyor");
					                    int t;
					                    for(t=0;t<3;t++){
					                    	usleep(400000);
					                    	printf(".");
										}
										usleep(400000);
					                    ekraniYazdir(matris, N, user1, user2,mod);
				                }
				            }
				            if (matris[i][j] != ' ' && i + a >= 0 && i + a < N) {
				                if (matris[i + a/2][j] != ' ' && matris[i + a][j] == ' '){
				                    matris[i + a][j] = matris[i][j];
				                    user2[matris[i + a/2][j] - 'A']++;
				                    matris[i + a/2][j] = ' ';
				                    matris[i][j] = ' ';
				                    flag = 1;
				                    harfSon[0]=i+a;
					                harfSon[1]=j;
					                
					                printf("Bilgisayar oynuyor");
					                    int t;
					                    for(t=0;t<3;t++){
					                    	usleep(400000);
					                    	printf(".");
										}
										usleep(400000);
					                    ekraniYazdir(matris, N, user1, user2,mod);
				                }
				            }
				            a += 4;
				        }
				        j++;
				    }
				    i++;
				}
				
				devam=1;
				while(devam==1 && flag==1){
					a = -2,devam=0;
		        	while (a < 3 && devam == 0) {
			            if (harfSon[1] + a >= 0 &&  harfSon[1] + a < N) {
			                if (matris[harfSon[0]][harfSon[1] + a/2] != ' ' && matris[harfSon[0]][harfSon[1] + a] == ' '){
			                	matris[harfSon[0]][harfSon[1] + a] = matris[harfSon[0]][harfSon[1]];
			                	user2[matris[harfSon[0]][harfSon[1] + a/2] - 'A']++;
								matris[harfSon[0]][harfSon[1] + a/2] = ' ';
								matris[harfSon[0]][harfSon[1]] = ' ';
								devam=1;
								harfSon[1]=harfSon[1] + a;
								printf("Bilgisayar oynuyor");
			                    int t;
			                    for(t=0;t<3;t++){
			                    	usleep(400000);
			                    	printf(".");
								}
								usleep(400000);
			                    ekraniYazdir(matris, N, user1, user2,mod);
			                }
			            }
			            if (harfSon[0] + a >= 0 && harfSon[0] + a < N) {
			                if (matris[harfSon[0] + a/2][harfSon[1]] != ' ' && matris[harfSon[0] + a][harfSon[1]] == ' '){
			                	matris[harfSon[0] + a][harfSon[1]] = matris[harfSon[0]][harfSon[1]];
			                	user2[matris[harfSon[0] + a/2][harfSon[1]] - 'A']++;
								matris[harfSon[0] + a/2][harfSon[1]] = ' ';
								matris[harfSon[0]][harfSon[1]] = ' ';
								devam=1;
								harfSon[0]=harfSon[0] + a;
								printf("Bilgisayar oynuyor");
					                    int t;
					                    for(t=0;t<3;t++){
					                    	usleep(400000);
					                    	printf(".");
										}
										usleep(400000);
					                    ekraniYazdir(matris, N, user1, user2,mod);
			                }
			            }
			            a += 4;
		        	}
				}
			}
		}
		flag=0,i=0,bittiMi=1;
		while(i<N && bittiMi==1){
			j=0;
			while(j<N && bittiMi==1){
				a = -2;
		        while (a < 3 && flag == 0) {
		            if (matris[i][j] != ' ' && j + a >= 0 && j + a < N) {
		                if (matris[i][j + a/2] != ' ' && matris[i][j + a] == ' '){
							bittiMi=0;
		                }
		            }
		            if (matris[i][j] != ' ' && i + a >= 0 && i + a < N) {
		                if (matris[i + a/2][j] != ' ' && matris[i + a][j] == ' '){
		                	bittiMi=0;
		                }
		            }
		            a += 4;
		        }
				j++;
			}
			i++;
		}
		sira=1;		
	}
	
	int puan1=user1[1], puan2=user2[1],toplam1=0,toplam2=0;
	for(i=0;i<5;i++){
		if(user1[i]<puan1){
			puan1 = user1[i];
		}
		if(user2[i]<puan2){
			puan2 = user2[i];
		}
		toplam1+=user1[i];
		toplam2+=user2[i];
	}
	
	if(puan1>puan2){
		printf("Oyunun kazanani user1'dir.");
	}else if(puan2>puan1){
		if(mod==1){
			printf("Oyunun kazanani user2'dir.");
		}else{
			printf("Oyunun kazanani bilgisayardir.");
		}
	}else{
		if(toplam1>toplam2){
			printf("Puanlar esittir ama user1'in toplam harf sayisi daha fazla oldugu icin oyunun kazanani user1'dir.");
		}else if(toplam2>toplam1){
			if(mod==1){
				printf("Puanlar esittir ama user2'nin toplam harf sayisi daha fazla oldugu icin oyunun kazanani user2'dir.");
			}else{
				printf("Puanlar esittir ama bilgisayarin toplam harf sayisi daha fazla oldugu icin oyunun kazanani bilgisayardir.");
			}
			
		}else{
			printf("Dostluk kazandý =)\nOyun berabere bitmistir.");
		}
	}
	FILE *file=fopen("saveData.txt", "r");
	if(file != NULL){
		fclose(file);
    	remove("saveData.txt");
	}
}

void freeMatris(char** matris, int N) {
    int i;
    for (i = 0; i < N; i++) {
        free(matris[i]);
    }
    free(matris);
}

void game(){
    	system("cls");
    	char** matris;
		int N, i,j ,mod,kayit,sira=1;
		int user1[5],user2[5];
        for(i=0;i<5;i++){
        	user1[i]=0;
        	user2[i]=0;
		}
		FILE *file=fopen("saveData.txt", "r");
		if(file == NULL){
			kayit=2;
			printf("1- Iki kisilik oyun\n2- Bilgisayara karsi oyun\nOynamak istediginiz modu seciniz: ");
			scanf("%d", &mod);
        	printf("Oyun tahtasinin boyutunu giriniz: ");
        	scanf("%d", &N);
        	matris = gameBoard(N);
		}else{
			printf("1- Kaydedilmis oyuna devam et\n2- Yeni oyun baslat\nSeciminizi yapiniz: ");
			scanf("%d", &kayit);
			if(kayit==2){
				fclose(file);
	        	remove("saveData.txt");
				printf("1- Iki kisilik oyun\n2- Bilgisayara karsi oyun\nOynamak istediginiz modu seciniz: ");
				scanf("%d", &mod);
        		printf("Oyun tahtasinin boyutunu giriniz: ");
        		scanf("%d", &N);
        		matris = gameBoard(N);
			}else{
				fscanf(file, "%d", &N);
			    fscanf(file, "%d", &mod);
			    fscanf(file, "%d", &sira);
			    
			    for (i = 0; i < 5; i++) {
			        fscanf(file, "%d", &user1[i]);
			    }
			    
			    for (i = 0; i < 5; i++) {
			        fscanf(file, "%d", &user2[i]);
			    }
				matris = gameBoard(N);	
				for (i = 0; i < N; i++) {
			        for (j = 0; j < N; j++) {
			            fscanf(file, " %c", &matris[i][j]);
			            if(matris[i][j] == '0'){
			            	matris[i][j] = ' ';
						}
			        }
			    }
			}
		}
		fclose(file);
        ekraniYazdir(matris, N, user1, user2,mod);
        hamle(matris, N, user1, user2,mod,sira);
        freeMatris(matris, N);
	}
	
void printGameRules() {
	system("cls");
    printf("OYUN KURALLARI\n\n");
    printf("1- Tahta Boyutu:\n");
    printf(" Tahtanin boyutu kullanici tarafindan belirlenir.\n");
    printf(" Boyut minimum 6, maksimum 20 olabilir.\n\n");
    
	printf("2- Oyun Modlari:\n");
    printf(" Oyun, iki oyuncunun karsilikli oynayabilecegi modda veya bilgisayara karsi oynanabilen modda oynanabilir.\n\n");

	printf("3- Puan Hesabi:\n");
    printf(" Her tam renk set tamamlandiginnda oyuncunun puani artar. Bir tam renk set, her renkten birer adet tasi icermelidir.\n\n");

    printf("3- Hamleler:\n");
    printf(" Kullanicilar hamle yapmak icin tasin ve yerlestirilecek hucrenin koordinatlarini girer.\n");
    printf(" Tasin uzerinden atladigi hucre dolu olmalidir.\n");
    printf(" Hamle sonrasi atlanan taslar otomatik olarak tahtadan silinir ve puanlar guncellenir.\n\n");

    printf("5- Undo/Redo Hakki:\n");
    printf(" Her kullanici, karsi taraf hamle yapmadan once bir kez undo (geri al) veya redo (yinele) yapma hakkina sahiptir.\n\n");

    printf("6- Devam Etme Hakki:\n");
    printf(" Kullanici bir hamle yaptiktan sonra, tasin baska bir hamle yapma sansi varsa, devam edip etmemeye karar verebilir.\n");
    printf(" Devam etmek isterse, tasini yeniden hareket ettirir.\n");
    printf(" Devam etmek istemezse, hamle sirasi diger oyuncuya gecer.\n\n");

    printf("7- Oyunu Sonlandirma ve Kaydetme:\n");
    printf(" Kullanici, oyunu istedigi zaman koordinatlara \"0 0\" girerek sonlandirabilir. ");
    printf(" Bu islem, oyun tahtasini kaydeder ve kullanici oyuna daha sonra kaldigi yerden devam edebilir.\n\n");

    printf("8- Oyun Bitisi:\n");
    printf(" Oyun, hamle yapma olasiligi kalmadiginda sona erer.\n");
    printf(" Oyun bitiminde en yuksek puana sahip oyuncu oyunu kazanir.\n");
    printf(" Puanlar esitse, tas sayisi fazla olan oyuncu kazanir.\n");
    printf(" Tas sayisi da esitse, oyun beraberlikle sona erer.\n");
}
	

void menu(int flag) {
	system("cls");
    int secim;
    if (flag != 0) {
        printf(" Lutfen gecerli bir deger giriniz[1-3]\n\n");
        flag = 0;
    }
    printf("1. Oyuna Basla\n");
    printf("2. Kurallari ogren\n");
    printf("3. Oyundan cik\n");
    printf("Seciminizi yapin:");
    scanf(" %d", &secim);

    switch (secim) {
    case 1:game();break;
    case 2:printGameRules();break;
    case 3:exit(0);break;
    default:
        menu(1);
    }
}

int main() {
	srand(time(NULL));
    char choice = 'm';
    menu(0);
    while (choice == 'm') {
        printf("\nMenuye donmek icin m'ye, cikmak icin q'ya basin: ");
        scanf(" %c", &choice);

        while (choice != 'm' && choice != 'q') {
            system("cls");
            printf("Lutfen gecerli bir islem giriniz!!\n");
            printf("Menuye donmek icin m'ye, cikmak icin q'ya basin: ");
            scanf(" %c", &choice);
        }
        if (choice == 'm') {
            menu(0);
        }
    }

    return 0;
}

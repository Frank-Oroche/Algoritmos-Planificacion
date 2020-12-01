#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define M 10 //tamaño de la matriz (numero de procesos - 1)

void FCFS(int array[M][2]);
void SRTF(int array[M][2]);
void RR(int array[M][2]);
int menu();
void ImprimirMatriz(int lastdone, int output[M][100]);
void CopiarArray(int arr[M][2],int array[M][2]);

int main(int argc, char *argv[]){
	int op=0;
	int arr[M][2] = {{0,0},{1,3},{2,3},{3,4},{4,4},{5,2},{6,3},{7,4},{8,4},{9,4}};
	//int arr[M][2] = {{0,0},{1,4},{2,3},{2,3},{3,2}};
	do{
		system("cls");
		op=menu();
		switch(op){
			case 1:
                FCFS(arr);
                break;
            case 2:
                SRTF(arr);
                break;
            case 3:
                RR(arr);
                break;
            case 4:
                return 0;
		}
	}while(op!=4);
}

int menu(){
	int op;
	do{
		system("cls");
		printf("\tMENU DE ALGORITMOS DE PLANIFICACION\n");
		printf("[ 1]: FCFS\n");
		printf("[ 2]: SRTF\n");
		printf("[ 3]: RR\n");
		printf("[ 4]: salir\n");
		printf("\tElija una opcion...........[ ]\b\b");
	    scanf("%d",&op);
	}while(op<1 || 4<op);
	return op;
}

void ImprimirMatriz(int lastdone, int output[M][100]){
	int i,l;
    printf("   ");
    for (l = 0; l < lastdone; l++)  {
    	printf("%2d   ",l);
    }
    printf("\n    ");
    for (l = 0; l < lastdone; l++)  {
        printf("-----");
    }
    printf("\n");
    for (i = 1; i < M; i++) {
        printf("%c ",i+64);
        for (l = 0; l < lastdone; l++)  {
            if (output[i][l] == 1) {
                printf("  -  ");
            }else{
            	printf("     ");
			}
        }
        printf("\n");
    }
    printf("    ");
    for (l = 0; l < lastdone; l++)  {
        printf("-----");
    }
    printf("\n");
	getche();
}

void CopiarArray(int arr[M][2],int array[M][2]){
	int i,j;
	for(i=0;i<M;i++){
    	for(j=0;j<2;j++){
    		arr[i][j]=array[i][j];
		}
	}
}

void FCFS(int array[M][2]){
    int arr[M][2];
    int i,j,k,l;
    int loop = 0,ready = 0,lastdone = 0,allprdone = 0;
    int output[M][100] = {0};
    CopiarArray(arr,array);
    for (i = 1; i < M; i++) {
        loop += arr[i][1] + arr[i][0];
    }
    for (i = 0; i < loop; i++) {
        ready = 0;
        for (j = 1; j < M; j++) {
            if (i >= arr[j][0] && arr[j][1] >= 1) {
                if (ready == 0) {
                    ready = j;
                    break;
                }
            }
        }
        if (ready > 0) {
            arr[ready][1]--;
            output[ready][i] = 1;
        }
        if (arr[M-1][1] < 1) {
            lastdone = ++i;
            break;
        }
    }
    ImprimirMatriz(lastdone,output);
}

void SRTF(int array[M][2]){
    int arr[M][2];
    int i,j,k,l;
    int loop = 0,ready = 0,lastdone = 0,allprdone = 0;
    int output[M][100] = {0};
    CopiarArray(arr,array);
    for (i = 1; i < M; i++) {
        loop += arr[i][1]+arr[i][0];
    }
    for (i = 0; i < loop; i++) {
        allprdone = 0;
        ready = 0;
        for (j = 1; j < M; j++) {
            if (i >=arr[j][0] && arr[j][1] >= 1) {
                if (ready == 0) {
                    ready = j;
                }else if (arr[j][1] < arr[ready][1]) {
                    ready = j;
                }
            }
            if (arr[j][1] < 1){
            	allprdone++;
			}
        }
        if (ready > 0) { 
            arr[ready][1]--; 
            output[ready][i] = 1; 
        }
        if (allprdone == M-1) { 
            lastdone = i; 
            break;
        }
    }
	ImprimirMatriz(lastdone,output);
}

void RR(int array[M][2]){
    int arr[M][2];
    int i,j,l,k;
    int timequantom = 1,loop = 0,ready = 0,lastdone = 0,allprdone = 0;
    int output[M][100] = {0},q[M] = {0},scpr[M] = {0};
    CopiarArray(arr,array);
    printf("\n\tIngrese Quantum: ");
	scanf("%d",&timequantom);
    for (i = 1; i < M; i++) {
        loop += arr[i][1] + arr[i][0];
    }
    for (i = 0; i < loop; i++) {
        if (scpr[ready] % timequantom == 0 || arr[ready][1] < 1) {
            scpr[ready] = 0;
            q[ready] = 0;
            for (k = 1; k < M; k++) {
                if (i >= arr[k][0] && k != ready){
                	q[k]++;
				}
            }
        }
        allprdone = 0;
        ready = 0;
        for (j = 1; j < M; j++) {
            if (i >=arr[j][0] && arr[j][1] >= 1) {
                if (ready == 0) {
                    ready = j;
                }else if (q[ready] < q[j]) {
                    ready = j;
                }
            }
            if (arr[j][1] < 1){
            	allprdone++;
			}
        }
        if (ready > 0) {
            arr[ready][1]--;
            output[ready][i] = 1;
            scpr[ready]++;
        }
        if (allprdone == M-1) {
            lastdone = i;
            break;
        }
    }
	ImprimirMatriz(lastdone,output);
}


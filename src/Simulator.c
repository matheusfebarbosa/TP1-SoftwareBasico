#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int REGISTER;

int ram[256];
REGISTER pc;
REGISTER ac = 0;
REGISTER rc;
REGISTER rx;

int loader(char *program, int loadPoint){
	FILE *f =  fopen(program,"r");
	char flag;

	pc = loadPoint;

	while(fscanf(f,"%c", &flag) == 1){
		if(flag == '!'){
			fscanf(f,"%d %d%*c", &ram[pc], &ram[pc+1]);
			pc+=2;
		}else if(flag == '*'){
			fscanf(f,"%d%*c", &ram[pc]);
			pc++;
		}
	}

	pc = loadPoint;

	return 0;
}

int interpreter(){
	int sb,fb;
	while(ram[pc]!=11){
		fb = ram[pc];
		sb = ram[pc+1];
		pc+=2;
		switch(fb){
			case 1:
				ac = ram[sb+pc]; 
				break;
			case 2:
				ram[sb+pc] = ac;
				break;
			case 3:
				ac += ram[sb+pc];
				break;
			case 4:
				ac -= ram[sb+pc];
				break;
			case 5:
				scanf("%d",&ram[sb+pc]);
				break;
			case 6:
				printf("%d\n", ram[sb+pc]);
				break;
			case 7:
				pc = sb+pc;
				break;
			case 8:
				if(ac>0){
					pc = sb+pc;	
				}
				break;
			case 9:
				if(ac<0){
					pc = sb+pc;	
				}
				break;
			case 10:
				if(ac==0){
					pc = sb+pc;	
				}
				break;
			case 11:
				return 0;
				break;
			case 12:
				rx = ram[sb+pc];
				break;
			case 13:
				ram[sb+pc] = rx;
				break;
			case 14:
				ac = ram[rx++];
				break;
			case 15:
				ram[rx++] = ac;
				break;
			case 16:
				rc = ram[sb+pc];
				break;
			case 17:
				rc = rc - 1;
				if(rc)
					pc = sb+pc;
				break;
			case 18:
				rx =  pc;
				pc =  sb + pc;
				break;
			case 19:
				pc = rx;
				break;
			case 20:
				ac = ram[ram[rx]];
				rx = rx + 1;
				break;
			case 21:
				ram[ram[rx]] = ac;
				rx = rx + 1;
				break;
			case 22:
				ram[rx] *= 2;
				ac = ram[rx];
				break;
			case 23:
				ram[rx] /= 2;
				ac = ram[rx];
				break;
			case 24:
				if(ac%2==0){
					pc = sb+pc;	
				}
				break;
		}
	}
	return 0;
}


int main(int argc, char *argv[]){

	if(loader(argv[1],atoi(argv[2]))){
		fprintf(stderr, "Erro no carregamento\n");
	}

	if(interpreter()){
		fprintf(stderr, "Erro ao executar o programa\n");
	}

	return 0;
}
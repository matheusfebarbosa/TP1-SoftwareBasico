#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int REGISTER;

int ram[1000];
REGISTER pc;
REGISTER ac = 0;

void loader(char *program, int loadPoint){
	FILE *f =  fopen(program,"r");

	pc = loadPoint;

	while(fscanf(f,"%d %d", &ram[pc], &ram[pc+1])==2){
		pc+=2;
	}

	pc = loadPoint;
}

void interpreter(){
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
		}
	}
}


int main(int argc, char *argv[]){

	loader(argv[1],atoi(argv[2]));

	interpreter();

	return 0;
}
#include <stdio.h>

#define IRBIAS_M ((4.50-0.03)/(254-0)*(1000))

int main(void){
	int a =0;
	a = (IRBIAS_M*100+30);
	printf("%f %d",IRBIAS_M,a);
	return 0;
}




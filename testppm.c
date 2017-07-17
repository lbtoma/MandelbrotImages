#include<stdio.h>
#include<math.h>

int main(){
	FILE *saida = fopen("test.ppm", "w");
	fprintf(saida, "P3\n1920 1080\n255\n");
	int i,j;
	for( i = 0; i < 1080; i++){
		for( j = 0; j < 1920; j++){
			fprintf(saida,"%3d %3d %3d ", (int)( (float)( (float)( i % ( j + 1) )/(1080) )*255 ) , (i*j)/(1080*1920/255), 0 );
		}
		fprintf(saida,"\n");
	}
	return 0;
}

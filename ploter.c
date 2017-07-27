/*

        This code plot the mandelbrot set in a ppm picture.

        The complex numbers will be represented by a bidimensional
    double precision array, the first element is the real part, And
    the second element is the imaginary part.

*/

#include<stdio.h>
#include<stdlib.h>

#define FULL_COLLOR 1024

double z[2];
double aux;
double c[2];

//  Function thats do the follow iteraction:
//     z = z^2 + c;
//  And returns the value of |z|^2.
double iteraction();

int main(){
    //default parameters
    unsigned int height = 1080;  //height of the picture in pixels
    unsigned int width = 1920;   //width of the picture in pixels
    unsigned int maxIteractions = 40;
    unsigned int color;
    unsigned int color2;
    double origin[2];     //origin of the picture
    double z0[2];
    double resolution = 500;    //resolution in pixels per unit
    double module;
    FILE *title = fopen("title","r");
    FILE *output = fopen("output.ppm","w");
    int readingChar = fgetc(title);
    int iRe, iIm, i; //counters
    origin[0] = -0.5;
    origin[1] = 0;
    z0[0] = 0;
    z0[1] = 0;

    while ( readingChar != EOF ){
        printf("%c", readingChar);
        readingChar = fgetc(title);
    }
    if( title != NULL )
        fclose( title );
    printf("\tRun with the default parameters?(y/n) : ");
    readingChar = getchar();
    if( readingChar != 'Y' && readingChar != 'y' ){
        fflush( stdin );
        printf("\t\tHeight (pixels) : ");
        scanf("%u", &height);
        fflush( stdin );
        printf("\t\tWidth (pixels) : ");
        scanf("%u", &width);
        fflush( stdin );
        printf("\t\tMax iteractions : ");
        scanf("%u", &maxIteractions);
        fflush( stdin );
        printf("\t\tOrigin Re : ");
        scanf("%lf", &origin[0] );
        fflush( stdin );
        printf("\t\tOrigin Im : ");
        scanf("%lf", &origin[1] );
        fflush( stdin );
        printf("\t\tResolution (pixels per unit) : ");
        scanf("%lf", &resolution );
        fflush( stdin );
        printf("\t\tZ0 Re : ");
        scanf("%lf", &z[0] );
        fflush( stdin );
        printf("\t\tZ0 Im : ");
        scanf("%lf", &z[1] );
    }

    printf("\n\tGenerating, this can take a while...");

    if( output != NULL ){
        fprintf(output, "P3\n%d %d\n%d\n", width, height, FULL_COLLOR );

        for( iIm = height/2; iIm > -((int)height)/2; iIm-- ){
            for(  iRe = -((int)width/2); iRe < ((int)width/2); iRe++  ){
                c[0] = ( (double)iRe + origin[0]*resolution )/(double)resolution;
                c[1] = ( (double)iIm + origin[1]*resolution )/(double)resolution;
                z[0] =  z0[0]*z0[0] - z0[1]*z0[1] + c[0];
                z[1] =  2*z0[0]*z0[1] + c[1];
                i = 1;
                module = z[0]*z[0] + z[1]*z[1];
                while( i < maxIteractions && module <= 4 ){
                    module = iteraction();
                    i++;
                    // printf("\nmod = %lf , zRe = %lf, zRe = %lf, cRe = %lf, cIm = %lf\n", module, z[0], z[1], c[0], c[1] );
                }
                color = (float)FULL_COLLOR*( ( (float)( maxIteractions - i ) )/(float)maxIteractions )*0.8;
                color2 = (float)FULL_COLLOR*( ( (float)( maxIteractions - i ) )/(float)maxIteractions )*( ( (float)i )/(float)maxIteractions );
                fprintf(output,"%3d %3d %3d ", color2 , color2 , color );
            }
            fprintf(output,"\n");
        }

        if( output != NULL )
            fclose(output);

        printf("\n\n\tDone!\n\n");
    }
    else{
        printf("\n\n\tERROR!\n\n");
    }
    return 0;
}

double iteraction(){
    aux = z[0]*z[0] - z[1]*z[1] + c[0]; //real
    z[1] = 2*z[0]*z[1] + c[1];           //Imaginary
    z[0] = aux;
    // printf("\n\tmod = %lf , zRe = %lf, zIm = %lf, cRe = %lf, cIm = %lf\n", z[0]*z[0] + z[1]*z[1], z[0], z[1], c[0], c[1] );
    return( z[0]*z[0] + z[1]*z[1] );     //squre of the module
}

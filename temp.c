#include <stdio.h>
#include <math.h>

#define M 640
#define N 480
#define pi 3.14159265358979323846264338

typedef struct
{
   double x ;
   double y ;
   double z ;
   double r, g, b;
} triple ;
triple e = { 0.50 , 0.50 , -1.00 } ; // the eye
triple g = { 0.00 , 1.25 , -0.50 } ; // the light
typedef struct
{
	triple c, h;
	double r;
}circle;
double dotp( triple t , triple u )
{
   return t.x * u.x + t.y * u.y + t.z * u.z ;
}
void diff( triple* t , triple u , triple v ) // t = u - v
{
   t->x = u.x - v.x ;
   t->y = u.y - v.y ;
   t->z = u.z - v.z ;
}
circle a[4];
void init()
{
   a[0].c.x =      0.50 ;
   a[0].c.y = -20000.00 ; // the floor
   a[0].c.z =      0.50 ;
   a[0].r   =  20000.25 ;
   a[0].h.r =    205    ; // color is Peru
   a[0].h.g =    133    ;
   a[0].h.b =     63    ;
   
   a[1].c.x =      0.50 ;
   a[1].c.y =      0.50 ;
   a[1].c.z =      0.50 ;
   a[1].r   =      0.25 ;
   a[1].h.r =      0    ; // color is Blue
   a[1].h.g =      0    ;
   a[1].h.b =    255    ;
   
   a[2].c.x =      1.00 ;
   a[2].c.y =      0.50 ;
   a[2].c.z =      1.00 ;
   a[2].r   =      0.25 ;
   a[2].h.r =      0    ; // color is Green
   a[2].h.g =    255    ;
   a[2].h.b =      0    ;
   
   a[3].c.x =      0.00 ;
   a[3].c.y =      0.75 ;
   a[3].c.z =      1.25 ;
   a[3].r   =      0.50 ;
   a[3].h.r =    255    ; // color is Red
   a[3].h.g =      0    ;
   a[3].h.b =      0    ;
}

//void drawline(


//main
int main(void)
{
   int rgb[N][M][3]; // red-green-blue for each pixel
   int y, x;
   
   FILE* fout ;
   init();
   
   for( y = 0 ; y < N ; y++ )
   {
      for( x = 0 ; x < M ; x++)
      {
         rgb[y][x][0] = 0; // red
         rgb[y][x][1] = 0; // green
         rgb[y][x][2] = 0; // blue
      }
   }
   /*
   //circles
  	for(int it = 0; it<sizeof(a)/sizeof(a[0]); it++){
  		for(int xval = 0; xval<M; xval++){	//xval is x here
			int yval = -1*(int)(sqrt(a[it].r*a[it].r-(xval-a[it].c.x)*(xval-a[it].c.x))+a[it].c.y);///////////////////////////////////////FIX THIS SO ITS NOT SUPER DUPER HUGE
			printf("r: %f\tcx: %f\tcy:%f\t\n", a[it].r, a[it].c.x, a[it].c.y);
			printf("%i, %i\n", xval, yval);
			if(yval>=0 && yval <N){
				rgb[yval][xval][0] = a[it].h.r;//red1;
				rgb[yval][xval][1] = a[it].h.g;//green1;
				rgb[yval][xval][2] = a[it].h.b;//blue1;
				
				//DRAWLINE
				int Bx1 = a[it].c.x;
				int Bx2 = xval;
				int By1 = a[it].c.y;
				int By2 = yval;

				double Btrials = 1000.0;
				double Bxslope = (Bx2-Bx1)/Btrials;
				double Byslope = (By2-By1)/Btrials;
				for (int iter = 0; iter < 1000; iter++){
					int curr_x = (int)(Bx1+Bxslope*iter);
					int curr_y = (int)(By1+Byslope*iter);
					if(curr_x>=0 && curr_x<M && curr_y>=0 && curr_y<N){
						rgb[curr_y][curr_x][0] = 255;//a[it].h.r;//red1;
						rgb[curr_y][curr_x][1] = 255;//a[it].h.g;//green1;
						rgb[curr_y][curr_x][2] = 255;//a[it].h.b;//blue1;
					}
				}
				//DRAWLINE
				
			}
		}
  	}*/
  	
  	double sinx = sin(pi/4);
  	printf("%f\n", sinx);
   
   
	//make circles

   /*fout = fopen( "step1.ppm" , "w" ) ;
   
   fprintf( fout , "P3\n" ) ;
   fprintf( fout , "%d %d\n" , M , N ) ;
   fprintf( fout , "255\n" ) ;
   
   for( y = 0 ; y < N ; y++ )
   {
      for( x = 0 ; x < M ; x++)
      {
         fprintf( fout , "%d %d %d\n" ,
          rgb[y][x][0] , rgb[y][x][1] , rgb[y][x][2] ) ;
      }
   }
   fclose( fout ) ;
   */
   return 0 ;
}

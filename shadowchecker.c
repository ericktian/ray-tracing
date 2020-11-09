#include <stdio.h>
#include <math.h>
#include <stdbool.h>

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
   int sizea = sizeof(a)/sizeof(a[0]);
   
   FILE* fout ;
   init();
   
   for( y = 0 ; y < N ; y++ )
   {
      for( x = 0 ; x < M ; x++)
      {
         rgb[y][x][0] = 0; // red
         rgb[y][x][1] = 0; // green
         rgb[y][x][2] = 0; // blue
         
         double mint = -1.0; //placeholder for the minimum value of t
         
         for(int circ = 0; circ<sizea; circ++){ //iterates through circles
         
             //-----check for if T is a minimum-----
             //make variables for easier math
             double dz = e.z-a[circ].c.z;
             double dy = e.y-a[circ].c.y;
             double dx = e.x-a[circ].c.x;
             
             double px = (x+.5)/640;        //location on the plane with z=0, .5 is for rounding error
             double py = 1.0 - (y+.5)/640;
             double pz = 0;
             
             //unnormalized
             double rx2 = px-e.x;            //vector from eye to the plane z=0
             double ry2 = py-e.y;
             double rz2 = pz-e.z;
             
             //normalize
             double mag = sqrt(rx2*rx2 + ry2*ry2 + rz2*rz2);
             double rx = rx2/mag;            //vector from eye to the plane z=0
             double ry = ry2/mag;
             double rz = rz2/mag;
             
             double r = a[circ].r;            //radius
             
             //quadratic equation variables
             double avar = 1.0;                //technically rx^2+ry^2+rz^2 but that's just 1
             double bvar = 2*(rx*dx + ry*dy + rz*dz);
             double cvar = dx*dx + dy*dy + dz*dz - r*r;
             
             //-----finding t (- since it is minimum)-----
             //check if there's a solution
             double determinate = bvar*bvar-4*avar*cvar;
             
             if( determinate >=0 ){
                  double t = ( -bvar - sqrt(determinate)) / (2*avar);
                                       
                  if(mint==-1.0 && t>0){
                      mint = t;    //if this is the first sphere
                  }
                  if(t<=mint && t>0){
                      mint = t;            //update the minimum value of t
                      //printf("mint: %f\n", mint);
                      
           /*          rgb[y][x][0] = a[circ].h.r; //change color of pixel
                     rgb[y][x][1] = a[circ].h.g;
                     rgb[y][x][2] = a[circ].h.b;
             */        
                     
                     
                     //----------SHADOW----------
                     //x y and z values of the point on the sphere
                     double pxnew = e.x + mint*rx;//(x+.5)/640;        //location on the plane with z=0, .5 is for rounding error
                     double pynew = e.y + mint*ry;//1.0 - (y+.5)/640;
                     double pznew = e.z + mint*rz;//0;
                     
                         
                     //unnormalized
                     double rx2new = g.x-pxnew;			//vector from eye to the plane z=0
							double ry2new = g.y-pynew;
							double rz2new = g.z-pznew;
                     
                     //normalize
                     double magnew = sqrt(rx2new*rx2new + ry2new*ry2new + rz2new*rz2new);
                     double rxnew = rx2new/magnew;            //vector from eye to the plane z=0
                     double rynew = ry2new/magnew;
                     double rznew = rz2new/magnew;
                     
                     
                    
                 		
                 		//alcohol
                 		double unnormalx = (pxnew-a[circ].c.x);
                 		double unnormaly = (pynew-a[circ].c.y);
                 		double unnormalz = (pznew-a[circ].c.z);
                 		double normalmag = sqrt(unnormalx*unnormalx + unnormaly*unnormaly + unnormalz*unnormalz);
                 		double normalx = unnormalx/normalmag;
                 		double normaly = unnormaly/normalmag;
                 		double normalz = unnormalz/normalmag;
                     
                     rgb[y][x][0] = a[circ].h.r * ((normalx*rxnew + normaly*rynew + normalz*rznew)*.5 + .5); //change color of pixel using dot product and formula
                     rgb[y][x][1] = a[circ].h.g * ((normalx*rxnew + normaly*rynew + normalz*rznew)*.5 + .5);
                     rgb[y][x][2] = a[circ].h.b * ((normalx*rxnew + normaly*rynew + normalz*rznew)*.5 + .5);
                     
                     
                     
                     
                     for(int circ2 = 0; circ2<sizea; circ2++){ //iterates through circles to check which one crosses the light source
                      if (circ2==circ) continue;
      //curently all in shadow, might need to make the x y z coords
      
                      //-----check for if there is a T-----
                      //make variables for easier math
                      //also renamed a bunch of variables to 2 or new at the end
                      double dznew = pznew-a[circ2].c.z;
                      double dynew = pynew-a[circ2].c.y;
                      double dxnew = pxnew-a[circ2].c.x;
                      
                      double rnew = a[circ2].r;            //radius
                      
                      //quadratic equation variables
                      double avarnew = 1.0;                //technically rx^2+ry^2+rz^2 but that's just 1
                      double bvarnew = 2*(rxnew*dxnew + rynew*dynew + rznew*dznew);
                      double cvarnew = dxnew*dxnew + dynew*dynew + dznew*dznew - rnew*rnew;
                      
                      //-----finding t (- since it is minimum)-----
                      //check if there's a solution
                      double determinatenew = bvarnew*bvarnew-4*avarnew*cvarnew;
                      
                      //also might need to check if the point where the shadow is is slightly above the sphere, so the distance > 0.1 or smth
                      if( determinatenew >=0 ){    //-----FOUND A SOLUTION! So we make it in shadow-----
                          double checkifpositive = ( -bvarnew - sqrt(determinatenew)) / (2*avarnew);    //but first check if this is positive so that it doesnt intersect behind the sphere
                          if(checkifpositive>0){ //&& < mag maybe
                          
                          
                          		
                          
                              rgb[y][x][0] = a[circ].h.r * .5; //change color of pixel
                              rgb[y][x][1] = a[circ].h.g * .5;
                              rgb[y][x][2] = a[circ].h.b * .5;
                              
                              
                              
                              
                              
                              
                              break;
                          }
                        }
                     }
                     
                     
                     /////CHECKER
                     if (circ==0){
                     	int first = (int)(pxnew*10);
                     	int second = (int)(pznew*10);
                     	if(pxnew<0)first--;
                     	if((first+second) % 2 == 0){
                     		rgb[y][x][0]*=.3;
                     		rgb[y][x][1]*=.3;
                     		rgb[y][x][2]*=.3;
                     	}
                     }
                     
                 }
             }
           }
      }
   }
   
   
   
   
   
    //make circles

   fout = fopen( "shadowchecker.ppm" , "w" ) ;
   
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
   
   return 0 ;
}


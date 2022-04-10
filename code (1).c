#include <iostream>
#include <cmath>
using namespace std;
int main()
{ float rf[135][129],rainfall;
float lo[135], la[129] ;
int i, j, k, year, year1, month, date, nd ;
FILE *fptr1,*fptr2;
int nd1[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31} ;
int nd2[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31} ;
year = 2000;
printf("Year = %d",year) ;
fptr1 = fopen("Rainfall_ind2000_rfp25.grd","rb"); // input file
fptr2 = fopen("Rainfall_ind2000_rfp25.prt","w");
if(fptr1==NULL) { printf("Can't open file"); return 0; }
if(fptr2==NULL) { printf("Can't open file"); return 0; }
for(j=0 ; j < 135 ; j++) lo[j] = 66.5 + j * 0.25 ;
for(j=0 ; j < 129 ; j++) la[j] = 6.5 + j * 0.25 ;
year1 = year / 4 ;
year1 = year1 * 4 ;

double temprainfall=0;
double yearavg=0;
int cou=1;
double standdev=0;
for(month=6 ; month < 10 ; month++)
    { nd = nd1[month] ;
    if(year == year1)nd = nd2[month] ;
        for(date=1 ; date <= nd ; date++)
            { fprintf(fptr2,"\n%02d%02d%04d",date,month,year);
            for(j=0 ; j < 135 ; j++)fprintf(fptr2,"%7.2f",lo[j]) ;
                for(i=0 ; i < 129 ; i++)
                    { fprintf(fptr2,"\n%8.2f",la[i]) ;
                    for(j=0 ; j < 135 ; j++)
                        { if(fread(&rainfall,sizeof(rainfall),1,fptr1) != 1) return 0 ;
                        rf[j][i] = rainfall ;
                        fprintf(fptr2,"%7.1f",rf[j][i] );
                        if (rainfall>0){
                        cou=cou+1;
                        temprainfall =temprainfall + rainfall;
                        }
                        }
                    }
                printf("%4d %02d %02d %f \n",year,month,date,temprainfall/cou);
                yearavg = yearavg + temprainfall/cou;
                //standdev = abs(standdev+ (yearavg-temprainfall)*(yearavg-temprainfall));
                //printf("%10d \n",standdev);
                temprainfall=0;
                cou=1;
                }

    }
yearavg= yearavg/122;
printf("Value of Ravg = %f\n",yearavg);
//standdev = standdev/365;
//standdev = pow(standdev,0.5);
//printf("%10d \n",standdev);
fclose(fptr1);
fclose(fptr2);
printf("Year = %d",year) ;
return 0;
} /* end of main */
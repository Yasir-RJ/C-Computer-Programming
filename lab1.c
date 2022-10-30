// Lab1: Landing on the moon
// by Yasir Riyadh Jabbar / KTH
#include <stdio.h>

int main(){
 float Height=250.0,Velocity=-25.0;
 int Time=0,fual=0,branslet=500;

 printf("Lunar decent challenge!\n");
 printf("You will pilot a lunar decent the last 250m.\n");
 printf("Each turn represent 1-second decent time.\n");
 printf("Set the throttle for each turn (0-100)\n\n");
 printf("Time Height Velocity Branslet Throttle?\n");

 while(Height>0){
    printf("%3d %6.1f   %5.1f     %d    ",Time,Height,Velocity,branslet);
    scanf("%d",&fual);
    Height=Height+Velocity+(0.1*fual-1.5)*0.5;
    Velocity=Velocity+(0.1*fual-1.5);
    branslet=branslet-fual;
    if(branslet<=0) break;
    Time++;
 }

 if (Velocity >= -2)
    printf("The landing is Successful at %.1f m/s\n",Velocity);
 else
    printf("FAILED! Crash landing at %.1f m/s\n",Velocity);
 return 0;
}

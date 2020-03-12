#include <stdio.h>
#include <bcm_host.h>

int main(){
  short* peripheral_address = bcm_host_get_peripheral_address();
  while(true){
    printf("pls typing on or off");

    char buff[256];
    scanf("%s", buff);

    short pin_val;

    if(buff == "on"){
      pin_val = 0x02000000;
    }
    else{
      pin_val = 0x00000000;
    }

    *peripheral_address = pin_val;
  }
}

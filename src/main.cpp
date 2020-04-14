#include <stdio.h>
#include "gpio.hpp"

int main(){
  Gpio* gpio = new Gpio();

  while(true){
    printf("pls typing on or off\n");

    char buff[256];
    scanf("%s", buff);

    if(strcmp(buff, "on") == 0){
      gpio->set_pin(2);
      //gpio->set_fsel(2, Gpio::FunctionSelect::IN);
    }
    else{
      gpio->clear_pin(2);
      //gpio->set_fsel(2, Gpio::FunctionSelect::OUT);
    }
  }

  return 0;
}

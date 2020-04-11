#include <stdio.h>
#include "gpio.hpp"

int main(){
  Gpio* gpio = new Gpio();

  while(true){
    printf("pls typing on or off\n");

    char buff[256];
    scanf("%s", buff);

    short pin_val;

    if(strcmp(buff, "on") == 0){
      gpio->set_pin(2, Gpio::FunctionSelect::IN);
    }
    else{
      gpio->set_pin(2, Gpio::FunctionSelect::OUT);
    }
  }

  return 0;
}

#include <cstring>
#include <cstdio>
#include "gpio.h"

int main() {
  Gpio* g = new Gpio();
  g->set_fsel(2, Gpio::FunctionSelect::OUT);
  while(true){
    printf("pls typing on or off\n");

    char buff[256];
    scanf("%s", buff);

    if(strcmp(buff, "on") == 0){
      g->set_pin(2);
    }
    else{
      g->clear_pin(2);
    }
  }
  delete g;

  return 0;
}

#include <cstring>
#include <cstdio>
#include <unistd.h>
#include "gpio.hpp"

int main() {
  Gpio* g = new Gpio();
  while(true){
    printf("pls typing on or off\n");

    char buff[256];
    scanf("%s", buff);

    if(strcmp(buff, "on") == 0){
      g->set_pin(2);
      g->set_pin(21);
    }
    else{
      g->clear_pin(2);
      g->clear_pin(21);
    }
  }
  delete g;

  return 0;
}

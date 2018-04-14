#include <iostream>
#include "window.h"

int main(void)
{
  Window window(1700, 1200, "window");
  while(window.Open())
  {
    window.Render();
    window.Update();
  }
  window.DestroyWindow();
}

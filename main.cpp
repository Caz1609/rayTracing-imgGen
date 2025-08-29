#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"
#include "funcs.h"
/*
int main(){
   int w, h, c, a;
   std::cout << "w: ";
   std::cin >> w;
   std::cout << "h: ";
   std::cin >> h;
   std::cout << "c: ";
   std::cin >> c;
   std::cout << "a: ";
   std::cin >> a;
   img i1(w, h, c);
   img_gen(i1, a);
}
*/

int main(){
   img i1(1000, 1000, 3);
   test_write_img(i1);
}

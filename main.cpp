#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"
#include "funcs.h"

int main(){
   Plane p(Ray(42, 6, 10), Ray(20, 6, 11), Ray(42, 16, 12), Color(0, 255, 0), 10);
   Img i1(1000, 1000, 3);
   test_plane_img(i1, p);
}

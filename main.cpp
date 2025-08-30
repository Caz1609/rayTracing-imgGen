#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"
#include "funcs.h"

int main(){
   Plane p(Ray(100, 100, 5), Ray(200, 300, 5), Ray(100, 200, 5), Color(0, 255, 0));
   Img i1(1000, 1000, 3);
   test_plane_img(i1, p);
}

#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"
#include "funcs.h"

int main(){
   Img i1(4000, 3000, 3);
   Sphere s1(Ray(2000, 1500, 5000), 2000);
   test_sphere_img(i1, s1);
}

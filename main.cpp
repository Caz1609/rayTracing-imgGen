#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"
#include "funcs.h"

int main(){
   Img i1(4000, 3000, 3);
   Color c1(70, 130, 180), c2(255, 255, 0), c3(109, 116, 145); 
   Sphere s1(Ray(700, 700, 7000), 1100, c2), s2 (Ray(-100, 700, 6400), 300, c1), s3(Ray(1550, 800, 7400), 1800, c3);
   Scenery scene(s1);
   scene.Insert(s2);
   scene.Insert(s3);
   test_scenery_img(i1, scene);
}

//Code to generate custom scenery//

   /* int n=100, x, y, z, r, red, green, blue;
   while(n>10){
      std::cout << "How many spheres would you like to insert(At most 10 cus skill issue): ";
      std::cin >> n;
   }
   Scenery s(n);
   while(n--){
      std::cout << "Enter coordinates and radius with space separation: ";
      std::cin >> x >> y >> z >> r;
      std::cout << "Enter color of sphere as RGB values with space separation: ";
      std::cin >> red >> green >> blue;
      z += 5000;
      s.Insert(Sphere(Ray(x, y, z), r, Color(red, green, blue)));
   }

   test_scenery_img(i1, s); */


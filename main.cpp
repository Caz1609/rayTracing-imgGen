#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"
#include "funcs.h"

int main(){
   Img i1(4000, 3000, 3);
   Color c1(70, 130, 180), c2(255, 255, 0), c3(109, 116, 145), c4(21, 201, 249), c5(117, 239, 183), c6(215, 88, 18); 
   Sphere s1(Ray(700, 700, 7000), 1100, c2), s2 (Ray(-100, 700, 6400), 300, c1), s3(Ray(1550, 800, 7400), 1800, c3);
   // Sphere s1(Ray(-700, 500, 5900), 1300, c4), s2(Ray(500, -1222, 6200), 1600, c5), s3(Ray(1500, 1500, 6000), 800, c5), s4(Ray(0, 0, 5000), 5000, Color(0, 255, 255));
   Light l1(Ray(-2000, 0, 6000), 0.5), l2(Ray(2000, -100, 5400), 0.7), l3(Ray(0, 0, 0), 0.1);
   Scenery scene(s1);
   scene.Insert(s2);
   scene.Insert(s3);
   // scene.Insert(s4);
   scene.Insert(l1);
   // scene.Insert(l2);
   // scene.Insert(l3);
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


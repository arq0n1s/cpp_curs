#include <unordered_map>
#include <iostream>

int main () {
 
   std::unordered_map <int, int> umap;
   //  заполняем таблицу 2000 элементами - парами чисел 
   for (int i = 0; i < 2000; i++) {
      //  выводим число элементов и число сегментов на каждой итерации
      std::cout << umap.size() << " " << umap.bucket_count() << std::endl;
      umap.insert({i, i+1});
   }
}
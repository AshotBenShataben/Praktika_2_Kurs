#include <iostream>
#include <vector>
 
using namespace std;
 
class RandomNumberGenerator
{
   protected:
 
      unsigned int   init_seed;  // Начальное случайное значение
      unsigned int   cur_seed;   // Текущее случайное значение
      unsigned int   num_draws;  //Размерность
 
   public:
 
      RandomNumberGenerator(unsigned int _num_draws,unsigned int _init_seed) : num_draws(_num_draws), init_seed(_init_seed), cur_seed(_init_seed)
      {
      };
   
      virtual ~RandomNumberGenerator()
      {
      };
 
      virtual unsigned int get_random_seed() const
      {
         return cur_seed;
      }
   
      virtual void set_random_seed(unsigned int _seed)
      {
         cur_seed = _seed;
      }
   
      virtual void reset_random_seed()
      {
         cur_seed = init_seed;
      }
   
      virtual void set_num_draws(unsigned int _num_draws)
      {
         num_draws = _num_draws;
      }
 
      // получить случайное целое число
      virtual unsigned int  get_random_integer() = 0;
 
      // Заполняет вектор однородными случайными величинами на открытом интервале (0,1)
      virtual void   get_uniform_draws(std::vector<double>& draws) = 0;
};
 
class LinearCongruentialGenerator : public RandomNumberGenerator
{
   private:
      
      double   max_multiplier;
 
   public:
   
               LinearCongruentialGenerator(unsigned int _num_draws,unsigned int _init_seed = 1);
      virtual ~LinearCongruentialGenerator() 
               {
               };
 
      virtual unsigned int get_random_integer();
      virtual void         get_uniform_draws(std::vector<double>& draws);
};
                     
const unsigned int   a = 16807;       // 7^5
const unsigned int   m = 2147483647;  // 2^32 - 1 (and thus prime)
 
// Константы алгоритма Шраге
 
const unsigned int   q = 127773;
const unsigned int   r = 2836;
 
// Конструктор параметров
LinearCongruentialGenerator::LinearCongruentialGenerator(unsigned int _num_draws,unsigned int _init_seed) : RandomNumberGenerator(_num_draws,_init_seed)
{
   if (!_init_seed)
   {
      init_seed = 1;
      cur_seed  = 1;
   }
 
   max_multiplier = 1.0 / (1.0 + (m - 1));
}
 
// Получает случайное целое число без знака
unsigned int LinearCongruentialGenerator::get_random_integer()
{
   unsigned int   kk  = 0;
 
   kk = cur_seed / q;
   
   cur_seed = a * (cur_seed - kk * q) - r * kk;
 
   if (cur_seed < 0)
   {
      cur_seed += m;
   }
 
   return cur_seed;
}
 
// Создайте вектор равномерных участков между (0,1)
void LinearCongruentialGenerator::get_uniform_draws(std::vector<double>& draws)
{
   for (unsigned int ii = 0; ii < num_draws; ++ii)
   {
      draws[ii] = get_random_integer() * max_multiplier;
   }
}
 
int main()
{                 
   unsigned int   init_seed = 1;
   unsigned int   num_draws = 20;
 
   vector<double> random_draws(num_draws,0.0);
 
   // Cоздать случайные формы
   // открыть интервал (0,1) 
   LinearCongruentialGenerator   lcg(num_draws,init_seed);
 
   lcg.get_uniform_draws(random_draws);
 
   // вывод случайных чисел
   for (unsigned int ii = 1; ii < num_draws; ++ii)
   {
      cout << random_draws[ii] << endl;
   }
 
   system("pause");
 
   return 0;
}
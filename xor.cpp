// Попытка реализации нейросети для решения XOR. Код - ужасен. 
// {x1,x2} -> {input neurons} -> F(sum  Wi*Xi) -> {hidden layer} -> F(sum Wj*yj) -> OUT. 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>

using Vec = std::vector<float>;

class Neuron;

class Link{
public:
  float weight;
  Neuron *neuron;
  Link(float weight,Neuron *neuron):weight(weight),neuron(neuron){}
  Link& operator=(const Link&) = default;
  ~Link(){}
};

class Neuron{
public:
  std::vector<Link> links;
  float power = 0;
  Neuron(const decltype(links) & links = {}):links(links){}
  ~Neuron(){}
  void reset() { power = 0; }
};

class Neuronet{
  std::function<float(float)> activation_func;
  std::vector<std::vector<Neuron>> net; 
  Neuron out;
public:
  typedef decltype(activation_func) func_t;
  Neuronet(func_t func):activation_func(func){
    net.push_back({Neuron(),Neuron()});// IN
    net.push_back({Neuron(),Neuron()});// hidden layer
    net[0][0].links = {Link(1,&net[1][0]),Link(-1,&net[1][1])};// считается, что нейросеть уже 
    //обучена. Таблица весов - [[1,-1],[-1,1]]
    net[0][1].links = {Link(-1,&net[1][0]),Link(1,&net[1][1])};
    net[1][0].links = {Link(1,&out)}; // OUT.
    net[1][1].links = net[1][0].links;
  }
  void setIn(const std::vector<float> &signals){
    for(uint32_t i = 0; i < signals.size(); ++ i ){
      net[0][i].power = signals[i];
    }
  }
  float solve(){
    uint32_t it = 0;
    for(auto &layer : net){ // проходим по каждому слою
      ++it;
      for(auto &neuron : layer){
        for(auto &link : neuron.links){
          link.neuron->power += neuron.power * link.weight; // "посылаем сигналы" по Link 
          //к нейронам на следующих слоях.
        }
      }
      if(it >= net.size()) { continue; } // тк OUT отсутсвует в векторе.
      for(auto &neuron : net[it]){
        neuron.power = activation_func(neuron.power);
      }
    }
    return activation_func(out.power); // применяем функцию к результате, тк в процессе итерации
    //этого сделано не было.
  }
  void reset() {
    for(auto&x:net){
      for(auto&y:x){
        y.reset();
      }
    }
    out.reset();
  }
  virtual ~Neuronet(){}

};
int main(int argc, char *argv[])
{
  Neuronet net([](float a){ return a>=0.5?1:0; } );
  net.setIn({1,1});
  std::wcout << L"1 xor 1 = " << net.solve() << std::endl;
  net.reset();
  net.setIn({1,0});
  std::wcout << L"1 xor 0 = " << net.solve() << std::endl;
  net.reset();
  net.setIn({0,1});
  std::wcout << L"0 xor 1 = " << net.solve() << std::endl;
  net.reset();
  net.setIn({0,0});
  std::wcout << L"0 xor 0 = " << net.solve() << std::endl;
  return 0;
}


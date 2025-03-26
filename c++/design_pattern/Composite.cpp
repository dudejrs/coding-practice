#include <array>
#include <iostream>
#include <numeric>

using namespace std;

namespace ArrayBasedAttribute {

class BadCaseCreature {
  int strength, agility, intelligence;

 public:
  int sum() const { return strength + agility + intelligence; }

  double average() const { return sum() / 3; }

  int max() const { return ::max(::max(strength, agility), intelligence); }
};

class GoodCaseCreature {
  enum Abilites { str, agl, intl, count };

  array<int, count> abillites;

 public:
  GoodCaseCreature(int strength, int agility, int intelligence) {
    abillites[str] = strength;
    abillites[agl] = agility;
    abillites[intl] = intelligence;
  }

  int sum() const { return accumulate(begin(abillites), end(abillites), 0); }

  double average() const { return sum() / (double)count; }

  int max() const { return *max_element(begin(abillites), end(abillites)); }
};

void main() {
  GoodCaseCreature creature1{1, 0, 5};
  cout << creature1.max() << endl;
}
};  // namespace ArrayBasedAttribute

namespace Composite {

struct GraphicObject {
  virtual void draw() = 0;
};

struct Circle : GraphicObject {
  void draw() override { cout << "Circle" << endl; }
};

struct Group : GraphicObject {
  vector<GraphicObject*> objects;
  string name;

  Group(const string& name) : name(name) {}

  void draw() override {
    cout << "Group <" << name << "> contians : ";
    for (auto& o : objects) {
      o->draw();
    }
  }
};

void main() {
  Group root("root");
  Circle c1, c2;
  root.objects.push_back(&c1);

  Group subgroup("sub");
  subgroup.objects.push_back(&c2);
  root.objects.push_back(&subgroup);

  root.draw();
}

};  // namespace Composite

namespace TamplateBasedComposite {

// 1. 개별객체와 컬렉션 객체 모두에 동일한 인터페이스를 사용가능하도록 template
// method

template <typename Self>
struct NeuronBase;
struct Neuron;

template <typename Self>
struct NeuronBase {
  template <typename T>
  void connect_to(T& ohter);
};

struct Neuron : NeuronBase<Neuron> {
  vector<Neuron*> in, out;
  unsigned int id;

  Neuron() {
    static int id = 1;
    this->id = id++;
  }

  Neuron* begin();
  Neuron* end();
};

struct NeuronLayer : vector<Neuron>, NeuronBase<NeuronLayer> {
  NeuronLayer(int count) {
    while (count-- > 0) emplace_back(Neuron{});
  }
};

template <typename Self>
template <typename T>
void NeuronBase<Self>::connect_to(T& other) {
  for (Neuron& from : *static_cast<Self*>(this)) {
    for (Neuron& to : other) {
      from.out.push_back(&to);
      to.in.push_back(&from);
    }
  }
}

Neuron* Neuron::begin() { return this; }
Neuron* Neuron::end() { return this + 1; }

void main() {
  Neuron n1, n2;
  NeuronLayer layer1(0), layer2(0);
  n1.connect_to(n2);
  n1.connect_to(layer1);
  layer1.connect_to(n1);
  layer1.connect_to(layer2);
}

};  // namespace TamplateBasedComposite

int main(void) {
  ArrayBasedAttribute::main();
  Composite::main();
  TamplateBasedComposite::main();

  return 0;
}
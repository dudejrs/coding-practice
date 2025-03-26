#include <iostream>
#include <stack>
#include <vector>

using namespace std;

namespace CollectionsMemento {

class Memento {
  int balance;

 public:
  Memento(const int balance) : balance(balance) {};

  friend class BankAccount;
};

class BankAccount {
  int balance;
  vector<shared_ptr<Memento>> changes;
  int current;

 public:
  explicit BankAccount(const int balance) : balance(balance), current(0) {
    changes.emplace_back(make_shared<Memento>(balance));
  }

  shared_ptr<Memento> deposit(int amount) {
    balance += amount;
    auto m = make_shared<Memento>(balance);
    changes.push_back(m);
    current++;
    return m;
  }

  void restore(const shared_ptr<Memento>& m) {
    if (m) {
      balance = m->balance;
      changes.push_back(m);
      current = changes.size() - 1;
    }
  }

  shared_ptr<Memento> undo() {
    if (current <= 0) return {};

    --current;
    auto m = changes[current];
    balance = m->balance;
    return m;
  }

  friend ostream& operator<<(ostream& os, const BankAccount& obj) {
    return os << obj.balance;
  }
};

void main(void) {
  cout << "[CollectionsMemento]" << endl;
  BankAccount ba(10000);
  ba.deposit(5000);
  cout << ba << endl;
  ba.undo();
  cout << ba << endl;
  cout << endl;
}
}  // namespace CollectionsMemento

namespace NestedClassMemento {

class Originator {
  int value;

 public:
  class Memento {
    int val;

   public:
    Memento(const int val) : val(val) {}

    friend class CareTaker;
    friend class Originator;
  };

  Originator(const int& value) : value(value) {}

  void set_value(const int& val) { this->value = val; };

  void restore(shared_ptr<Memento>& m) { this->value = m->val; }

  shared_ptr<Memento> save() { return make_shared<Memento>(value); }

  friend ostream& operator<<(ostream& os, Originator& origin) {
    return os << origin.value;
  }
};

class CareTaker {
  typedef shared_ptr<Originator::Memento> Memento;

  Originator& origin;
  stack<Memento> history;

 public:
  CareTaker(Originator& origin) : origin(origin) { save(); }

  void undo() {
    if (history.size() > 0) {
      Memento m = history.top();
      origin.restore(m);
      history.pop();
    }
  }

  void save() {
    Memento m = origin.save();
    history.push(m);
  }
};

void main(void) {
  cout << "[NestedMemento]" << endl;
  Originator origin(0);
  CareTaker ct(origin);
  cout << origin << endl;
  origin.set_value(1);
  ct.save();
  origin.set_value(2);
  ct.undo();
  cout << origin << endl;
  ct.undo();
  cout << origin << endl;

  cout << endl;
}
}  // namespace NestedClassMemento

namespace HierarchicalMemento {

struct CareTaker;
struct ConcreteMemento;

struct Originator {
  virtual void save() = 0;
};

struct Memento {
  virtual void restore() = 0;
};

struct CareTaker {
  void undo() {
    if (history.size() > 0) {
      Memento* m = history.top();
      m->restore();
      history.pop();
    }
  }
  void save(Memento* m) { history.push(m); }

 private:
  stack<Memento*> history;
};

struct ConcreteOriginator : public Originator {
  ConcreteOriginator(const int& value, CareTaker& ct) : value(value), ct(ct) {}
  void save() override;

  void set_value(const int& value) { this->value = value; }

 private:
  int value;
  CareTaker& ct;

  friend ostream& operator<<(ostream& os, ConcreteOriginator& origin) {
    return os << origin.value;
  }
  friend class Memento;
};

struct ConcreteMemento : public Memento {
  ConcreteMemento(ConcreteOriginator* origin, const int& value)
      : origin(origin), value(value) {}

  void restore() override { origin->set_value(value); }

 private:
  const int value;
  ConcreteOriginator* origin;
};

void ConcreteOriginator::save() {
  Memento* m = new ConcreteMemento(this, value);
  ct.save(m);
}

void main(void) {
  cout << "[HierarchicalMemento]" << endl;

  CareTaker ct;
  ConcreteOriginator origin1(0, ct);
  ConcreteOriginator origin2(10, ct);

  origin1.set_value(1);
  origin1.save();  // 1
  origin2.set_value(9);
  origin1.set_value(2);
  origin1.save();  // 2
  origin2.save();  // 9
  origin2.set_value(8);
  origin1.set_value(3);
  origin2.save();  // 8
  ct.undo();
  cout << origin1 << ',' << origin2 << endl;
  ct.undo();
  cout << origin1 << ',' << origin2 << endl;
  ct.undo();
  cout << origin1 << ',' << origin2 << endl;
  ct.undo();
  cout << origin1 << ',' << origin2 << endl;

  cout << endl;
}
}  // namespace HierarchicalMemento

int main(void) {
  CollectionsMemento::main();
  NestedClassMemento::main();
  HierarchicalMemento::main();

  return 0;
}
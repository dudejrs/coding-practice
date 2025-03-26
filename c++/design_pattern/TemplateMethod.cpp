#include <functional>
#include <iostream>

using namespace std;

namespace TemplateMethod {

class Game {
 public:
  explicit Game(const int number_of_players)
      : number_of_players(number_of_players) {}

  void run() {
    start();
    while (!have_winner()) take_turn();

    cout << "Player " << get_winner() << " wins" << endl;
  }

 protected:
  int current_player = 0;
  int number_of_players;
  virtual void start() = 0;
  virtual bool have_winner() = 0;
  virtual void take_turn() = 0;
  virtual int get_winner() = 0;
};

class Chess : public Game {
 public:
  explicit Chess() : Game(2) {}

 protected:
  void start() override { cout << "Game started" << endl; }
  bool have_winner() override { return turns == max_turns; }

  void take_turn() override {
    cout << "Turn " << turns << " taken by Player " << current_player << endl;
    turns++;
    current_player = (current_player + 1) % number_of_players;
  }
  int get_winner() override { return current_player; }

 private:
  int turns{0}, max_turns{10};
};

void main(void) {
  cout << "[TemplateMethod]" << endl;
  Chess cs;
  cs.run();
  cout << endl;
}
}  // namespace TemplateMethod

namespace FunctionalTemplateMethod {

struct Customer {
  Customer(int id) : id(id), name("Bob"), balance(12345) {}

  int id;
  string name;
  int balance;
};

struct Database {
  static Customer* get_customer(int id) { return new Customer(id); }
};

struct OnlineBanking {
  OnlineBanking(function<void(Customer*)> f) : make_customer_happy(f) {}

  void processCustomer(int id) {
    Customer* c = Database::get_customer(id);
    make_customer_happy(c);
  }

 private:
  function<void(Customer*)> make_customer_happy;
};

void main(void) {
  cout << "[FunctionalTemplateMethod]" << endl;

  OnlineBanking hello_banking(
      [](Customer* c) { cout << "Hello " << c->name << endl; });
  hello_banking.processCustomer(1234);

  OnlineBanking deposit_banking([](Customer* c) {
    c->balance += 1000000000;
    cout << "Now your Balance is " << c->balance << endl;
  });

  deposit_banking.processCustomer(1234);

  cout << endl;
}
}  // namespace FunctionalTemplateMethod

int main(void) {
  TemplateMethod::main();
  FunctionalTemplateMethod::main();
}

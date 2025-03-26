#include <boost/signals2.hpp>
#include <initializer_list>
#include <iostream>
#include <string>

using namespace std;

namespace HandlerChain {

struct Request {
  string name;
  Request(const string& name) : name(name) {}
};

struct Handler {
  virtual void set_next(Handler* next) = 0;
  virtual void handle(Request& request) = 0;
};

struct BaseHandler : Handler {
  void set_next(Handler* next) override { this->next = next; };
  void handle(Request& request) override {
    if (next)
      next->handle(request);
    else
      cout << "BaseHandler handling the " << request.name << endl;
  };

 protected:
  Handler* next = nullptr;
};

struct ConcreteHandler : public BaseHandler {
  ConcreteHandler(const string& name) : BaseHandler(), name(name) {}

  bool can_handle(const Request& request) { return true; }

  void handle(Request& request) override {
    if (can_handle(request))
      cout << "[" << name << "]" << " : handling the " << request.name << endl;
    BaseHandler::handle(request);
  };

 private:
  string name;
};

void main() {
  Request r1("request 1");

  Handler* h1 = new ConcreteHandler("Handler 1");
  Handler* h2 = new ConcreteHandler("Handler 2");
  Handler* h3 = new ConcreteHandler("Handler 3");

  h1->set_next(h2);
  h2->set_next(h3);

  h1->handle(r1);
}
};  // namespace HandlerChain

namespace PointerChain {

struct Creature {
  string name;
  int attack, defense;
};

class CreatureModifier {
  CreatureModifier* next{nullptr};

 protected:
  Creature& creature;

 public:
  explicit CreatureModifier(Creature& creature) : creature(creature) {}

  void add(CreatureModifier* cm) {
    if (next)
      next->add(cm);
    else
      next = cm;
  }

  virtual void handle() {
    if (next) next->handle();
  }
};

class DoubleAttackModifier : public CreatureModifier {
 public:
  explicit DoubleAttackModifier(Creature& creature)
      : CreatureModifier(creature) {}

  void handle() override {
    creature.attack *= 2;
    CreatureModifier::handle();
  }
};

class IncreaseDefenseModifier : public CreatureModifier {
 public:
  explicit IncreaseDefenseModifier(Creature& creature)
      : CreatureModifier(creature) {}

  void handle() override {
    creature.attack *= 2;
    CreatureModifier::handle();
  }
};

class NoBonusesModifier : public CreatureModifier {
 public:
  explicit NoBonusesModifier(Creature& creature) : CreatureModifier{creature} {}

  void handle() {
    // do nothing!
  }
};

void main() {
  Creature goblin{"Goblin", 1, 1};
  CreatureModifier root{goblin};
  DoubleAttackModifier r1{goblin};
  DoubleAttackModifier r1_2{goblin};
  IncreaseDefenseModifier r2{goblin};

  root.add(&r1);
  root.add(&r1_2);
  root.add(&r2);

  root.handle();

  cout << "name : " << goblin.name << "( attack : " << goblin.attack
       << ", defense : " << goblin.defense << ")" << endl;

  Creature goblin2{"Goblin", 1, 1};
  CreatureModifier root2{goblin2};
  DoubleAttackModifier r1_{goblin2};
  DoubleAttackModifier r1_2_{goblin2};
  IncreaseDefenseModifier r2_{goblin2};
  NoBonusesModifier r3_{goblin2};

  root2.add(&r2_);
  root2.add(&r3_);
  root2.add(&r1_2_);
  root2.add(&r1_);

  root2.handle();
  cout << "name : " << goblin2.name << "( attack : " << goblin2.attack
       << ", defense : " << goblin2.defense << ")" << endl;
}
};  // namespace PointerChain

namespace BrokerChain {

template <typename T>
using signal = boost::signals2::signal<T>;
using connection = boost::signals2::connection;

struct Query {
  string creature_name;
  enum Argument { ATTACK, DEFENSE } argument;
  int result;
};

struct Game {
  signal<void(Query&)> queries;
  int result;
};

struct Creature {
  int attack, defense;
  string name;

  Creature(Game& game, const string& name, int attack, int defense)
      : game(game), name(name), attack(attack), defense(defense) {}

  int get_attack() const {
    Query q{name, Query::Argument::ATTACK, attack};
    game.queries(q);

    return q.result;
  }

 private:
  Game& game;
};

struct CreatureModifier {
  CreatureModifier(Game& game, Creature& creature)
      : game(game), creature{creature} {}

 private:
  Game& game;
  Creature& creature;
};

struct DoubleAttackModifier : public CreatureModifier {
  DoubleAttackModifier(Game& game, Creature& creature)
      : CreatureModifier(game, creature) {
    conn = game.queries.connect([&](Query& q) {
      if (q.creature_name == creature.name &&
          q.argument == Query::Argument::ATTACK)
        q.result *= 2;
    });
  }

  ~DoubleAttackModifier() { conn.disconnect(); }

 private:
  connection conn;
};

void main() {
  Game game;
  Creature goblin{game, "Strong Goblin", 2, 2};

  cout << "name : " << goblin.name << "( attack : " << goblin.attack << ")"
       << endl;

  {
    DoubleAttackModifier dam{game, goblin};
    cout << "name : " << goblin.name << "( attack : " << goblin.get_attack()
         << ")" << endl;
  }

  cout << "name : " << goblin.name << "( attack : " << goblin.attack << ")"
       << endl;
}
};  // namespace BrokerChain

int main(void) {
  HandlerChain::main();
  PointerChain::main();
  BrokerChain::main();

  return 0;
}
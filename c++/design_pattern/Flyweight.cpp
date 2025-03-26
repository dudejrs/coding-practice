#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <iostream>
#include <map>
#define N 100
#define SPRITE 1000

using namespace std;

namespace Flyweight {

/********************/
/* 플라이웨이트 원본 객체 */
/********************/

struct ParticleOrigin {
  pair<int, int> coords;
  pair<int, int> vector;
  pair<int, int> speed;
  int color[N];
  int sprite[SPRITE];
};

/**********************/
/* 플라이웨이트 패턴 적용후 */
/**********************/

// 공유 상태
struct ParticleFlyweight {
  int color[N];
  int sprite[SPRITE];
};

struct ParitcleFlyweightFactory {
  static ParticleFlyweight* getFlyweightParticle(const string& key) {
    if (cache.find(key) == end(cache)) {
      cache[key] = new ParticleFlyweight();
    }

    return cache[key];
  }

 private:
  static map<string, ParticleFlyweight*> cache;
};

// 고유 상태

struct ParticleContext {
 public:
  ParticleContext(pair<int, int> coords, pair<int, int> vector,
                  pair<int, int> speed, const string& key)
      : coords(coords), vector(vector), speed(speed) {
    this->flyweight = ParitcleFlyweightFactory::getFlyweightParticle(key);
  }

  void draw() {}

 private:
  pair<int, int> coords;
  pair<int, int> vector;
  pair<int, int> speed;
  ParticleFlyweight* flyweight;
};

void main() {}
};  // namespace Flyweight

namespace FlyweightFormattedText {

// BadCase
class FormattedText {
  string plainText;
  bool* caps;

 public:
  explicit FormattedText(const string& plainText)
      : plainText(plainText), caps(new bool[plainText.length()]) {}

  ~FormattedText() { delete[] caps; }

  void capitalize(int start, int end) {
    for (int i = start; i <= end; i++) {
      caps[i] = true;
    }
  }

  int length() const { return plainText.length(); }

  friend ostream& operator<<(ostream& os, const FormattedText& text) {
    stringstream ss;

    for (int i = 0; i < text.length(); i++) {
      char c = text.plainText[i];
      ss << ((text.caps[i]) ? toupper(c) : c);
    }

    return os << ss.str();
  }
};

// GoodCase

struct TextRange {
  int begin;
  int end;
  bool capitalize;

  TextRange(int begin, int end) : begin(begin), end(end), capitalize(false) {}

  bool covers(int position) const {
    return position >= begin && position <= end;
  }
};

class FlyweightFormattedText {
  string plainText;
  vector<TextRange> formatting;

 public:
  explicit FlyweightFormattedText(const string& plainText)
      : plainText(plainText) {}

  ~FlyweightFormattedText() {}

  TextRange& get_range(int start, int end) {
    formatting.emplace_back(start, end);
    return *(formatting.rbegin());
  }

  int length() const { return plainText.length(); }

  friend ostream& operator<<(ostream& os, const FlyweightFormattedText& text) {
    stringstream ss;

    for (int i = 0; i < text.length(); i++) {
      char c = text.plainText[i];
      for (auto range : text.formatting) {
        if (range.covers(i) && range.capitalize) c = toupper(c);
        ss << c;
      }
    }

    return os << ss.str();
  }
};

void main() {}

};  // namespace FlyweightFormattedText

namespace FlyweightExampleWithBoost1 {
typedef uint32_t key;
template <typename K, typename V>
using bimap = boost::bimap<K, V>;

struct User {
  User(const string& first_name, const string& last_name)
      : first_name(add(first_name)), last_name(add(last_name)) {}

  const string& get_first_name() const {
    return names.left.find(first_name)->second;
  }
  const string& get_last_name() const {
    return names.left.find(last_name)->second;
  }

  static key seed;
  static bimap<key, string> names;

 protected:
  key first_name, last_name;
  static key add(const string& s) {
    auto it = names.right.find(s);
    if (it == names.right.end()) {
      names.insert({++seed, s});
      return seed;
    }
    return it->second;
  }

  friend ostream& operator<<(ostream& os, const User& obj) {
    return os << "first_name : " << obj.get_first_name() << endl
              << "last_name : " << obj.get_last_name();
  }
};

key User::seed = 0;
bimap<key, string> User::names;

void main() {
  User a("John", "Doe");
  std::cout << a << endl;
}
};  // namespace FlyweightExampleWithBoost1

namespace FlyweightExampleWithBoost2 {

template <typename T>
using flyweight = boost::flyweight<T>;

struct User {
  flyweight<string> first_name, last_name;

  User(const string& first_name, const string& last_name)
      : first_name(first_name), last_name(last_name) {}
};

void main() {
  User john_doe{"John", "Doe"};
  cout << "first_name : " << john_doe.first_name.get() << endl
       << "last_name : " << john_doe.last_name.get() << endl;
}
}  // namespace FlyweightExampleWithBoost2

int main(void) {
  Flyweight::main();
  FlyweightFormattedText::main();
  FlyweightExampleWithBoost1::main();
  FlyweightExampleWithBoost2::main();

  return 0;
}
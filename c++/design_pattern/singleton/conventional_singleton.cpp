#include <iostream>

using namespace std;

struct Datbase {
 protected:
  Datbase() {}

 public:
  static Datbase& get() {
    static Datbase* db = new Datbase();
    return *db;
  }

  Datbase(Datbase const&) = delete;
  Datbase(Datbase&&) = delete;
  Datbase& operator=(Datbase const&) = delete;
  Datbase& operator=(Datbase&&) = delete;
};

int main(void) { return 0; }
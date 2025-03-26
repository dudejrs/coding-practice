#include <cmath>
#include <initializer_list>
#include <iostream>
#include <map>
#include <string>

using namespace std;

namespace ProblemCase {

enum class PointType { cartesian, polar };

struct Point {
  float x, y;
  Point(const float x, const float y) : x(x), y(y) {}  // 1. Cartisean 좌표계
  // Point(const float r, const float theta): x(r*cos(theta)),
  // y(r*sin(theta)){};  // 2. Polar 좌표계 :  (Error발생) 구분 불가
  Point(const float a, const float b, PointType type = PointType::cartesian) {
    if (type == PointType::cartesian) {
      x = a;
      y = b;
    } else {
      x = a * cos(b);
      y = a * sin(b);
    }
  }
};

};  // namespace ProblemCase

/* 1. 팩토리 메서드 */
/* - 충돌이 일어나는 생성자는 숨겨놓고 메서드로 생성자를 구현*/

namespace FactoryMethod {

struct Point {
  float x, y;

 protected:
  Point(const float x, const float y) : x(x), y(y) {};

 public:
  static Point NewCartesian(float x, float y) { return {x, y}; }
  static Point NewPolar(float r, float theta) {
    return {r * cos(theta), r * sin(theta)};
  }
};

void do_factory_method() { auto p = Point::NewPolar(5, 3.14); }

};  // namespace FactoryMethod
/* 2. 팩토리 */
/* - 팩토리 클래스를 생성*/

namespace Factory {

struct Point {
  float x, y;
  friend class PointFactory;

 private:
  Point(const float x, const float y) : x(x), y(y) {}
};

struct PointFactory {
  static Point NewCartesian(float x, float y) { return Point{x, y}; }

  static Point NewPolar(float r, float theta) {
    return Point{r * cos(theta), r * sin(theta)};
  }
};

void do_factory() { auto p = PointFactory::NewPolar(5, 3.14); }
};  // namespace Factory

/* 3. 내부 팩터리 */
/* - 내부 팩터리는 생성할 타입의 내부 클래스로 존재하는 간단한 팩터리 */

namespace InnerFactory {
struct Point {
 private:
  Point(float x, float y) : x(x), y(y) {};
  struct PointFactory {
   private:
    PointFactory() {}

   public:
    static Point NewCartesian(float x, float y) { return {x, y}; }
    static Point NewPolar(float r, float theta) {
      return {r * cos(theta), r * sin(theta)};
    }
  };

 public:
  float x, y;
  static PointFactory Factory;
};

void do_inner_factory() { auto p = Point::Factory.NewPolar(5, 3.14); }
}  // namespace InnerFactory

/* 4. 계층 팩터리 */
// 생성 객체 타입이 증가해도 클라이언트 코드를 수정할 필요가 없음

namespace HierarchicalFactory {

struct RoadLogistics;
struct SeaLogistics;

struct Transport {
  virtual void deliver() = 0;
};

struct Logistics {
  void someOperation();
  Transport* create_transport() { return nullptr; };
};

struct Truck : Transport {
  void deliver() {}
};

struct Ship : Transport {
  void deliver() {}
};

struct RoadLogistics : public Logistics {
  Transport* create_transport() { return new Truck(); }
};

struct SeaLogistics : public Logistics {
  Transport* create_transport() { return new Ship(); }
};

void Logistics::someOperation() {
  // ...
  Transport* t = create_transport();
  t->deliver();
  // ...
}

void do_hierarchical_factory() {
  Logistics l;
  RoadLogistics rl;
  SeaLogistics sl;

  l.someOperation();
  rl.someOperation();
  sl.someOperation();
}
};  // namespace HierarchicalFactory

int main(void) {
  FactoryMethod::do_factory_method();
  Factory::do_factory();
  InnerFactory::do_inner_factory();
  HierarchicalFactory::do_hierarchical_factory();

  return 0;
}
#include <initializer_list>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace HierarchcialState {

class LightSwitch;

struct State {
  virtual void on(LightSwitch* ls) {
    cout << "LightSwitch is already on" << endl;
  }
  virtual void off(LightSwitch* ls) {
    cout << "LightSwitch is already off" << endl;
  }
};

struct OnState : State {
  OnState() { cout << "Light turned on." << endl; }
  void off(LightSwitch* ls) override;
};

struct OffState : State {
  OffState() { cout << "Light turned off." << endl; }
  void on(LightSwitch* ls) override;
};

class LightSwitch {
  State* state;

 public:
  LightSwitch() { state = new OnState(); }

  void set_state(State* state) {
    State* previous = this->state;
    this->state = state;
    delete previous;
  }

  void on() { state->on(this); }
  void off() { state->off(this); }
};

void OffState::on(LightSwitch* ls) {
  cout << "Switching light on... " << endl;
  ls->set_state(new OnState());
}

void OnState::off(LightSwitch* ls) {
  cout << "Switching light off... " << endl;
  ls->set_state(new OffState());
}

void main() {
  cout << "[HierarchcialState]" << endl;
  LightSwitch ls;
  ls.on();
  ls.off();
  ls.off();
  ls.on();
  cout << endl;
}
};  // namespace HierarchcialState

namespace RuleBasedState {

enum class State {
  off_hook,    // 수화기를 든 상태
  connecting,  // 연결 시도 상태
  connected,   // 연결 된 상태
  on_hold,     // 대기 상태
  on_hook      // 수화기 내린 상태
};

inline ostream& operator<<(ostream& os, const State& s) {
  switch (s) {
    case State::off_hook:
      os << "off hook";
      break;
    case State::connecting:
      os << "connecting";
      break;
    case State::connected:
      os << "connected";
      break;
    case State::on_hold:
      os << "on hold";
      break;
    case State::on_hook:
      os << "on hook";
      break;
  }
  return os;
}

enum class Trigger {
  call_dialed,      // 전화 걸기
  hung_up,          // 전화 끊기
  call_connected,   // 전화 연결됨
  place_on_hold,    // 대기
  taken_off_hold,   // 대기 종료
  left_message,     // 메시지 남기기
  stop_using_phone  // 전화 사용 종료
};

inline ostream& operator<<(ostream& os, const Trigger& s) {
  switch (s) {
    case Trigger::call_dialed:
      os << "call dialed";
      break;
    case Trigger::hung_up:
      os << "hung up";
      break;
    case Trigger::call_connected:
      os << "call connected";
      break;
    case Trigger::place_on_hold:
      os << "place on hold";
      break;
    case Trigger::taken_off_hold:
      os << "taken off hold";
      break;
    case Trigger::left_message:
      os << "left message";
      break;
    case Trigger::stop_using_phone:
      os << "stop using phone";
      break;
  }
  return os;
}

void main() {
  cout << "[RuleBasedState]" << endl;

  map<State, vector<pair<Trigger, State>>> rules;
  rules[State::off_hook] = {{Trigger::call_dialed, State::connecting},
                            {Trigger::stop_using_phone, State::on_hook}};

  rules[State::connecting] = {
      {Trigger::hung_up, State::off_hook},
      {Trigger::call_connected, State::connected},
  };

  rules[State::connected] = {{Trigger::place_on_hold, State::on_hold},
                             {Trigger::left_message, State::off_hook},
                             {Trigger::hung_up, State::off_hook}};

  rules[State::on_hold] = {{Trigger::taken_off_hold, State::connected},
                           {Trigger::hung_up, State::off_hook}};

  State currentState{State::off_hook}, exitState{State::on_hook};

  while (true) {
    cout << "The phone is currently " << currentState << "." << endl;
  select_trigger:
    cout << "Select a trigger : " << endl;
    int i = 0;
    for (auto t : rules[currentState]) {
      cout << i << ". " << t.first << endl;
      i++;
    }

    cin >> i;

    if (i < 0 || i >= rules[currentState].size()) {
      cout << "Incorrect option. Please try again" << endl;
      goto select_trigger;
    }
    currentState = rules[currentState][i].second;

    if (currentState == exitState) break;
  }
  cout << "We are done using the phone." << endl;
  cout << endl;
}

};  // namespace RuleBasedState

int main(void) {
  HierarchcialState::main();
  RuleBasedState::main();

  return 0;
}
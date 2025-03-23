package com.example.design_pattern.state;

import static java.util.stream.Collectors.*;

import java.util.*;

public class RuleBasedState {

  private static Map<Trigger, Map<State, State>> rules;

  static {
    rules =
        Map.ofEntries(
            Map.entry(Trigger.CALL_DIALED, Map.of(State.OFF_HOOK, State.CONNECTING)),
            Map.entry(
                Trigger.HANG_UP,
                Map.of(
                    State.CONNECTING, State.OFF_HOOK,
                    State.ON_HOLD, State.OFF_HOOK)),
            Map.entry(Trigger.CALL_CONNECTED, Map.of(State.CONNECTING, State.CONNECTED)),
            Map.entry(Trigger.PLACE_ON_HOLD, Map.of(State.CONNECTED, State.ON_HOLD)),
            Map.entry(Trigger.TAKEN_OFF_HOLD, Map.of(State.ON_HOLD, State.CONNECTED)),
            Map.entry(Trigger.LEFT_MESSAGE, Map.of(State.CONNECTED, State.OFF_HOOK)),
            Map.entry(Trigger.STOP_USING_PHONE, Map.of(State.OFF_HOOK, State.ON_HOOK)));
  }

  private static enum State {
    OFF_HOOK("off hook"), // 수화기를 든 상태
    CONNECTING("connecting"), // 연결 시도 상태
    CONNECTED("connected"), // 연결 된 상태
    ON_HOLD("on hold"), // 대기 상태
    ON_HOOK("on hook"); // 수화기 내린 상태

    private String text;

    State(String text) {
      this.text = text;
    }

    public List<Trigger> getTriggers() {
      return rules.entrySet().stream()
          .filter(s -> s.getValue().containsKey(this))
          .map(s -> s.getKey())
          .collect(toList());
    }

    @Override
    public String toString() {
      return this.text;
    }
  };

  private static enum Trigger {
    CALL_DIALED("call dialed"), // 전화 걸기
    HANG_UP("hang up"), // 전화 끊기
    CALL_CONNECTED("call connected"), // 전화 연결됨
    PLACE_ON_HOLD("place one hold"), // 대기
    TAKEN_OFF_HOLD("taken off hold"), // 대기 종료
    LEFT_MESSAGE("left message"), // 메시지 남기기
    STOP_USING_PHONE("stop using phone"); // 전화 사용 종료

    private String text;

    Trigger(String text) {
      this.text = text;
    }

    public State next(State before) {
      return rules.get(this).get(before);
    }

    @Override
    public String toString() {
      return this.text;
    }
  };

  public static void main(String... args) {
    State current = State.OFF_HOOK;
    Scanner scanner = new Scanner(System.in);

    while (true) {
      if (current == State.ON_HOOK) {
        break;
      }
      System.out.println("The phone is currenty " + current);

      List<Trigger> triggers = current.getTriggers();
      Trigger occured;

      while (true) {
        System.out.println("Select a trigger : ");

        for (int i = 0; i < triggers.size(); i++) {
          System.out.printf("%s(%d), ", triggers.get(i), i);
        }
        System.out.println();

        int choice = scanner.nextInt();

        if (choice >= 0 && choice < State.values().length) {
          occured = triggers.get(choice);
          break;
        }

        System.out.println("Incorrect option. Please try again");
      }

      current = occured.next(current);
    }
    System.out.println("We are done using the phone.");
  }
}

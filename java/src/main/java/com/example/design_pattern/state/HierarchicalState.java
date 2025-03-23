package com.example.design_pattern.state;

public class HierarchicalState {

  private static class LightSwitch {

    private State state = new OffState();

    public void on() {
      state.on(this);
    }

    public void off() {
      state.off(this);
    }
  }

  private static interface State {

    void on(LightSwitch ls);

    void off(LightSwitch ls);
  }

  private static class OnState implements State {

    OnState() {
      System.out.println("Light turned on.");
    }

    @Override
    public void on(LightSwitch ls) {}

    @Override
    public void off(LightSwitch ls) {
      System.out.println("Switching light off...");
      ls.state = new OffState();
    }
  }

  private static class OffState implements State {

    OffState() {
      System.out.println("Light turned off.");
    }

    @Override
    public void on(LightSwitch ls) {
      System.out.println("Switching light on...");
      ls.state = new OnState();
    }

    @Override
    public void off(LightSwitch ls) {}
  }

  public static void main(String... args) {
    LightSwitch ls = new LightSwitch();
    ls.on();
    ls.on();
    ls.off();
    ls.off();
    ls.on();
  }
}

package com.example.design_pattern;

public class ChainOfResponsibility {

  private static class HandlerChain {

    private static class Request {
      public String name;

      Request(String name) {
        this.name = name;
      }
    }

    private static interface Handler {
      void setNext(Handler handler);

      void handle(Request request);
    }

    private static class BaseHandler implements Handler {

      private Handler next;

      @Override
      public void setNext(Handler handler) {
        if (next == null) {
          next = handler;
          return;
        }
        next.setNext(handler);
      }

      @Override
      public void handle(Request request) {
        if (next != null) {
          next.handle(request);
        } else {
          System.out.println("[BaseHandler] handling the " + request.name);
        }
      }
    }

    private static class ConcreteHandler extends BaseHandler {

      public String name;

      ConcreteHandler(String name) {
        super();
        this.name = name;
      }

      boolean canHandle(Request request) {
        return true;
      }

      @Override
      public void handle(Request request) {

        if (canHandle(request)) {
          System.out.println(String.format("[%s] : handling the %s", name, request.name));
        }
        super.handle(request);
      }
    }

    public static void main() {

      Request request = new Request("Request 1");
      Handler handler1 = new ConcreteHandler("Handler 1");
      Handler handler2 = new ConcreteHandler("Handler 2");
      Handler handler3 = new ConcreteHandler("Handler 3");

      handler1.setNext(handler2);
      handler1.setNext(handler3);

      handler1.handle(request);
    }
  }

  private static class PointerChain {

    private static class Creature {
      public String name;
      public int attack;
      public int defense;

      Creature(String name, int attack, int defense) {
        this.name = name;
        this.attack = attack;
        this.defense = defense;
      }

      @Override
      public String toString() {
        return String.format("[%s] attack-%d, defense-%d", name, attack, defense);
      }
    }

    private static class CreatureModifier {

      protected Creature creature;
      private CreatureModifier next;

      CreatureModifier(Creature creature) {
        this.creature = creature;
      }

      public void add(CreatureModifier modifier) {
        if (next != null) {
          next.add(modifier);
          return;
        }
        this.next = modifier;
      }

      public void handle() {
        if (next != null) {
          next.handle();
        }
      }
    }

    private static class DoubleAttackModifier extends CreatureModifier {

      DoubleAttackModifier(Creature creature) {
        super(creature);
      }

      @Override
      public void handle() {
        super.creature.attack *= 2;
        super.handle();
      }
    }

    private static class IncreaseDefenseModifier extends CreatureModifier {

      IncreaseDefenseModifier(Creature creature) {
        super(creature);
      }

      @Override
      public void handle() {
        super.creature.defense += 1;
        super.handle();
      }
    }

    private static class NoBonusModifier extends CreatureModifier {
      NoBonusModifier(Creature creature) {
        super(creature);
      }

      @Override
      public void handle() {
        // do nothing
      }
    }

    public static void main() {
      Creature goblin = new Creature("goblin", 1, 1);
      CreatureModifier modifier1 = new DoubleAttackModifier(goblin);
      CreatureModifier modifier2 = new DoubleAttackModifier(goblin);
      CreatureModifier modifier3 = new IncreaseDefenseModifier(goblin);
      CreatureModifier modifier4 = new NoBonusModifier(goblin);
      CreatureModifier modifier5 = new IncreaseDefenseModifier(goblin);

      modifier1.add(modifier2);
      modifier1.add(modifier3);
      modifier1.add(modifier4);
      modifier1.add(modifier5);

      modifier1.handle();

      System.out.println(goblin);
    }
  }

  public static void main(String... args) {
    HandlerChain.main();
    PointerChain.main();
  }
}

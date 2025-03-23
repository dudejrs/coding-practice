package com.example.design_pattern;

import java.util.*;

public class Mediator {

  private static class BasicMediator {

    private static class ComponenetA {
      private Mediator_ mediator;

      public void setMeidator(Mediator_ mediator) {
        this.mediator = mediator;
      }

      public void operationA() {
        System.out.println("A does OperationA");
        mediator.notify("A", "B");
      }

      public void receive(String message) {
        System.out.println("A recive message: " + message);
      }
    }

    private static class ComponentB {
      private Mediator_ mediator;

      public void setMeidator(Mediator_ mediator) {
        this.mediator = mediator;
      }

      public void operationB() {
        System.out.println("B does OperationB");
        mediator.notify("B", "A");
      }

      public void receive(String message) {
        System.out.println("B recive message: " + message);
      }
    }

    private static class Mediator_ {

      private ComponenetA a;
      private ComponentB b;

      Mediator_(ComponenetA a, ComponentB b) {
        this.a = a;
        this.b = b;
        a.setMeidator(this);
        b.setMeidator(this);
      }

      public void notify(String sender, String reciever) {
        if ("A".equals(sender)) {
          System.out.println(String.format("Mediator react to A and Send Message to %s", reciever));
          a.receive("Hello World!");
        }

        if ("B".equals(sender)) {
          System.out.println(String.format("Mediator react to B and Send Message to %s", reciever));
          b.receive("Hello World!");
        }
      }
    }

    public static void main() {
      ComponenetA a = new ComponenetA();
      ComponentB b = new ComponentB();

      Mediator_ mediator = new Mediator_(a, b);
      a.operationA();
      b.operationB();
    }
  }

  private static class CollectionMediator {

    private static class Person {
      public String name;
      public ChatRoom chatroom;
      public List<String> chatLogs = new ArrayList<>();

      Person(String name) {
        this.name = name;
      }

      public void say(String message) {
        if (chatroom != null) {
          chatroom.boradcast(name, message);
        }
      }

      public void privateMessageTo(String whom, String message) {
        if (chatroom != null) {
          chatroom.message(name, whom, message);
        }
      }

      public void receiveFrom(String whom, String message) {
        System.out.println(String.format("[%s's session] %s : %s", name, whom, message));
      }
    }

    private static class ChatRoom {

      List<Person> people = new ArrayList<>();

      public void join(Person p) {
        String joinMsg = String.format("%s joins the chat", p.name);
        p.chatroom = this;
        boradcast("rooms", joinMsg);
        people.add(p);
      }

      public void boradcast(String from, String message) {

        for (Person p : people) {
          if (!from.equals(p.name)) {
            p.receiveFrom(from, message);
          }
        }
      }

      public void message(String from, String to, String message) {
        Optional<Person> optPerson = people.stream().filter(p -> to.equals(p.name)).findFirst();

        if (!optPerson.isEmpty()) {
          optPerson.get().receiveFrom(from, message);
        }
      }
    }

    public static void main() {

      Person john = new Person("John");
      Person jane = new Person("Jane");
      Person simon = new Person("Simon");

      ChatRoom chatroom = new ChatRoom();

      chatroom.join(john);
      chatroom.join(jane);
      john.say("hi Jane!");
      chatroom.join(simon);
      john.say("hi Simon!");
      john.privateMessageTo("Simon", "glad you could join us, Simon!");
    }
  }

  private static class MediatorWithHierarchicalComponent {

    private static interface Mediator_ {
      void notify(BaseComponent sender, String event);
    }

    private static class BaseComponent {
      protected Mediator_ mediator;

      public void setMeidator(Mediator_ mediator) {
        this.mediator = mediator;
      }
    }

    private static class ComponentA extends BaseComponent {
      void doA() {
        System.out.println("ComponentA does A");
        if (mediator != null) mediator.notify(this, "A");
      }

      void doB() {
        System.out.println("ComponentA does B");
      }
    }

    private static class ComponentB extends BaseComponent {
      void doC() {
        System.out.println("ComponentA does C");
      }

      void doD() {
        System.out.println("ComponentB does D");
        if (mediator != null) mediator.notify(this, "D");
      }
    }

    private static class ConcreterMediator implements Mediator_ {

      ComponentA a;
      ComponentB b;

      ConcreterMediator(ComponentA a, ComponentB b) {
        this.a = a;
        this.b = b;
        this.a.setMeidator(this);
        this.b.setMeidator(this);
      }

      @Override
      public void notify(BaseComponent sender, String event) {
        if (sender instanceof ComponentA) {
          if ("A".equals(event)) {
            System.out.println("Mediator react to A and trigger following operations: ");
            this.b.doC();
          }
        }
        if (sender instanceof ComponentB) {
          if ("D".equals(event)) {
            System.out.println("Mediator react to B and trigger following operations: ");
            this.a.doB();
          }
        }
      }
    }

    public static void main() {

      ComponentA a = new ComponentA();
      ComponentB b = new ComponentB();

      ConcreterMediator mediator = new ConcreterMediator(a, b);

      a.doA();
      b.doD();
    }
  }

  public static void main(String... args) {
    BasicMediator.main();
    CollectionMediator.main();
    MediatorWithHierarchicalComponent.main();
  }
}

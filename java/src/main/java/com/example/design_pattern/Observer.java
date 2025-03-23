package com.example.design_pattern;

import java.util.*;

public class Observer {

  public static class Observer1 {

    public static interface Observer_<T> {
      void fieldChange(T source, String fieldName);
    }

    public static class Observable<T> {
      private List<Observer_<T>> observers;

      Observable() {
        observers = new LinkedList<>();
      }

      void subscribe(Observer_<T> observer) {
        synchronized (observers) {
          observers.add(observer);
        }
      }

      void unsubscribe(Observer_<T> observer) {
        synchronized (observers) {
          observers.remove(observer);
        }
      }

      void notify(T source, String fieldName) {
        for (Observer_<T> ob : observers) ob.fieldChange(source, fieldName);
      }
    }

    public static class Person extends Observable<Person> {
      private int age;

      Person(int age) {
        this.age = age;
      }

      int getAge() {
        return age;
      }

      void setAge(int age) {
        this.age = age;
        notify(this, "age");
      }
    }

    public static class ConsolePersonObserver implements Observer_<Person> {

      @Override
      public void fieldChange(Person person, String fieldName) {
        if ("age".equals(fieldName)) {
          System.out.println(
              String.format("Person's %s has changed to %s.", fieldName, person.getAge()));
        }
      }
    }

    public static void main() {
      Person p = new Person(20);
      ConsolePersonObserver observer = new ConsolePersonObserver();
      p.subscribe(observer);
      p.setAge(21);
      p.unsubscribe(observer);
      p.setAge(22);
    }
  }

  public static class PublisherSubscriberPattern {

    public static interface Publisher<T> {
      void subscribe(Subscriber<? super T> subscriber);
    }

    public static interface Subscriber<T> {
      void onNext(T t);
    }

    public static class SimpleCell implements Publisher<Integer>, Subscriber<Integer> {
      private int value = 0;
      private String name;
      private List<Subscriber> subscribers = new ArrayList<>();

      public SimpleCell(String name) {
        this.name = name;
      }

      @Override
      public void subscribe(Subscriber<? super Integer> subscriber) {
        subscribers.add(subscriber);
      }

      @Override
      public void onNext(Integer value) {
        this.value = value;
        System.out.println(String.format("[%s] value : %d", name, value));
        notifyAllSubscribers();
      }

      private void notifyAllSubscribers() {
        subscribers.forEach(subscriber -> subscriber.onNext(value));
      }
    }

    public static class ArithmeticCell extends SimpleCell {

      private int left = 0;
      private int right = 0;

      public ArithmeticCell(String name) {
        super(name);
      }

      public void setLeft(int left) {
        this.left = left;
        onNext(left + right);
      }

      public void setRight(int right) {
        this.right = right;
        onNext(left + right);
      }
    }

    public static void main() {
      ArithmeticCell c3 = new ArithmeticCell("C3");
      SimpleCell c1 = new SimpleCell("C1");
      SimpleCell c2 = new SimpleCell("C2");

      c1.subscribe(c3::setLeft);
      c2.subscribe(c3::setRight);
      c1.onNext(1);
      c2.onNext(2);
    }
  }

  public static void main(String... args) {
    Observer1.main();
    PublisherSubscriberPattern.main();
  }
}

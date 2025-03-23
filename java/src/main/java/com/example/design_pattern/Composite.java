package com.example.design_pattern;

import java.util.*;

public class Composite {

  private static class ArrayBasedAttribute {

    private static class Creature {

      public enum Abilites {
        STR,
        AGL,
        INTL,
        COUNT;
      }

      private EnumMap<Abilites, Integer> abilites;

      Creature(int strength, int agility, int intelligence) {
        abilites = new EnumMap<>(Abilites.class);
        abilites.put(Abilites.STR, strength);
        abilites.put(Abilites.AGL, agility);
        abilites.put(Abilites.INTL, intelligence);
      }

      public int sum() {
        return abilites.values().stream().mapToInt(i -> i).sum();
      }

      public double average() {
        return sum() / (abilites.size());
      }

      public int max() {
        return abilites.values().stream().mapToInt(i -> i).max().getAsInt();
      }
    }

    public static void main() {
      Creature creature = new Creature(1, 2, 3);
      System.out.println(creature.max());
    }
  }

  private static class Composite_ {

    private static interface GraphicObject {
      void draw();
    }

    private static class Circle implements GraphicObject {
      @Override
      public void draw() {
        System.out.println("Circle");
      }
    }

    private static class Group implements GraphicObject {
      private String name;
      private List<GraphicObject> objects;

      Group(String name) {
        this.name = name;
        objects = new LinkedList<>();
      }

      public void add(GraphicObject object) {
        objects.add(object);
      }

      @Override
      public void draw() {
        System.out.printf("group <%s> contains : ", name);
        for (GraphicObject object : objects) {
          object.draw();
        }
      }
    }

    public static void main() {
      Group root = new Group("root");
      Group subGroup = new Group("sub");
      Circle c1 = new Circle();
      Circle c2 = new Circle();

      subGroup.add(c2);
      root.add(c1);
      root.add(subGroup);
      root.draw();
    }
  }

  private static class TemplateBasedComposite {

    private abstract static class NeuronBase implements Iterable<Neuron> {
      public <T extends NeuronBase> void connectTo(T other) {
        for (Neuron in : this) {
          for (Neuron out : other) {
            out.connect(in);
          }
        }
      }

      public abstract Iterator<Neuron> iterator();
    }

    private static class Neuron extends NeuronBase {
      private static int number = 1;
      private List<Neuron> in;
      private List<Neuron> out;
      private int id;

      private class SelfIterator implements Iterator<Neuron> {
        private boolean hasNext = false;

        @Override
        public boolean hasNext() {
          return hasNext;
        }

        @Override
        public Neuron next() {
          hasNext = false;
          return Neuron.this;
        }

        @Override
        public void remove() {}
      }

      Neuron() {
        in = new LinkedList<>();
        out = new LinkedList<>();
        id = number++;
      }

      public void connect(Neuron other) {
        other.in.add(this);
        out.add(other);
      }

      @Override
      public Iterator<Neuron> iterator() {
        return new SelfIterator();
      }
    }

    private static class NeuronLayer extends NeuronBase {
      private List<Neuron> layer;

      public NeuronLayer(int count) {
        this.layer = new LinkedList<>();
        while (count > 0) {
          layer.add(new Neuron());
          count--;
        }
      }

      @Override
      public Iterator<Neuron> iterator() {
        return layer.iterator();
      }
    }

    public static void main() {
      Neuron n1 = new Neuron();
      Neuron n2 = new Neuron();
      NeuronLayer layer = new NeuronLayer(5);
      n1.connectTo(layer);
      layer.connectTo(n2);
    }
  }

  public static void main(String... args) {
    ArrayBasedAttribute.main();
    Composite_.main();
    TemplateBasedComposite.main();
  }
}

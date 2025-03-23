package com.example.design_pattern;

public class Bridge {

  private static class Pimpl {

    private static class Person {

      private String name;
      private PersonImpl impl;

      Person(String name, PersonImpl impl) {
        this.name = name;
        this.impl = impl;
      }

      public static interface PersonImpl {
        void greet(Person p);
      }

      public void greet() {
        impl.greet(this);
      }

      public String getName() {
        return name;
      }
    }

    private static class HelloPersonImpl implements Person.PersonImpl {

      @Override
      public void greet(Person p) {
        System.out.println("Hello " + p.getName());
      }
    }

    public static void main() {
      Person p = new Person("David", new HelloPersonImpl());
      p.greet();
    }
  }

  private static class Bridge_ {

    public static interface Renderer {
      void renderCicle(double x, double y, double radius);
    }

    public abstract static class Shape {
      protected Renderer renderer;

      Shape(Renderer renderer) {
        this.renderer = renderer;
      }

      public abstract void draw();
    }

    public static class Circle extends Shape {
      private double x;
      private double y;
      private double radius;

      public Circle(double x, double y, double radius, Renderer renderer) {
        super(renderer);
        this.x = x;
        this.y = y;
        this.radius = radius;
      }

      @Override
      public void draw() {
        renderer.renderCicle(x, y, radius);
      }
    }

    public static class VectorRenderer implements Renderer {
      @Override
      public void renderCicle(double x, double y, double radius) {
        System.out.println(
            String.format("Drawing a vector circle of radius %.2f at (%.2f, %.2f)", radius, x, y));
      }
    }

    public static class RasterRenderer implements Renderer {
      @Override
      public void renderCicle(double x, double y, double radius) {
        System.out.println(
            String.format("Rastering a circle of radius %.2f at (%.2f, %.2f)", radius, x, y));
      }
    }

    public static void main() {
      VectorRenderer vectorRenderer = new VectorRenderer();
      RasterRenderer rasterRenderer = new RasterRenderer();

      Circle vectorCircle = new Circle(5, 5, 5, vectorRenderer);
      Circle rasterCircle = new Circle(5, 5, 5, rasterRenderer);

      vectorCircle.draw();
      rasterCircle.draw();
    }
  }

  public static void main(String... args) {

    Pimpl.main();
    Bridge_.main();
  }
}

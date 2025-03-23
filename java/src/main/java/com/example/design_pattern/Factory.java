package com.example.design_pattern;

public class Factory {
  private static class Point {

    public enum Type {
      CARTESIAN,
      POLAR;
    }

    private double x;
    private double y;
    private Type type;

    public Point(double x, double y) {
      this.x = x;
      this.y = y;
      this.type = Type.CARTESIAN;
    }

    public Point(double a, double b, Type type) {
      if (type == Type.POLAR) {
        this.x = a * Math.cos(b);
        this.y = a * Math.sin(b);
        this.type = type;
        return;
      }

      this.x = a;
      this.y = b;
      this.type = type;
    }
  }

  private static class FactoryMethod {
    private static class Point {
      private double x;
      private double y;

      private Point(double x, double y) {
        this.x = x;
        this.y = y;
      }

      public static Point newCartesianPoint(double x, double y) {
        return new Point(x, y);
      }

      public static Point newPolarPoint(double r, double theta) {
        double x = r * Math.cos(theta);
        double y = r * Math.sin(theta);
        return new Point(x, y);
      }
    }

    public static void main() {
      Point p1 = Point.newCartesianPoint(1.0, 2.0);
      Point p2 = Point.newCartesianPoint(2.0, 3.0);
    }
  }

  private static class FactoryClass {
    private static class Point {
      private double x;
      private double y;

      protected Point(double x, double y) {
        this.x = x;
        this.y = y;
      }
    }

    private static class PointFactory {

      private PointFactory() {}

      public static Point newCartesian(double x, double y) {
        return new Point(x, y);
      }

      public static Point newPolar(double r, double theta) {
        double x = r * Math.cos(theta);
        double y = r * Math.sin(theta);

        return new Point(x, y);
      }
    }

    public static void main() {

      Point p1 = PointFactory.newCartesian(1.0, 2.0);
      Point p2 = PointFactory.newPolar(1.0, 2.0);
    }
  }

  private static class InnerFactory {
    private static class Point {
      private double x;
      private double y;

      public static class PointFactory {
        private PointFactory() {}

        public static Point newCartesian(double x, double y) {
          return new Point(x, y);
        }

        public static Point newPolar(double r, double theta) {
          double x = r * Math.cos(theta);
          double y = r * Math.sin(theta);

          return new Point(x, y);
        }
      }

      private Point(double x, double y) {
        this.x = x;
        this.y = y;
      }
    }

    public static void main() {
      Point p1 = Point.PointFactory.newCartesian(1.0, 2.0);
      Point p2 = Point.PointFactory.newPolar(1.0, 2.0);
    }
  }

  private static class HierarchicalFactory {

    private static interface Transport {
      public void deliver();
    }

    private static class Truck implements Transport {
      public void deliver() {}
    }

    private static class Ship implements Transport {
      public void deliver() {}
    }

    private static class Logistics {
      void someOperation() {
        Transport t = createTransport();
        t.deliver();
      }

      Transport createTransport() {
        return null;
      }
    }

    private static class RoadLogistics extends Logistics {
      Transport createTransport() {
        return new Truck();
      }
    }

    private static class SeaLogistics extends Logistics {
      Transport createTransport() {
        return new Ship();
      }
    }

    public static void main() {
      RoadLogistics rl = new RoadLogistics();
      SeaLogistics sl = new SeaLogistics();

      rl.someOperation();
      sl.someOperation();
    }
  }

  public static void main(String... args) {}
}

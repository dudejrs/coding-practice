package com.example.design_pattern;

import java.util.*;
import java.lang.reflect.*;
import java.util.function.*;

public class Decorator{
	
	private static class Decorator_{


		private static interface Notifier {
			void send(String message);
		}

		private static class ConcreteNotifier implements Notifier {
			@Override
			public void send(String message){
				System.out.println("[Concrete] : " + message);
			}
		}

		private static class BaseDecorator  implements Notifier{
			protected Notifier wrapee;

			BaseDecorator(Notifier wrapee){
				this.wrapee = wrapee;
			}

			@Override
			public void send(String message){
				wrapee.send(message);
			}
		}

		private static class SMSDecorator extends BaseDecorator {
			SMSDecorator(Notifier wrapee){
				super(wrapee);
			}

			private void sendSMS(String message){
				System.out.println("[SMS] : " + message);
			}

			@Override
			public void send(String message){
				super.send(message);
				sendSMS(message);
			}
		}

		private static class SlackDecorator extends BaseDecorator {
			SlackDecorator(Notifier wrapee){
				super(wrapee);
			}

			private void sendSlack(String message){
				System.out.println("[Slack] : "+message);
			}

			@Override
			public void send(String message){
				super.send(message);
				sendSlack(message);
			}
		}

		public static void main(){
			SMSDecorator decoratedNotifier = new SMSDecorator(
				new SlackDecorator(
					new ConcreteNotifier()
				));

			decoratedNotifier.send("Hello World");
		}
	}


	private static class DyncamicDecorator {

		private static interface Shape {
			String render();
		}

		private static class Circle implements Shape {
			double radius;

			public Circle(double radius){
				this.radius = (double) radius;
			}

			public void resize(double factor){
				radius *= factor;
			}

			@Override
			public String render(){
				return String.format("Circle of raidus %.2f", radius);
			}

		}


		private static class ColorShape implements Shape {
			private Shape shape;
			private String color;

			ColorShape(Shape shape, String color){
				this.shape = shape;
				this.color = color;
			}

			@Override
			public String render(){
				return String.format("%s has %s", shape.render(), color);
			}

		}

		private static class TransparentShape implements Shape {
			private Shape shape;
			private int transparency;

			public TransparentShape(Shape shape, int transparency){
				this.shape = shape;
				this.transparency = transparency;
			}

			@Override
			public String render(){
				return String.format("%s has %.2f%% transparency", shape.render(), ((double) Math.min(256,transparency) * 100) /256 );
			}
		}

		public static void main(){


			ColorShape decoratedShape = new ColorShape(
				new TransparentShape(
					new Circle(3.0), 128
				),
				"red"
			);

			System.out.println(decoratedShape.render());

		}
	}

	private static class StaticDecorator_ {

		private static interface Shape {
			String render();
		}

		private static class Circle implements Shape {
			double radius;

			public Circle(Object... radius){
				if(radius[0] instanceof Number){
					this.radius = (double) radius[0];
					return;
				}
				this.radius = 0;
			}

			public void resize(double factor){
				radius *= factor;
			}

			@Override
			public String render(){
				return String.format("Circle of raidus %.2f", radius);
			}

		}

		private static class StaticDecorator <T extends Shape> implements Shape {
			
			protected T shape;
			protected static Object[] trimObjects(Object... args){
				return Arrays.stream(args)
							.skip(1)
							.toArray();
			}

			public StaticDecorator(Object... args) {

				try {
					Class<T> clazz = (Class<T>) args[0];
					Object[] arguments = {};
					if(args.length > 1){
						arguments = trimObjects(args);	

					} 

					Class<?>[] classes = new Class<?>[arguments.length];
					for(int i=0; i<arguments.length; i++){
						classes[i] = arguments[i].getClass();
					}

					Constructor<?> constructor = clazz.getConstructors()[0];
					shape = (T) constructor.newInstance((Object) arguments);

				}catch(InstantiationException | IllegalAccessException 
					| InvocationTargetException e){
					
					throw new IllegalArgumentException(e);
				}
			}

			@Override
			public String render(){
				return shape.render();
			}
		}


		private static class ColorShape<T extends Shape> extends StaticDecorator {

			private String color;

			public ColorShape(Object... args){
				super(StaticDecorator.trimObjects(args));
				this.color = (String) args[0];
			}

			@Override
			public String render(){
				return String.format("%s has %s", super.render(), color );
			}

		}

		private static class TransparentShape<T extends Shape> extends StaticDecorator {

			private int transparency;

			public TransparentShape(Object... args){
				super(StaticDecorator.trimObjects(args));
				this.transparency = (int) args[0];
			}

			@Override
			public String render(){
				return String.format("%s has %.2f%% transparency", super.render(), ((double) Math.min(transparency,256)*100) / 256  );
			}
		}


		public static void main(){

			ColorShape<TransparentShape<Circle>> decoratedShape = 
				new ColorShape("red", TransparentShape.class, 128, Circle.class, 3.0);

			System.out.println(decoratedShape.render());
		}
	}

	private static class FunctionalDecorator {


		private static class Logger implements Runnable{
			
			private Runnable function;
			private String name;

			Logger(String name, Runnable function){
				this.name = name;
				this.function = function;
			}

			@Override
			public void run(){
				System.out.println("Entering " + name);
				function.run();
				System.out.println("Exiting " + name);
			}
		}

		public static void main(){
			Logger logger = new  Logger("Hello Function",()->{
				System.out.println("Hello");
			});

			logger.run();
		}
	}


	public static void main(String... args){

		Decorator_.main();
		DyncamicDecorator.main();
		StaticDecorator_.main();
		FunctionalDecorator.main();
	}
}
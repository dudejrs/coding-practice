package com.example.design_pattern;


import java.util.*;
import java.util.function.*;

public class AbstractFactory {


	private static interface HotDrink {
		public abstract void prepare(int volume);
	}

	private static class Tea implements HotDrink {

		@Override
		public void prepare(int volume){
			System.out.println(String.format("Making Tea %sml...",volume));
		}
	}

	private static class Coffee implements HotDrink {
		
		@Override
		public void prepare(int volume){
			System.out.println(String.format("Making Coffee %sml...", volume));
		}

	}

	private static class AbstractFactory1{

		private static interface HotDrinkFactory{
			public HotDrink make();
		}

		private static class TeaFactory implements HotDrinkFactory{
			@Override 
			public HotDrink make(){
				return new Tea();
			}
		}

		private static class CoffeeFactory implements HotDrinkFactory {
			@Override
			public HotDrink make(){
				return new Coffee();
			}
		}

		private static class DrinkFactory {
			private static Map<String, HotDrinkFactory> hotFactories;

			public DrinkFactory(){
				hotFactories = new HashMap<>();
				hotFactories.put("tea", new TeaFactory());
				hotFactories.put("coffee", new CoffeeFactory());
			}

			public HotDrink makeDrink(String name){
				HotDrink drink = hotFactories.get(name).make();
				if( drink instanceof Tea){
					drink.prepare(50);
				}
				if( drink instanceof Coffee){
					drink.prepare(200);
				}
				return drink;
			}
		}

		public static void main(){
			DrinkFactory myFactory = new DrinkFactory();
			HotDrink myDrink = myFactory.makeDrink("tea");
		}
	}

	private static class FunctionalAbstractFactory{

		private static interface HotDrinkWithVolumeFactory{
			public HotDrink makeWithVolume();
		}

		private static class DrinkWithVolumeFactory {
			private Map<String, HotDrinkWithVolumeFactory> hotFactories;

			public DrinkWithVolumeFactory(){
				hotFactories = new HashMap<>();

				hotFactories.put("tea", () -> {
					HotDrink tea = new Tea();
					tea.prepare(50);
					return tea;
				});	
				hotFactories.put("coffee", ()-> {
					HotDrink coffee = new Coffee();
					coffee.prepare(200);
					return coffee;
				});
			}

			public HotDrink makeDrink(String name){
				return hotFactories.get(name).makeWithVolume();
			}
		}

		public static void main(){

			DrinkWithVolumeFactory myFactory = new DrinkWithVolumeFactory();
			HotDrink myDrink = myFactory.makeDrink("coffee");
			
		}
	}

	private static interface Button {
		abstract public void paint();
	}

	private static interface CheckBox {
		abstract public void paint();
	}

	private static interface DropDown {
		abstract public void paint();
	}

	private static class WinButton  implements Button{
		@Override 
		public void paint(){}
	}
	private static class MacButton  implements Button{
		@Override 
		public void paint(){}
	}

	private static class WinCheckBox  implements CheckBox{
		@Override 
		public void paint(){}
	}
	
	private static class MacCheckBox  implements CheckBox{
		@Override 
		public void paint(){}
	}

	private static class WinDropDown  implements DropDown{
		@Override 
		public void paint(){}
	}
	private static class MacDropDown  implements DropDown{
		@Override 
		public void paint(){}
	}



	private static class AbstractFactory2{


		private static interface GuiFactory {
			public Button createButton();
			public CheckBox createCheckBox();
			public DropDown createDropDown();
		}

		private static class WinGuiFactory implements GuiFactory{
			@Override 
			public Button createButton(){
				return new WinButton();
			}
			@Override 
			public CheckBox createCheckBox(){
				return new WinCheckBox();
			}
			@Override 
			public DropDown createDropDown(){
				return new WinDropDown();
			}
		}

		private static class MacGuiFactory implements GuiFactory{
			@Override 
			public Button createButton(){
				return new MacButton();
			}
			@Override 
			public CheckBox createCheckBox(){
				return new MacCheckBox();
			}
			@Override 
			public DropDown createDropDown(){
				return new MacDropDown();
			}
		}

		private static class Application {
			Button button;
			CheckBox checkBox;
			DropDown dropDown;
			Application(GuiFactory factory){
				button = factory.createButton();
				checkBox = factory.createCheckBox();
				dropDown = factory.createDropDown();
			}
		};

		public static void main(){

			GuiFactory factory = new MacGuiFactory();
			Application app = new Application(factory);
		}
	}


	public static void main(String... args){

		AbstractFactory1.main();
		FunctionalAbstractFactory.main();
		AbstractFactory2.main();
	}	
}
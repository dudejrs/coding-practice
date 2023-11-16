package com.example.design_pattern;


import java.util.*;

public class Builder {

	private static class FluentInterfaceBuilder{
		
		private static class HtmlElement{
			private String name;
			private String text;
			private List<HtmlElement> children;


			public HtmlElement(String name, String text){
				this.name = name;
				this.text = text;
				this.children = new ArrayList<>();
			}

			public HtmlElement(){
				this("","");
			}

			public void addChildren(String name, String text){
				children.add(new HtmlElement(name,text));
			}

			@Override
			public String toString(){
				StringBuilder builder = new StringBuilder();
				builder.append(String.format("<%s>\n",name));
				for(HtmlElement child : children){
					builder.append(child);
				}
				builder.append(text+"\n");
				if(!"".equals(text)){
					builder.append(String.format("</%s>\n",name));
				}
				return builder.toString();
			}

			public void setName(String name){
				this.name = name;
			}

			public void SetText(String text){
				this.text = text;
			}

		}

		private static class HtmlElementBuilder{
			private HtmlElement root;

			public HtmlElementBuilder(String rootName, String rootText){
				this.root = new HtmlElement(rootName, rootText);
			}

			public HtmlElementBuilder(String rootName){
				this.root = new HtmlElement(rootName, "");
			}

			public HtmlElementBuilder addChildren(String name, String text){
				root.addChildren(name, text);
				return this;
			}

			public HtmlElement build(){
				return root;
			}
		}

		public static void main(String... args){
			HtmlElementBuilder builder = new HtmlElementBuilder("ul");
			HtmlElement root = builder.addChildren("li", "Hello")
									.addChildren("l1", "World")
									.build();

			System.out.println(root.toString());
		}
	}

	private static class CompositeBuilder {

		private static class Person {
			private String streetAddress;
			private String postCode;
			private String city;
			private String companyName;
			private String position;
			private int annualIncome;

			public Person(){}

			public Person(Person other){
				this.streetAddress = other.streetAddress;
				this.postCode = other.postCode;
				this.city = other.city;
				this.companyName = other.companyName;
				this.position = other.position;
				this.annualIncome = other.annualIncome;
			}

			void setStreetAddress(String streetAddress){
				this.streetAddress = streetAddress;
			}

			void setPostCode(String postCode){
				this.postCode = postCode;
			}

			void setCity(String city){
				this.city = city;
			}

			void setCompanyName(String companyName){
				this.companyName = companyName;
			}

			void setPosition(String position){
				this.position = position;
			}

			void setAnnualIncome(int annualIncome){
				this.annualIncome = annualIncome;
			}
		}

		private static class PersonBuilder{

			private Person p;

			public PersonBuilder(){
				this.p = new Person();
			}

			public Person build(){
				return p;
			}

			public PersonAddressBuilder lives(){
				return new PersonAddressBuilder(p);
			}

			public PersonJobBuilder works(){
				return new PersonJobBuilder(p);
			}
		}

		private static class PersonAddressBuilder extends PersonBuilder{
			private Person p;
			public PersonAddressBuilder(Person p){
				this.p = p;
			}

			public PersonAddressBuilder at(String streetAddress){
				p.setStreetAddress(streetAddress);
				return this;
			}

			public PersonAddressBuilder withPostCode(String postCode){
				p.setPostCode(postCode);
				return this;
			}

			public PersonAddressBuilder in(String city){
				p.setCity(city);
				return this;
			}
		}

		private static class PersonJobBuilder extends PersonBuilder{
			private Person p;
			public PersonJobBuilder(Person p){
				this.p = p;
			}

			public PersonJobBuilder at(String companyName){
				p.setCompanyName(companyName);
				return this;
			}

			public PersonJobBuilder asA(String position){
				p.setPosition(position);
				return this;
			}

			public PersonJobBuilder earning(int annualIncome){
				p.setAnnualIncome(annualIncome);
				return this;
			}
		}

		public static void main(String... args) {
			PersonBuilder builder = new PersonBuilder();

			Person p = builder.lives()
							.at("123 London Road")
							.withPostCode("SW1 1GB")
							.in("London")
							.works()
							.at("PragmaSoft")
							.asA("Consultant")
							.earning((int)10e6)
							.build();
		}
	}

	private static class HierarchicalBuilder {

		private abstract class Pizza{
			public enum Topping {HAM, MUSHROOOM, ONION, PEPPER, SAUSAGE};
			private Set<Topping> toppings;
		}

		private class NyPizza extends Pizza {
			public enum Size {SMALL, MEDIUM, LARGE};
			private Size size;
		}

		private class Calzone extends Pizza{
			private boolean sauceInside;
		}


		public static void main(String... args){

		}
	}

	public static void main(String... args){
		FluentInterfaceBuilder.main();
		CompositeBuilder.main();
		HierarchicalBuilder.main();
	}
}
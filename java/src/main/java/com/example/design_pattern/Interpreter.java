package com.example.design_pattern;

import java.util.*;

public class Interpreter {

	public static class Token {

		public String text;
		public Type type;

		public static enum Type {
			INTEGER, PLUS, MINUS, LPAREN, RPAREN;
		}

		Token(Type type, String text){
			this.type = type;
			this.text = text;
		}
	}

	public static List<Token> lex(String input){

		List<Token> result = new LinkedList<>();

		for(int i=0; i<input.length(); i++){
			switch(input.charAt(i)){
				case '+' -> result.add(new Token(Token.Type.PLUS, "+"));
				case '-' -> result.add(new Token(Token.Type.MINUS, "-"));
				case '(' -> result.add(new Token(Token.Type.LPAREN, "("));
				case ')' -> result.add(new Token(Token.Type.RPAREN, ")"));
				default ->{
					StringBuilder builder = new StringBuilder();
					builder.append(input.charAt(i));
					for(int j=i+1; j<input.length(); j++){
						if(!Character.isDigit(input.charAt(j))) break;

						builder.append(input.charAt(j));
						i++;
					}
					result.add(new Token(Token.Type.INTEGER, builder.toString()));
				}
			}
		}


		return result;
	}

	public static interface Element {
		public int eval();
	}

	public static class IntegerElement implements Element {

		private int value;

		IntegerElement(String input){
			this.value = Integer.parseInt(input);
		}

		@Override 
		public int eval(){
			return value;
		}
	}

	public static class BinaryOperatorElement implements Element {

		public static enum Type {
			ADDITION, SUBTRACTION;
		}

		public Element left;
		public Element right;
		public Type type;

		BinaryOperatorElement(){}

		@Override 
		public int eval(){
			if (left == null) return 0;
			if (right == null) return left.eval();

			if (type == Type.ADDITION){
				return left.eval() + right.eval();
			}
			return left.eval() - right.eval();
		}
	}

	public static Element parse(List<Token> tokens){
		BinaryOperatorElement result = new BinaryOperatorElement();

		boolean haveLeft = false;

		for(int i=0; i<tokens.size(); i++){
			switch(tokens.get(i).type){
				case INTEGER -> {
					if (!haveLeft){
						result.left = new IntegerElement(tokens.get(i).text);
						haveLeft = true;
						break;
					} 

					result.right = new IntegerElement(tokens.get(i).text);
				}
				case PLUS -> {
					result.type = BinaryOperatorElement.Type.ADDITION; 
				}
				case MINUS -> {
					result.type = BinaryOperatorElement.Type.SUBTRACTION;
				}
				case LPAREN -> {
					int j;
					for (j= i+1; j<tokens.size();j++){
						if(tokens.get(j).type == Token.Type.RPAREN) break;
					}
					Element element = parse(tokens.subList(i+1,j));

					if (!haveLeft){
						result.left = element;
						haveLeft = true;
						
					} else {
						result.right = element;
					}
					i = j;
				}
				case RPAREN -> {}
				default -> {}
			}
		}

		return result;
	}

	public static void main(String... args){
		List<String> inputs = List.of("(13-4)-(12+1)", "12+5", "(12+5)-3");

		for (String input  : inputs){
			List<Token> tokens = lex(input);
			Element e = parse(tokens);
			System.out.println(e.eval());
		}
	}
}
package com.example.design_pattern;

import java.util.*;


public class Flyweight {

	private static final int N = 100;
	private static final int SPRITE = 1000;

	private static class Flyweight_ {


		private static class ParticleFlyweight {
			int[] color;
			int[] sprite;

			ParticleFlyweight(){
				this.color = new int[N];
				this.sprite = new int[SPRITE];
			}

			ParticleFlyweight(int[] color, int[] sprite){
				assert(color.length == N && sprite.length == SPRITE);
				this.color = color;
				this.sprite = sprite;
			}
		}

		private static class ParticleFlyweightFactory {
			public static ParticleFlyweight getFlyweight(String key){
				if(!cache.containsKey(key)){
					cache.put(key, new ParticleFlyweight());
				}
				return cache.get(key);
			}

			private static Map<String, ParticleFlyweight> cache = new HashMap<>();
		}

		private static class Particle{
			int[] coords;
			int[] vector;
			int[] speed;
			String key;
			
			Particle(int[] coords, int[] vector, int[] speed, String key){
				assert(coords.length == 2 && vector.length == 2 && speed.length == 2);
				this.coords = coords;
				this.vector = vector;
				this.speed = speed;
				this.key = key;
			}
		}

		public static void main(){

		}
	}


	private static class FormattedText {

		private static class TextRange{
			private int begin;
			private int end;
			boolean capitalize;

			TextRange(int begin, int end, boolean capitalize){
				this.begin = begin;
				this.end =end;
				this.capitalize = capitalize;
			}

			public boolean covers(int position){
				return begin <= position && position <= end;
			}
		}


		private static class FormattedText_{
			private String text;
			private List<TextRange> formats;

			FormattedText_(String text){
				this.text = text.toLowerCase();
				this.formats = new LinkedList<>();
			}

			void capitalize(int start, int end){
				formats.add(new TextRange(start, end, true));
			}

			@Override
			public String toString(){
				StringBuilder builder = new StringBuilder();
				for(int i=0; i< text.length(); i++){
					char c = text.charAt(i);
					for(TextRange format : formats){
						if(format.covers(i)){
							c = Character.toUpperCase(c);
						}
					}
					builder.append(c);
				}
				return builder.toString();
			}
		}

		public static void main() {

		}
	}

	private static class Flyweight2 {

		private class User {
			
			private static int seed = 0;
			private static Map<Integer,String> names;
			private static Map<String, Integer> keys;

			private int firstName;
			private int secondName;	
			
			@Override 
			public String toString(){
				return firstName+" "+secondName;
			}
		}

		public static void main(){

		}
	}

	public static void main(String... args){
		Flyweight_.main();
		FormattedText.main();
		Flyweight2.main();
	}
}
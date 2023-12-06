package com.example.design_pattern;


import java.util.*;

public class Proxy {
	
	private static class Proxy_ {

		private static interface ServiceInterface {
			void operation();
		}

		private static class Service implements ServiceInterface {
			public void operation(){
			}
		}

		private static class ServiceProxy implements ServiceInterface {
			
			ServiceInterface service;

			ServiceProxy(ServiceInterface service){
				this.service = service;
			}

			private boolean checkAccess(){
				System.out.println("Proxy : checking access prior to firing real request.");
				return true;
			}

			private void logAccess(){
				System.out.println("Proxy : Logging the time of request");
			}

			public void operation(){
				if(checkAccess()){
					service.operation();
					logAccess();
				}
			}
		}

		public static void main(){
			ServiceInterface proxy = new ServiceProxy(new Service());
			proxy.operation();
		}		
	}

	private static class AttributeProxy{

		private static class Property <T> {
			T value;

			Property(T value){
				this.value = value;
			}

			T get(){
				System.out.println("get : something to do");
				return value;
			}

			void set(T value){
				System.out.println("set : something to do");
				this.value = value;
			}
		}

		private static class Creature {
			private Property<Integer> strength;
			private Property<Integer> agility;

			Creature(int strength, int agility){
				this.strength = new Property<Integer>(strength);
				this.agility = new Property<Integer>(agility);
			}

			public void setStrength(int strength){
				this.strength.set(strength);
			}

			public void setAgility(int agility){
				this.agility.set(agility);
			}

			public int getStrength(){
				return strength.get();
			}

			public int getAgility(){
				return agility.get();
			}
		}

		public static void main(){
			Creature creature = new Creature(10,20);
			int str = creature.getStrength();
			creature.setAgility(10);
		}
	}

	private static class CachedProxy {

		private class VideoInfo{}
		private class VideoData{}

		private interface YoutubeService {
			List<String> getVideos();
			VideoInfo getVideoInfo(int id);
			void download(int id);
		}

		private class YoutubeServiceImpl implements YoutubeService{
			public List<String> getVideos(){
				return List.of();
			}

			public VideoInfo getVideoInfo(int id){
				return new VideoInfo();
			}

			public void download(int id){
			}
		}

		private class YoutubeServiceProxy implements YoutubeService{
			
			YoutubeService service;

			private List<String> ids;
			private Map<Integer,VideoInfo> infos;
			private List<Integer> downloaded;
			private boolean needReset;

			YoutubeServiceProxy(YoutubeService service){
				this.service = service;
				infos = new HashMap<>();
				downloaded = new LinkedList<>();
				needReset = false;
			}

			public List<String> getVideos(){
				if(ids == null || needReset){
					return ids= service.getVideos();
				}
				return ids;
			}

			public VideoInfo getVideoInfo(int id){
				if(!infos.containsKey(id) || needReset){
					VideoInfo info = service.getVideoInfo(id);
					infos.put(id, info);
				}
				return infos.get(id);
			}

			public void download(int id){
				if(!downloaded.contains(id) || needReset){
					service.download(id);
					downloaded.add(id);
				}
			}
		}

		public static void main(){

		}
	}

	private static class VirtualProxy {

		private static interface Image {
			void draw();
		}

		private static class Bitmap implements Image {
			Bitmap(String filename){
				System.out.println("Loading image from "+filename);
			}

			public void draw(){
				System.out.println("Drawing image");
			}
		}

		private static class LazyBitmap implements Image {
			
			private String filename;
			private Bitmap bitmap;

			LazyBitmap(String filename){
				this.filename = filename;
				System.out.println("Lazy Bitmap from "+ filename);
			}

			public void draw(){
				System.out.println("About to draw the image");
				if(bitmap == null){
					bitmap = new Bitmap(filename);
				}
				bitmap.draw();
				System.out.println("Complete drawing the image");
			}
		}

		public static void main(){
			Image bitmap = new LazyBitmap("pokemon.png");
			bitmap.draw();
		}
	}

	public static void main(String... args){
		Proxy_.main();
		AttributeProxy.main();
		CachedProxy.main();
		VirtualProxy.main();
	}
}
package com.example.design_pattern;

import java.util.*;

public class Adapter{

	private static record Point(int x, int y){
	}

	private static record Line(Point start, Point end){

	}

	private static class Rectangle implements Iterable<Line> {
		private List<Line> lines = new ArrayList<>();

		Rectangle(int x, int y, int width, int height){
			lines.add(new Line( new Point(x,y), new Point(x,y+height)));
			lines.add(new Line( new Point(x,y+height), new Point(x+width,y+height)));
			lines.add(new Line( new Point(x+width,y+height), new Point(x+width,y)));
			lines.add(new Line( new Point(x+width,y), new Point(x,y)));
		}

		@Override
		public Iterator<Line> iterator() {
			return lines.iterator();
		}
	}

	private static List<Point> rectToPoints(Line line){
		List<Point> points = new ArrayList<>();

	
		int left = Math.min(line.start().x(), line.end().x());
		int right = Math.max(line.start().x(), line.end().x());
		int bottom = Math.min(line.start().y(), line.end().y());
		int top = Math.max(line.start().y(), line.end().y());

		int dx = right - left;
		int dy = top - bottom;

		// 수직 수평이라고만 가정
		if ( dx == 0 ){
			for (int y = bottom; y <= top; y++){
				points.add(new Point(left, y));
			}
		} 

		if (dy == 0){
			for(int x = left; x <= right; x++ ){
				points.add(new Point(x, top));
			}
		}
	


		return points;
	}

	private static class LegacyRenderer{
		void drawPoints(List<Point> points){
			for(Point p : points){
				System.out.print(String.format("(%d, %d) ", p.x(), p.y()));
			}
			System.out.println();
		}
	}

	private static interface ClientRenderer{
		void drawRect(Rectangle rec);
	}
	private static class ObjectAdapter {

		private static class RendererAdapter implements ClientRenderer {
			private LegacyRenderer renderer;

			public RendererAdapter(){
				renderer = new LegacyRenderer();
			}

			@Override
			public void drawRect(Rectangle rect){
				for (Line line : rect){
					List<Point> points = rectToPoints(line);
					renderer.drawPoints(points);
				}
			}
		}
		
		public static void main(){
			Rectangle rect = new Rectangle(0,0, 5, 5);
			ClientRenderer renderer = new RendererAdapter();
			renderer.drawRect(rect);
		}
	}

	private static class CachingAdapter {
		
		private static class RendererAdapter implements ClientRenderer {
			private LegacyRenderer renderer; 
			private Map<Integer,List<Point>> cache;

			public RendererAdapter() {
				renderer = new LegacyRenderer();
				cache = new HashMap<>();
			}

			@Override
			public void drawRect(Rectangle rect){
				for(Line line : rect){

					if(cache.containsKey(line.hashCode())){
						continue;
					}

					List<Point> points = rectToPoints(line);
					cache.put(line.hashCode(), points);

					renderer.drawPoints(points);
				}
			}
		}

		public static void main(){
			Rectangle rect1 = new Rectangle(0,0,5,5);
			Rectangle rect2 = new Rectangle(0,0,5,5);

			ClientRenderer renderer = new RendererAdapter();
			renderer.drawRect(rect1);
			renderer.drawRect(rect2);
		}
	}
	
	public static void main(String... args){

		ObjectAdapter.main();
		CachingAdapter.main();
	}
}
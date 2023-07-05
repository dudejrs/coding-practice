package com.example.cote.GJM;

import java.util.*;

public class 다항방정식의_해 {

	private static final int TEST_CASES = 10;
	private static final int L = 100;
	private static int n;
	private static Random rd = new Random(43);

	private static double[] initialize(){
		n = rd.nextInt(9)+1;
		double[] poly = new double[n+1];
		for(int i =0; i<poly.length; i++){
			poly[i] = (rd.nextDouble()-0.5)*(rd.nextInt(10)+1) ;
		}
		return poly;
	}


	private static double[] differentiate(double[] poly) {
		double[] ret = new double[poly.length-1];
		int cur = poly.length -1;
		
		for(int i=0; i<poly.length-1; i++){
			ret[i] = cur * (poly[i]);
			cur--;
		}

		return ret;
	}

	private static double evaluate(double x, double[] poly){
		double sum = 0;

		for(int i= 0; i<poly.length; i++){
			sum += poly[i] * Math.pow(x,n-i);
		}

		return sum;
	}
	private static List<Double> solveNaive(double[] poly){

		if (n == 1) return List.of(-(poly[1])/poly[0]);
		
		
		double a = poly[0], b = poly[1], c = poly[2];
		double D = b * b - 4 * a * c;

		if( D < 0 ) return Collections.emptyList();
		if( D == 0 ) return List.of((-b)/(2.0 * a));

		double d = Math.sqrt(D);
		return List.of((-b-d)/(2.0*a), (-b+d)/(2.0*a));
	}
	private static void swap(double a, double b){
		double tmp = a;
		a= b;
		b = tmp;
	}

	private static List<Double> solve(double[] poly){

		if(poly.length-1 <= 2) return solveNaive(poly);

		double[] derivitives = differentiate(poly);
		List<Double> result = solve(derivitives);
		LinkedList<Double> sols = new LinkedList<>();
		LinkedList<Double> ret = new LinkedList<>();
		

		sols.addFirst(-L-1.0);
		sols.addAll(result);
		sols.addLast(L+1.0);

		for(int i=0; i<sols.size()-1; i++){
			double x0 = sols.get(i), x1 = sols.get(i+1);
			double y0 = evaluate(x0,poly), y1 = evaluate(x1, poly);

			if(y0 * y1 > 0) continue;
			if(y0 > y1){
				swap(y0,y1);
				swap(x0,x1);
			}

			for(int it=0; it<100; it++){
				double x_mid = (x0+x1)/2;
				double y_mid = evaluate(x_mid, poly);

				if(y0 * y_mid < 0 ){
					x1 = x_mid;
					y1 = y_mid;
				} else {
					x0 = x_mid;
					y0 = y_mid;
				}
			}
			ret.add((x0+x1)/2);
		}

		return ret;
	}

	public static void main(String... args){

		for(int i=0; i<TEST_CASES; i++){
			double[] poly = initialize();
			List<Double> result = solve(poly);
			for( Double r : result){
				System.out.printf("%.5f ", r);
			}
			System.out.println("");
		}

	}

}
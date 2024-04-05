package com.example.design_pattern.strategy;

import com.example.design_pattern.strategy.example.*;
import java.io.*;
import java.util.*;

public class StaticStrategy {

	private static class ListStrategyProvider{
		private static ListStrategyProvider instance;
		private Map<Class<? extends ListStrategy>, ListStrategy> strategies;

		private ListStrategyProvider() {
			this.strategies = Map.ofEntries(
				Map.entry(MarkdownListStrategy.class, new MarkdownListStrategy()),
				Map.entry(HtmlListStrategy.class ,new HtmlListStrategy())
			);
		}

		public static ListStrategyProvider getInstance() {
			if (instance == null) {
				instance = new ListStrategyProvider();
			}
			return instance;
		}

		public ListStrategy get(Class<? extends ListStrategy> cls) {
			return strategies.get(cls);
		}
	}

	private static class TextProcessor<T extends ListStrategy> {;
		
		private PrintWriter out;
		private ListStrategy strategy;

		TextProcessor(Class<T> clazz, PrintWriter out) {
			this.strategy = ListStrategyProvider.getInstance().get(clazz);
			this.out = out;
		}

		void appendLists(List<String> items) {	
			strategy.start(out);
			for (String item : items) {
				strategy.addListItem(out, item);
			}
			strategy.end(out);
		}

		void clear(){
			out.flush();
		}
	}
	
	public static void main(String... args){
		PrintWriter out = new PrintWriter(System.out);
		TextProcessor<MarkdownListStrategy> tp1 = new TextProcessor<>(MarkdownListStrategy.class, out);
		tp1.appendLists(List.of("foo", "bar", "baz"));
		tp1.clear();
		TextProcessor<HtmlListStrategy> tp2 = new TextProcessor<>(HtmlListStrategy.class, out);
		tp2.appendLists(List.of("foo", "bar", "baz"));
		tp2.clear();
	}
}
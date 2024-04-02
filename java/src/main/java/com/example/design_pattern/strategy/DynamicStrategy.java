package com.example.design_pattern.strategy;

import java.io.*;
import java.util.*;
import com.example.design_pattern.strategy.example.*;

public class DynamicStrategy {
	public static enum OutputFormat {
		MARK_DOWN, HTML;
	}

	public static class TextProcessor {

		private PrintWriter out;
		private ListStrategy strategy;

		TextProcessor(PrintWriter out, OutputFormat format){
			this.out = out;
			setOutputFormat(format);
		}

		void appendLists(List<String> items) {
			strategy.start(out);
			for (String item : items) {
				strategy.addListItem(out, item);
			}
			strategy.end(out);
		}
		void setOutputFormat(OutputFormat format) {
			switch(format) {
				case MARK_DOWN -> {
					this.strategy = new MarkdownListStrategy();
				}
				case HTML -> {
					this.strategy = new HtmlListStrategy();
				}
			}
		}
		void clear(){
			out.flush();
		}
	}
	
	public static void main(String... args){
		TextProcessor tp = new TextProcessor(new PrintWriter(System.out), OutputFormat.MARK_DOWN);
		tp.appendLists(List.of("foo", "bar", "baz"));
		tp.clear();
		tp.setOutputFormat(OutputFormat.HTML);
		tp.appendLists(List.of("foo", "bar", "baz"));
		tp.clear();
	}
}
package com.example.design_pattern.strategy.example;

import java.io.*;
import com.example.design_pattern.strategy.example.ListStrategy;

public class MarkdownListStrategy implements ListStrategy {
	
	@Override 
	public void start(PrintWriter out) {
		//do nothing
	}

	@Override
	public void addListItem(PrintWriter out, String item) {
		out.print(String.format("* %s\n", item));
	}

	@Override
	public void end(PrintWriter out) {
		//do nothing
	}
}
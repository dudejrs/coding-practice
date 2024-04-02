package com.example.design_pattern.strategy.example;

import java.io.*;
import com.example.design_pattern.strategy.example.ListStrategy;

public class HtmlListStrategy implements ListStrategy {
	
	@Override 
	public void start(PrintWriter out) {
		out.print("<ul>\n");
	}

	@Override
	public void addListItem(PrintWriter out, String item) {
		out.print(String.format("<li>%s</li>\n", item));
	}

	@Override
	public void end(PrintWriter out) {
		out.print("</ul>\n");
	}
}
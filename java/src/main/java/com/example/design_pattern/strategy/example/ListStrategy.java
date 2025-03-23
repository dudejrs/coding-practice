package com.example.design_pattern.strategy.example;

import java.io.*;

public interface ListStrategy {
  void start(PrintWriter out);

  void addListItem(PrintWriter out, String item);

  void end(PrintWriter out);
}

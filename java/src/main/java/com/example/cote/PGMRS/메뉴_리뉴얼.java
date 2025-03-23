package com.example.cote.PGMRS;

import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.stream.*;

public class 메뉴_리뉴얼 {

  private static class Course {

    public final String course;
    public final int occurences;

    public Course(String course, int occurences) {
      this.course = course;
      this.occurences = occurences;
    }
  }

  private static void getCourses(
      char nextMenu,
      Set<String> selectedMenus,
      List<Set<String>> orderList,
      Map<Integer, List<Course>> courses) {
    int occurences =
        (int) orderList.stream().filter(order -> order.containsAll(selectedMenus)).count();
    if (occurences < 2) return;

    int size = selectedMenus.size();

    if (courses.containsKey(size)) {
      List<Course> courseList = courses.get(size);
      String course = selectedMenus.stream().sorted().collect(Collectors.joining(""));
      Course newCourse = new Course(course, occurences);

      Course originalCourse = courseList.get(0);

      if (originalCourse.occurences < occurences) {
        courseList.clear();
        courseList.add(newCourse);
      } else if (originalCourse.occurences == occurences) {
        courseList.add(newCourse);
      }
    }

    if (size >= 10) return;

    for (char cur = nextMenu; cur < 'Z'; cur++) {
      String menu = String.valueOf(cur);
      selectedMenus.add(menu);
      getCourses((char) (cur + 1), selectedMenus, orderList, courses);
      selectedMenus.remove(menu);
    }
  }

  private static String[] solve(String[] orders, int[] course) {

    List<Set<String>> orderList =
        Arrays.stream(orders)
            .map(String::chars)
            .map(
                charStream ->
                    charStream
                        .mapToObj(menu -> String.valueOf((char) menu))
                        .collect(Collectors.toSet()))
            .collect(Collectors.toList());

    Map<Integer, List<Course>> courses = new HashMap<>();

    for (int length : course) {
      List<Course> list = new ArrayList<>();
      list.add(new Course("", 0));
      courses.put(length, list);
    }

    getCourses('A', new HashSet<>(), orderList, courses);

    return courses.values().stream()
        .filter(list -> list.get(0).occurences > 0)
        .flatMap(List::stream)
        .map(c -> c.course)
        .sorted()
        .toArray(String[]::new);
  }

  public static void main(String... args) throws IOException {

    Path p = Paths.get(System.getProperty("user.dir") + "/data/메뉴_리뉴얼.txt");
    BufferedReader rd = Files.newBufferedReader(p);

    int testCases = Integer.parseInt(rd.readLine());

    while (testCases > 0) {

      String[] orders = rd.readLine().split(" ");
      int[] course = Arrays.stream(rd.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

      System.out.println(Arrays.toString(solve(orders, course)));

      testCases--;
    }
  }
}

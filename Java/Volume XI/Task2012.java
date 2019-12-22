// Topic: elementary

import java.io.*;
import java.util.Scanner;

public class Task2012 {
  static final int TASKS = 12;
  static final int TIME = 45;
  static final int TOTAL_TIME = 240;
  Scanner in;
  PrintWriter out;

  void run() throws IOException
  {
    in = new Scanner(System.in);
    out = new PrintWriter(System.out);
    solve();
    out.flush();
  }

  void solve() throws IOException {
    int f = in.nextInt();
    if (TIME * (TASKS - f) < TOTAL_TIME) {
      out.println("YES");
    } else {
      out.println("NO");
    }
  }

  public static void main(String[] args) throws IOException {
    new Task2012().run();
  }
}

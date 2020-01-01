// Topic: elementary

import java.io.*;
import java.util.Scanner;

public class Task2001
{
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
    int a1 = in.nextInt();
    int b1 = in.nextInt();
    in.nextInt();
    int b2 = in.nextInt();
    int a3 = in.nextInt();
    in.nextInt();
    out.println((a1 - a3) + " " + (b1 - b2));
  }

  public static void main(String[] args) throws IOException {
    new Task2001().run();
  }
}
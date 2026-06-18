// LE 3.3: Grade Distribution
// Sep 24 2024
// Displays grades in a bar graph-like format

// Sample program execution
// Enter value for A >> 1
// Enter value for B >> 4
// Enter value for C >> 6
// Enter value for D >> 2
// Enter value for F >> 1
//
// 0    10   20   30   40   50   60   70   80   90  100%
// |    |    |    |    |    |    |    |    |    |   |
// **************************************************
// **** A 
// ************** B 
// ********************* C 
// ******* D 
// **** F 


package LE03;

import java.util.Scanner;

public class Grades {
	// class attributes
	private int A, B, C, D, F;
	private int total;
	
	// class constructor
	public Grades(int a, int b, int c, int d, int f) {
		this.A = a;
		this.B = b;
		this.C = c;
		this.D = d;
		this.F = f;
		
		// calculates total grades
		this.total = a + b + c + d + f;
	}
	
	// accessors and mutators
	public int getA() { return this.A; }
	public void setA(int a) {
		this.A = a;
		this.total = this.A + this.B + this.C + this.D + this.F;
	}
	
	public int getB() { return this.B; }
	public void setB(int b) {
		this.B = b;
		this.total = this.A + this.B + this.C + this.D + this.F;
	}
	
	public int getC() { return this.C; }
	public void setC(int c) {
		this.C = c;
		this.total = this.A + this.B + this.C + this.D + this.F;
	}
	
	public int getD() { return this.D; }
	public void setD(int d) {
		this.D = d;
		this.total = this.A + this.B + this.C + this.D + this.F;
	}
	
	public int getF() {return this.F; }
	public void setF(int f) {
		this.F = f;
		this.total = this.A + this.B + this.C + this.D + this.F;
	}

	public int getTotal() { return this.total; }
	
	// method for printing the data of the object in a bar graph format
	public void printGraph() {
		// declarations
		int As, Bs, Cs, Ds, Fs;
		
		// re-calculates total grades
		this.total = A + B + C + D + F;
		
		// calculates fraction of the 50 a grade gets
		As = (int) Math.round(50.0 * this.A / this.total);
		Bs = (int) Math.round(50.0 * this.B / this.total);
		Cs = (int) Math.round(50.0 * this.C / this.total);
		Ds = (int) Math.round(50.0 * this.D / this.total);
		Fs = (int) Math.round(50.0 * this.F / this.total);
		
		System.out.println("0    10   20   30   40   50   60   70   80   90  100%");
		System.out.println("|    |    |    |    |    |    |    |    |    |   |");
		System.out.println("**************************************************");
		System.out.println(Grades.fillX(As, 'A'));
		System.out.println(Grades.fillX(Bs, 'B'));
		System.out.println(Grades.fillX(Cs, 'C'));
		System.out.println(Grades.fillX(Ds, 'D'));
		System.out.println(Grades.fillX(Fs, 'F'));
	}
	
	// method for making a single bar in the bar graph
	private static StringBuilder fillX(int x, char l) {
		StringBuilder bar = new StringBuilder();
		
		for (int i = 0; i < x; i++) {
			bar.append("*");
		}
		
		bar.append(" ");
		bar.append(l);
		bar.append(" ");
		
		return bar;
	}

	// main method
	public static void main(String[] args) {
		// declarations
		Grades g1;
		int a, b, c, d, f;
		Scanner input = new Scanner(System.in);
		
		// user prompt and input
		System.out.print("Enter value for A >> ");
		a = input.nextInt();
		System.out.print("Enter value for B >> ");
		b = input.nextInt();
		System.out.print("Enter value for C >> ");
		c = input.nextInt();
		System.out.print("Enter value for D >> ");
		d = input.nextInt();
		System.out.print("Enter value for F >> ");
		f = input.nextInt();
		input.nextLine();
		System.out.println();
		
		// using Grade constructor
		g1 = new Grades(a, b, c, d, f);
		
		// calls method for printing bar graph
		g1.printGraph();
		
		// closing the Scanner object
		input.close();
	}
}

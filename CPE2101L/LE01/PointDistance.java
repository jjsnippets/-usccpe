// LE 1.4: Distance between Two Points
// Aug 22 2024
// implements distance formula between two points

// Sample program execution
// Enter x1 and y1: 1 2
// Enter x2 and y2: -3 4
//
// The distance between the two points is 4.47213595499958

package LE01;
import java.util.Scanner;

public class PointDistance {
	public static void main(String[] args) {
		double x1, y1, x2, y2;
		double result;
		Scanner input = new Scanner(System.in);
		
		// user prompt and input
		System.out.print("Enter x1 and y1: ");
		x1 = input.nextDouble();
		y1 = input.nextDouble();
		
		System.out.print("Enter x2 and y2: ");
		x2 = input.nextDouble();
		y2 = input.nextDouble();
		System.out.println();
		
		// calculations
		result = Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
		
		// output
		System.out.println("The distance between the two points is " + result);
		// System.out.printf("The distance between points (%.2f, %.2f) and (%.2f, %.2f): %f", x1, y1, x2, y2, result);
		
		// closing the Scanner object
		input.close();
	}
}
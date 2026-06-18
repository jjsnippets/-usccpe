// LE 1.2: Multiply the Digits
// Aug 22 2024
// multiplies the products of the digits in a number

// Sample program execution
// Enter a number between 0 and 1000: 932
//
// 2
// 3
// 9
// 
// The product of all digits in 932 is 54

// Intended program execution
// Enter a number between 0 and 1000: 932
// 9
// 3
// 2
// 
// The product of all digits in 932 is 54

package LE01;
import java.util.Scanner;

public class Multiplier {
	public static void main(String[] args) {
		// declarations
		int number, result = 1, current;
		Scanner input = new Scanner(System.in);
			
		// user prompt and input
		System.out.print("Enter a number between 0 and 1000: ");
		number = input.nextInt();
		int keep = number;
		System.out.println();
		input.close();
		
		// lesson: do not overcomplicate solutions; sometimes, brute force is quicker than a general solution

		for (; number > 0; number /= 10) {
			current = number % 10;
			result *= current;
			System.out.println(current);
		}
		
		// output
		System.out.println();
		System.out.println("The product of all digits in " + keep + " is " + result);
	}
}
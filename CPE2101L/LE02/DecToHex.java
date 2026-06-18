// LE 2.3: Dec to Hex
// Aug 29 2024
// converts a decimal number into a hexadecimal number
// uses built-in methods

// Sample program execution
// Enter a decimal number: 6702
// Hexadecimal number    : 1A2E


package LE02;
import java.util.Scanner;

public class DecToHex {
	public static void main(String[] args) {
		// declarations
		int number;
		Scanner input = new Scanner(System.in);
		
		// user prompt and input
		System.out.print("Enter a decimal number: ");
		number = input.nextInt();
		
		// output: using built-in methods 
		System.out.print("Hexadecimal number    : " + Integer.toHexString(number).toUpperCase());
		input.close();
	}
}

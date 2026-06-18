// LE 1.1: Change denomination
// Aug 20 2024
// calculates change from cents value

// Sample program execution
// Enter amount (1 - 99) of cents: 99
//
// Change is: 
// 3 quarters
// 2 dimes
// 0 nickels
// 4 pennies

package LE01;
import java.util.Scanner;

public class CoinChange {
	public static void main (String[] args){
		// declarations
		int cents;
		int quarters, dimes, nickels, pennies; 
		Scanner input = new Scanner(System.in);
		
		// user prompt and input
		System.out.print("Enter amount (1 - 99) of cents: ");
		cents = input.nextInt();
		System.out.println();
		
		// computes change (procedural code)
		quarters = cents / 25;
		cents -= quarters * 25;
		
		dimes = cents / 10;
		cents -= (dimes * 10);
	
		nickels = cents / 5;
		pennies = cents - (nickels * 5);
	
		// output
		System.out.println("Change is: ");
		System.out.println(quarters + " quarters");
		System.out.println(dimes + " dimes");
		System.out.println(nickels + " nickels");
		System.out.println(pennies + " pennies");
		
		// debug
		// System.out.printf("%d %d %d %d = %d", quarters, dimes, nickels, pennies, quarters * 25 + dimes * 10 + nickels * 5 + pennies);
		
		// closing the Scanner object
		input.close();
	}
}
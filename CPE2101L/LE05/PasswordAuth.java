// LE 5.3
// Oct 29 2024
// PIN Authentication system with randomized challenge-response system

/* Sample program execution
[A] SET PIN
[B] TEST PIN
[O] EXIT
 >> A

SET PIN TO? [5 DIGITS]
 >> 12345

PASSWORD SET TO 12345

[A] SET PIN
[B] TEST PIN
[O] EXIT
 >> B

PIN : 0 1 2 3 4 5 6 7 8 9 
NUM : 0 9 0 5 5 3 9 7 3 5 
ENTER PASSWORD >> 90553

CORRECT PASSWORD!

[A] SET PIN
[B] TEST PIN
[O] EXIT
 >> B

PIN : 0 1 2 3 4 5 6 7 8 9 
NUM : 2 5 1 6 7 9 7 4 4 5 
ENTER PASSWORD >> 22222

WRONG PASSWORD!

[A] SET PIN
[B] TEST PIN
[O] EXIT
 >> O

Closing PIN system!
*/

package LE05;

import java.util.Scanner;

public class PasswordAuth {
	// class attributes
	private String password;
	private static Scanner sc = new Scanner(System.in); // for convenience
	
	// default constructor
	
	// accessors and mutators
	private void setPassword(String pass) { this.password = pass; }
	private String getPassword() {
		return this.password;
	}
	
	// main method
	public static void main(String[] args) {
		// declarations
		PasswordAuth pass = new PasswordAuth();
		char choice;
		
		
		do {
			// user menu prompt
			System.out.println("[A] SET PIN");
			System.out.println("[B] TEST PIN");
			System.out.println("[O] EXIT");
			System.out.print(" >> ");
			
			choice = Character.toUpperCase(sc.nextLine().strip().charAt(0));
			System.out.println();
			
			switch (choice) {
				case 'A': // set PIN
					pass.setPassMenu();
					break;
				
				case 'B': // test PIN
					pass.enterPassMenu();
					break;
					
				case 'O': // exit
					break;
				
				default:
					System.out.println("INVALID INPUT!");
					System.out.println();
			}
		} while (choice != 'O');
		
		System.out.println("Closing PIN system!");
		System.out.println();
	}
	
	// provides a random assignment scheme
	// returns the corresponding password under this scheme
	private String challengePass() {
		int[] passNums = new int[5];
		char[] shuffle = new char[10];
		String ans;
		
		// converts type from String to int[]
		char[] temp = this.getPassword().toCharArray();
		for(int i = 0; i < 5; i++) {
			passNums[i] = Integer.valueOf(String.valueOf(temp[i]));
		}
		
		// generates a random assignment scheme
		for(int i = 0; i < 10; i++) {
			shuffle[i] = Character.forDigit(((int) (Math.random() * 10)), 10);
		}
		
		// mapping using assignment scheme
		for(int i = 0; i < 5; i++) {
			temp[i] = shuffle[passNums[i]];
		}
		ans = String.valueOf(temp);
		
		// print-out
		System.out.print("PIN : ");
		for(int i = 0; i < 10; i++)
			System.out.print(i + " ");
		System.out.println();
		
		System.out.print("NUM : ");
		for(char i : shuffle)
			System.out.print(i + " ");
		System.out.println();
		
		return ans;
	}
	
	// menu for setting the pin manually
	public void setPassMenu() {
		System.out.println("SET PIN TO? [5 DIGITS]");
		System.out.print(" >> ");

		this.setPassword(sc.nextLine().strip().substring(0, 5));
		System.out.println();
		
		System.out.println("PASSWORD SET TO " + this.getPassword());
		System.out.println();
	}
	
	// menu for entering the pin manually
	public void enterPassMenu() {
		String attempt;
		String soln = this.challengePass();
		System.out.print("ENTER PASSWORD >> ");
		
		attempt = sc.nextLine().strip();
		System.out.println();
		
		if(attempt.equals(soln)) {
			System.out.println("CORRECT PASSWORD!");
		} else {
			System.out.println("WRONG PASSWORD!");
		}
		System.out.println();
	}
}

// on-the-spot activity
// Aug 27 2024, 9:30AM - 10:00AM
// input name and displays in various formats

// assumptions
// last name is always the last word
// middle name is always the second to the last word
// all names are separated by spaces

// Sample program execution
// Input Complete Name: Fidel Valdez Ramos
//
// 1) Fidel V. Ramos
// 2) Ramos, F. V. 
// 3) FVRamos

package LE01;
import java.util.Scanner;

public class NameFormatter {
	public static void main(String[] args) {
		// declarations
		String fullName;
		String[] indivNames;
		Scanner input = new Scanner(System.in);
		
		// user prompt and input
		System.out.print("Input Complete Name: ");
		fullName = input.nextLine();
		indivNames = fullName.split(" ");
		System.out.println();

//		debugging
//		for(String x: indivNames) {
//			System.out.println(x);
//		}
//		System.out.println(indivNames.length);
		
		// format 1: first middleInitial last
		System.out.print("1) ");
		for(int i = 0; i < indivNames.length - 2; i++)
			System.out.print(indivNames[i] + " ");
		System.out.print(indivNames[indivNames.length - 2].charAt(0) + ". ");
		System.out.print(indivNames[indivNames.length - 1]);
		System.out.println();
		
		// format 2: Last, initials
		System.out.print("2) ");
		System.out.print(indivNames[indivNames.length - 1] + ", ");
		for(int i = 0; i < indivNames.length - 1; i++)
			System.out.print(indivNames[i].charAt(0) + ". ");
		System.out.println();
		
		// format 3: initials Last (no spaces in between)
		System.out.print("3) ");
		for(int i = 0; i < indivNames.length - 1; i++)
			System.out.print(indivNames[i].charAt(0));
		System.out.print(indivNames[indivNames.length - 1]);
		
		// clean-up
		input.close();
	}
}
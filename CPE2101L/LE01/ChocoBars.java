// LE 1.3: Chocolate Bars
// Aug 22 2024
// implements the Harris-Benedict equation

// Sample program execution
// Enter weight (in pounds): 92
// Enter height (in inches): 64
// Enter age: 20
//
// BMR for man: 1335.20 calories
// Equivalent to about 5.81 chocolate bars
// A 92" 64lb 20 year old man needs at most 6 chocolate bars to maintain weight
//
// BMR for woman: 1257.40 calories
// Equivalent to about 5.47 chocolate bars
// A 92" 64lb 20 year old woman needs at most 6 chocolate bars to maintain weight

package LE01;
import java.util.Scanner;

public class ChocoBars {
	public static void main(String[] args) {
		// declarations
		double weight, height;
		int age;
		double man, woman; 
		double manBars, womanBars;
		Scanner input = new Scanner(System.in);
		
		// user prompt and input
		System.out.print("Enter weight (in pounds): ");
		weight = input.nextDouble();
		
		System.out.print("Enter height (in inches): ");
		height = input.nextDouble();
		
		System.out.print("Enter age: ");
		age = input.nextInt();
		System.out.println();
		
		// calculations
		man = 66 + (6.3 * weight) + (12.9 * height) - (6.8 * age);
		woman = 655 + (4.3 * weight) + (4.7 * height) - (4.7 * age);
		
		manBars = man / 230;
		womanBars = woman / 230;
		
		// output
		System.out.printf("BMR for man: %.2f calories\n", man);
		System.out.printf("Equivalent to about %.2f chocolate bars\n", manBars);
		System.out.printf("A %.0f\" %.0flb %d year old man needs at most %d chocolate bars to maintain weight\n\n", weight, height, age, 1 + (int) manBars);
		
		System.out.printf("BMR for woman: %.2f calories\n", woman);
		System.out.printf("Equivalent to about %.2f chocolate bars\n", womanBars);
		System.out.printf("A %.0f\" %.0flb %d year old woman needs at most %d chocolate bars to maintain weight\n\n", weight, height, age, 1 + (int) womanBars);
		
		// closing the Scanner object
		input.close();
	}

}
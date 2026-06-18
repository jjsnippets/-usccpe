// LE 2.1: Day of the Week
// Aug 29 2024
// implements Zeller's congruence formula

// Sample program execution
// Enter year (e.g., 2012): 2015
// Enter month (1-12): 1
// Enter the day of month (1-31): 25
// Day of the week is Sunday


package LE02;

import java.util.Scanner;

public class DayOfWeek {

	public static void main(String[] args) {
		int h, q, m, y, j, k;
		Scanner input = new Scanner(System.in);
		
		System.out.print("Enter year (e.g., 2012): ");
		y = input.nextInt();
		System.out.print("Enter month (1-12): ");
		m = input.nextInt();
		System.out.print("Enter the day of month (1-31): ");
		q = input.nextInt();
		
		if (m == 1) {
			m = 13;
			y--;
		} else if (m == 2) {
			m = 14;
			y--;
		}
		
		j = y / 100;
		k = y % 100;
		
		h = (q + ((26*(m+1))/10) + k + (k/4) + (j/4) + (5*j)) % 7;
		System.out.print("Day of the week is ");
		
		switch(h) {
		case 0:
			System.out.print("Saturday");
			break;
		case 1:
			System.out.print("Sunday");
			break;
		case 2:
			System.out.print("Monday");
			break;
		case 3:
			System.out.print("Tuesday");
			break;
		case 4:
			System.out.print("Wednesday");
			break;
		case 5:
			System.out.print("Thursday");
			break;
		case 6:
			System.out.print("Friday");
			break;
		}
		
		input.close();
	}
}

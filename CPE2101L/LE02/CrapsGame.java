// bonus activity (unchecked)
// Aug 29 2024
// standard craps game implementation
// no interactivity

// Sample program execution
// You rolled 1 + 4 = 5
// Point is 5
// You rolled 5 + 4 = 9
// Point is 9
// You rolled 1 + 6 = 7
// You lose

package LE02;

public class CrapsGame {
	public static void main(String[] args) {
		int random1, random2, sum = 0, prev;
		
//		debug: outer loop for multiple rounds
//		for(int i = 0; i < 10; i++) {
//			System.out.println();

			while (true) {
				prev = sum;
				random1 = 1 + (int) (Math.random() * 6);
				random2 = 1 + (int) (Math.random() * 6);
				sum = random1 + random2;
				
				System.out.println("You rolled " + random1 + " + " + random2 + " = " + sum);
				
				// deals with the succeeding rolls
				if (prev > 0 && sum == 7) { // when 7 is rolled not on the first go, then lose
					System.out.println("You lose");
					break;
				} else if (prev == sum) { // when a number is rolled twice in a row, then win
					System.out.println("You win");
					break;
				// deals with the first few rolls
				} else if (sum == 7 || sum == 11) { // when 7 is rolled (on the first go)
					System.out.println("You win");  // or when 11 is rolled at any point, then win
					break;
				} else if (sum == 2 || sum == 3 || sum == 12) { // when 2, 3, or 12 is rolled at any point, then lose
					System.out.println("You lose");
					break;
				// repeat the roll
				} else
					System.out.println("Point is " + sum);
			}
//		}
	}
}

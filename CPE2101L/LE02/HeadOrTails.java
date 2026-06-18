// LE 2.2 Simulation: Heads or Tails
// Aug 29 2024
// simulates 2 million coin flips and shows results afterwards
// no interactivity

// Sample program execution
// For 2000000 flips of the coin:
// 1000210 were heads
// 999790 were tails


package LE02;

public class HeadOrTails {
	public static void main(String[] args) {
		final int FLIPS = 2000000;
		int heads = 0, tails = 0;
		
		
		for(int i = 0; i < FLIPS; i++) {
			int coin = (int) (Math.random() * 2);
			if (coin == 0)
				heads++;
			else
				tails++;
		}
		
		System.out.println("For " + FLIPS + " flips of the coin:");
		System.out.println(heads + " were heads");
		System.out.println(tails + " were tails");

	}
}

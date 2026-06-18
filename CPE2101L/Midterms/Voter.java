package Midterms;

import java.util.ArrayList;
import java.util.Scanner;

public class Voter {
	private static Scanner sc = new Scanner(System.in);

	// driver function for manual voting with a ballot
	public static void voterMenu(ArrayList<Candidate> candidates) {
		System.out.println("=== BALLOT ===");
		System.out.println("Reminder to always vote wisely!");
		System.out.println();

		// loop through all candidates
		for (Candidate candidate : candidates) {
			Voter.singleVote(candidate);
		}
	}
	
	// helper function to vote for a single candidate manually
	public static boolean singleVote(Candidate person) {
		char choice;
		boolean hasVoted = false, ret = false;
		
		do {
			// voter prompt and input for voting
			person.printOut();
			System.out.println("Vote for this person?");
			System.out.print("[Y/N] >> ");
			choice = sc.nextLine().strip().toUpperCase().charAt(0);
			System.out.println();
			
			// feedback to voter input
			if (choice == 'Y') {
				hasVoted = true;
				ret = true;
				person.incVotes();
				System.out.println("You voted for " + person.getName());
				
			}  else if (choice == 'N') {
				hasVoted = true;
				ret = false;
				System.out.println("You did not vote for " + person.getName());
				
			} else {
				System.out.println("Invalid selection!");
			}
			
			System.out.println();
		} while (!hasVoted);
		
			return ret;
	}

	// helper function to vote for a single candidate randomly
    public static boolean randomVote(Candidate person) {
        if (Math.random() > 0.5){ // 50% chance of voting for the candidate
			System.out.println("Voted for " + person.getName() + " as " + person.getPosition());
			person.incVotes();
			return true;
		} else {
			System.out.println("Did not vote for " + person.getName() + " as " + person.getPosition());
			return false;
		}
    }
}

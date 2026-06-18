package Midterms;

// used utilities
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Scanner;


public class Board {
	private static ArrayList<Candidate> candidates = new ArrayList<Candidate>();
	
	private static Scanner sc = new Scanner(System.in);
	
	public static void main(String[] args) {
		int choice;
		
		do {
			// system main menu
			System.out.println("Choose an action:");
			System.out.println("[1] New candidate");
			System.out.println("[2] Voter Ballot filling");
			System.out.println("[3] Show rankings");
			System.out.println("[4] Leave system");
			System.out.println();
			System.out.println("Or [0] to simulate a random election period");
			System.out.print(" >> ");
			choice = sc.nextInt();
			sc.nextLine();
			System.out.println();
			
			switch (choice) {
				case 0: // random automatic election simulation
					simulateElection();
					break;

				case 1: // add new candidate
					candidates.add(Candidate.newCandidateMenu());
					break;
					
				case 2: // manual voting
					Voter.voterMenu(candidates);
					break;
					
				case 3: // display election results
					Board.displayResults();
					break;
					
				case 4: // exit system
					System.out.println("Thank you for using the machine");
					System.out.println("Have a nice day! ");
					break;
					
				default:
					System.out.println("Invalid input!");
					System.out.println();
					break;
			}
		} while (choice != 4);
	}

	// helper function to get all unique positions
	private static HashSet<String> allPositions() {
		HashSet<String> res = new HashSet<String>();
		for(Candidate candidate : candidates) {
			res.add(candidate.getPosition());
		}
		return res;
	}

	// driver function that simulates an election
	private static void simulateElection(){
		char choice;

		do {
			// simulation menu
			System.out.println("Simulate with current candidates?");
			System.out.println("[Y] Yes, keep the candidate list as is");
			System.out.println("[N] No, create new ones");
			System.out.println("[C] Cancel operation");
			System.out.print(" >> ");
			choice = sc.nextLine().strip().toUpperCase().charAt(0);
			System.out.println();

			switch(choice){
				case 'N': // create new candidates
					System.out.println("Erasing data...");
					System.out.println();
					candidates = new ArrayList<Candidate>(); // clears candidates

					// adds preset candidates
					candidates.add(new Candidate("JOHN", "PRESIDENT"));
					candidates.add(new Candidate("JAKE", "PRESIDENT"));

					candidates.add(new Candidate("CHERRY", "VICE PRESIDENT"));
					candidates.add(new Candidate("CHARLIE", "VICE PRESIDENT"));

					candidates.add(new Candidate("ALEX", "SECRETARY"));
					candidates.add(new Candidate("ALICE", "SECRETARY"));
					candidates.add(new Candidate("AMY", "SECRETARY"));
					
					// then...

				case 'Y': // simulate with current candidates
					for (Candidate candidate : candidates) candidate.resetVotes();

					// size of the voting body
					int pop = (int) (Math.random() * 15) + 5;
					System.out.println("Voters population size: " + pop);
					System.out.println();

					// for each person, fill the ballot randomly
					for (int i = 0; i < pop; i++){
						System.out.println("Contents of ballot " + (i + 1) + ": ");
						for (Candidate candidate : candidates) {
							Voter.randomVote(candidate);
						}
						System.out.println();
					}

					// then display the results
					System.out.println();
					Board.displayResults();

					// reset votes
					for (Candidate candidate : candidates) candidate.resetVotes();

					// then...

				case 'C': // leaves simulation menu
					choice = 'C';
					break;

				default: // invalid input
					System.out.println("Invalid input!");
					System.out.println();
					break;
			}
		} while (choice != 'C');
	}
	
	// driver function that displays the election results
	public static void displayResults() {
		// declarations
		HashSet<String> allPositions = allPositions();
		int sumAll;

		System.out.println("$$$ ELECTION RESULTS $$$");
		
		// for each unique position
		for(String position : allPositions) {
			ArrayList<Candidate> inPosition = new ArrayList<Candidate>();
			sumAll = 0;
			
			// get all candidates with the same position
			for(Candidate candidate : candidates) {
				if(candidate.getPosition().equalsIgnoreCase(position)) {
					inPosition.add(candidate);
					sumAll += candidate.getVotes();
				}
			}

			// sort the candidates by votes
			Collections.sort(inPosition);
			
			// header
			System.out.println("=== " + position + " ===");
			System.out.println("Total votes: " + sumAll);
			
			if (sumAll == 0) sumAll = 1; // prevents division by zero
			
			// displays the candidate with that position and their votes by rank
			for(int i = 0; i < inPosition.size(); i++){
				Candidate candidate = inPosition.get(i);
				System.out.printf("%d) %-15s [%2d] (%.2f%%)\n", i + 1, candidate.getName(), candidate.getVotes(), ((float) candidate.getVotes()*100)/sumAll);
			}

			System.out.println();
		}
	}
}

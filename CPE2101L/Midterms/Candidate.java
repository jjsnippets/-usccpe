package Midterms;

import java.util.Scanner;

public class Candidate implements Comparable<Candidate>  {
	private String name;
	private String position;
	private int votes;

	private static Scanner sc = new Scanner(System.in);
	
	// constructor for user-defined name and position
	public Candidate(String name, String position) {
		this.setName(name);
		this.setPosition(position);
		this.resetVotes();

		this.printOut();
		System.out.println("Successfully added!");
		System.out.println();
	}
	
	// accessors and mutators
	public void setName(String name) { this.name = name; }
	public String getName() { return this.name; }
	
	public void setPosition(String position) { this.position = position; }
	public String getPosition() { return this.position; }
	
	public int getVotes() { return this.votes; }
	public void resetVotes() { this.votes = 0; }
	public void incVotes() { this.votes++; }
	
	// menu for creating a new candidate manually
	public static Candidate newCandidateMenu() {
		Candidate person;
		String name, position;
		
		System.out.print("Name of candidate >> ");
		name = sc.nextLine().strip().toUpperCase();
		System.out.print("Position of candidate >> ");
		position = sc.nextLine().strip().toUpperCase();
		System.out.println();
		
		System.out.println("Candidate information: ");
		person = new Candidate(name, position);
		
		return person;
	}
	
	// helper function to print out candidate information
	public void printOut() {
		System.out.println("Name: " + this.getName());
		System.out.println("Position: " + this.getPosition());
		
	}

	// compareTo method for sorting
	public int compareTo(Candidate y){
		return y.getVotes() - this.getVotes();
	}
}

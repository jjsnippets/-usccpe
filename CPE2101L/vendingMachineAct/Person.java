package vendingMachineAct;

public abstract class Person {
	// superclass for "people" classes, ie. Owner, Technician, Customer
	private String name; 
	private int wallet; // money in person
	
	// Person constructor
	public Person (String n, int w) {
		this.setName(n);
		this.setWallet(w);
	}
	
	// accessors and mutators
	public String getName() { return name; }
	public void setName(String name) { this.name = name; }
	
	public int getWallet() { return this.wallet; }
	public void setWallet(int amount) { this.wallet = amount; }
	public void incWallet(int amount) { this.wallet += amount; }
	public void decWallet(int amount) { this.wallet -= amount; }
}
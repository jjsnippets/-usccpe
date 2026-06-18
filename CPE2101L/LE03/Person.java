// LE 3.1: Person
// Sep 24 2024
// Demonstrates methods basics
// no interactivity

// Sample program execution ommited

package  LE03;

public class Person{
	// class attributes
	private String name;
	private int age;
	
	// class constructor
	public Person (String name, int age) {
		this.name = name;
		this.age = age;
	}
	
	// accessors and mutators
	String getName() { return this.name; }
	void setName(String name) { this.name = name; }
	
	int getAge() { return this.age; }
	void setAge(int age) { this.age = age; }
	
	// exercise-required methods
	boolean isEqual(Person p) {
		return this.sameName(p) && this.sameAge(p);
	}
	
	boolean sameName(Person p) {
		return this.name.equals(p.name);
	}
	
	boolean sameAge(Person p) {
		return this.age == p.age;
	}
	
	boolean isOlder(Person p) {
		return this.age > p.age;
	}
	
	boolean isYounger(Person p) {
		return this.age < p.age;
	}
	
	// support methods
	void printPerson() {
		System.out.println(this.name + ": " + this.age);
	}

	public static void main(String[] args) {
		// declarations
		Person alice = new Person("Alice", 10);
		Person bob = new Person("Bob", 20);
		Person charlie = new Person ("Charlie", 30);
		
		Person alison = new Person("Alice", 10);
		Person david = new Person ("David", 20);
		Person bobby = new Person ("Bob", 50);
		
		// display of object instances
		System.out.println("=== Object instances ===");
		System.out.print("alice > ");
		alice.printPerson();
		System.out.print("bob > ");
		bob.printPerson();
		System.out.print("charlie > ");
		charlie.printPerson();
		System.out.print("alison > ");
		alison.printPerson();
		System.out.print("david > ");
		david.printPerson();
		System.out.print("bobby > ");
		bobby.printPerson();
		System.out.println();
		
		// methods demonstration
		System.out.println("=== isEqual() method ===");
		System.out.print("alice.isEqual(alice) >> ");
		System.out.println(alice.isEqual(alice));
		System.out.print("alice.isEqual(alison) >> ");
		System.out.println(alice.isEqual(alison));
		System.out.print("alice.isEqual(bob) >> ");
		System.out.println(alice.isEqual(bob));
		System.out.println();
		
		System.out.println("=== sameName() method ===");
		System.out.print("bob.isEqual(bobby) >> ");
		System.out.println(bob.sameName(bobby));
		System.out.print("bob.isEqual(charlie) >> ");
		System.out.println(bob.sameName(charlie));
		System.out.println();
		
		System.out.println("=== sameAge() method ===");
		System.out.print("david.sameAge(bob) >> ");
		System.out.println(david.sameAge(bob));
		System.out.print("david.sameAge(charlie) >> ");
		System.out.println(david.sameAge(charlie));
		System.out.println();
		
		System.out.println("=== isOlder() method ===");
		System.out.print("bob.isOlder(alice) >> ");
		System.out.println(bob.isOlder(alice));
		System.out.print("bob.isOlder(charlie) >> ");
		System.out.println(bob.isOlder(charlie));
		System.out.println();
		
		System.out.println("=== isYounger() method ===");
		System.out.print("bob.isYounger(charlie) >> ");
		System.out.println(bob.isYounger(charlie));
		System.out.print("bob.isYounger(alice) >> ");
		System.out.println(bob.isYounger(alice));
		System.out.println();
	}
}
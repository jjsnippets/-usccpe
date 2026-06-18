package vendingMachineAct;

public class Drink {
	private String fullName;
	private int price;
	private int amount;

	// Drink constructor
	public Drink(String n, int p, int a) {
		this.setFullName(n);
		this.setPrice(p);
		this.setAmount(a);
	}
	
	// accessors and mutators
	public String getFullName() { return fullName; }
	public void setFullName(String fullName) { this.fullName = fullName; }

	public int getPrice() { return price;}
	public void setPrice(int price) { this.price = price; }
	
	public int getAmount() { return amount; }
	public void setAmount(int amount) { this.amount = amount; }
	public void decAmount() { this.amount--;}

	// other methods
	public static void printDrinks(Drink[] drinks, int count, String label){
		// [TABLE] prints the list of drinks of a vending machine
		System.out.printf("@@@ List of drinks in " + label + " @@@\n");
		System.out.printf("%-20s %-10s %-10s\n", "Drink", "Price", "Avaialable");

		for(int i = 0; i < count; i++) {
			System.out.printf("%-20s %-10d %-10d\n", drinks[i].getFullName(), drinks[i].getPrice(), drinks[i].getAmount());
		}

		System.out.println();
	}

	public static int matchDrinks(Drink[] drinks, int count, String name) {
		// [METHOD] returns index of drink if found, provides the next available slot if not
		int idx = count;
		for(int i = 0; i < count; i++) {
			if (drinks[i].getFullName().equalsIgnoreCase(name)) {
				idx = i;
				break;
			}
		}
		return idx;
	}
}
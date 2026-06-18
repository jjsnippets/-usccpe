package vendingMachineAct;

public class Machine {
	private static int count = 0; // total number of machines
	private Drink[] drinks = new Drink[MainExec.MAX_OBJECTS]; // list of drinks in a machine
	private int drinkCount = 0; // number of drinks in a machine
	private String label, owned, password;
	private int credit, profit;

	// Machine constructor
	public Machine(String l, String o, String p) {
		this.setLabel(l);
		this.setOwned(o);
		this.setPassword(p);
		Machine.incCount();
	}

	// accessors and mutators
	public static int getCount() { return Machine.count; }
	public static void incCount() { Machine.count++; }

	public Drink[] getDrinks() { return this.drinks; }

	public int getDrinksCount() { return this.drinkCount; }
	public void incDrinksCount() { this.drinkCount++; }

	public String getLabel() { return label; }
	public void setLabel(String label) { this.label = label; }

	public String getOwned() { return owned; }
	public void setOwned(String owned) { this.owned = owned; }

	public String getPassword() { return password; }
	public void setPassword(String password) { this.password = password; }

	public int getCredit() { return this.credit; }
	public void incCredit(int amount) { this.credit += amount; }
	public void decCredit(int amount) { this.credit -= amount; }

	public int getProfit() { return this.profit; }
	public void setProfit(int amount) { this.profit = amount; }
	public void incProfit(int amount) { this.profit += amount; }

	// other methods
	public static void printMachines(Machine[] machines) {
		// [TABLE] prints the list of all machines, excluding owner and profit information
		System.out.println("@@@ List of Machines @@@");
		System.out.printf("no %-15s%-10s%-10s\n", "Label", "Owned", "Profit");
		for(int i = 0; i < Machine.getCount(); i++) {
			System.out.printf("%02d %-15s%-10s%-10d\n", (i + 1), machines[i].getLabel(), machines[i].getOwned(), machines[i].getProfit());
		}
		System.out.println();
	}

	private static int matchMachine(Machine[] machines, String label) {
		// [METHOD] returns index of machine if found, -1 otherwise
		// {overloaded method}
		int idx = -1;
		for(int i = 0; i < Machine.getCount(); i++) {
			if (machines[i].getLabel().equalsIgnoreCase(label)) {
				idx = i;
				break;
			}
		}
		return idx;
	}

	public static int matchMachine(Machine[] machines) {
		// [PROMPT] user interface for matching machines
		// returns index of machine if successful, -1 otherwise
		// {overloaded method}
		int idx;
		String label;

		Machine.printMachines(machines);

		System.out.println("Which machine to choose?");
		System.out.print(" >> ");
		label = MainExec.input.nextLine();
		idx = matchMachine(machines, label);

		if (idx == -1) {
			System.out.println("Machine not found!");
		}
		System.out.println();

		return idx;
	}

	public boolean passwordCheck() {
		// [PROMPT] returns TRUE if password matches, FALSE otherwise
		String pass;
		
		System.out.print("Enter password >> ");
		pass = MainExec.input.nextLine();
		System.out.println();

		if (this.getPassword().equals(pass)) return true;
		return false;
	}

	public static int newMachine(Machine[] machines, String owner){
		// [PROMPT] creates a new machine
		// returns index of new machine if successful, -1 otherwise
		String label, pass;
		char check;
		int idx = Machine.getCount();
		if (idx == MainExec.MAX_OBJECTS) {
			System.out.println("Maximum number of machines reached!");
			return -1;
		}

		System.out.print("Name of new machine >> ");
		label = MainExec.input.nextLine();

		System.out.print("Machine Password >> ");
		pass = MainExec.input.nextLine();
		System.out.println();

		System.out.println("Are you sure with these details?");
		System.out.println("WARNING This action cannot be undone!");
		System.out.println("Machine Name: " + label);
		System.out.println("Machine Password: " + pass);
		System.out.print("(y/n) >> ");

		check = MainExec.input.nextLine().charAt(0);
		System.out.println();

		if (check == 'y') {
			machines[idx] = new Machine(label, owner, pass);
			System.out.println("Machine " + label + " created successfully!");
			System.out.println();
			return idx;

		} else {
			System.out.println("Machine creation cancelled!");
			return -1;
		}
	}

	public static int loginMachine(Machine[] machines){
		// [PROMPT] user interface for logging in a machine in maintance mode
		// returns index of machine if successful, -1 if not
		int idx;

		idx = matchMachine(machines);
		if (idx == -1) return -1;

		if (machines[idx].passwordCheck()) {
			System.out.println("Login successful!");
			System.out.println();
			return idx;
		} else {
			System.out.println("Incorrect password!");
			System.out.println();
			return -1;
		}
	}

	public void maintananceMenu() {
		// [MENU] user interface for machine maintainance
		char selection;
		String label = this.getLabel();
		
		do {
			System.out.println("### Maintainance: " + label + " ###");
			System.out.println("Profit: " + this.getProfit());
			System.out.println("[1] See list of drinks");
			System.out.println("[2] Refill inventory");
			System.out.println("[3] Change price of drink");
			System.out.println("[4] Leave " + label);
			System.out.print(" >> ");
			
			selection = MainExec.input.nextLine().toLowerCase().charAt(0);
			System.out.println();
			
			switch (selection) {
				case '1': // See list of drinks
					Drink.printDrinks(this.getDrinks(), this.getDrinksCount(), label);
					break;
					
				case '2': // Refill inventory
					this.refillInventory();
					break;
				
				case '3': // Change price of drink
					this.changePrice();
					break;
					
				case '4':
					break;
					
				default:
					System.out.println("Invalid selection [" + selection + "]!");
					System.out.println();
					break;
					
			} // end switch
		} while (selection != '4');

		System.out.println("Leaving " + label + "...");
		System.out.println();
	}

	private void refillInventory() {
		// [PROMPT] refill inventory of drinks
		// returns 0 if successful, -1 otherwise

		int idx, drinkCount = this.getDrinksCount();
		String drinkName;
		int amount, price;
		char check;
		Drink[] drinks = this.getDrinks();

		Drink.printDrinks(drinks, drinkCount, this.getLabel());

		System.out.print("Name of drink >> ");
		drinkName = MainExec.input.nextLine();

		idx = Drink.matchDrinks(drinks, drinkCount, drinkName);

		if (idx == drinkCount){
			System.out.println("Are you sure you want to add a new drink?");
			System.out.print("(y/n) >> ");

			check = MainExec.input.nextLine().charAt(0);
			System.out.println();

			if (check == 'n') {
				System.out.println("Drink creation cancelled!");
				System.out.println();
				return;
			}

			System.out.print("Set price of " + drinkName + " >> ");
			price = MainExec.input.nextInt();
			System.out.print("Number of " + drinkName + " to stock >> ");
			amount = MainExec.input.nextInt();
			MainExec.input.nextLine();
			System.out.println();

			drinks[idx] = new Drink(drinkName, price, amount);
			this.incDrinksCount();

			System.out.println("Added " + drinks[idx].getFullName() + " to " + this.getLabel() + "!");
			System.out.println();

		} else {
			System.out.print("Number of " + drinkName + " to stock >> ");
			amount = MainExec.input.nextInt();
			MainExec.input.nextLine();
			System.out.println();

			drinks[idx].setAmount(drinks[idx].getAmount() + amount);
			System.out.println("Refilled " + drinks[idx].getFullName() + " by " + amount + "!");
			System.out.println();
		}
	}

	private void changePrice() {
		// [PROMPT] user interface for changing price of a drink
		// returns index of drink if successful, -1 if not
		
		int idx, drinkCount = this.getDrinksCount();
		String drinkName;
		int price;
		Drink[] drinks = this.getDrinks();

		Drink.printDrinks(drinks, drinkCount, this.getLabel());

		System.out.print("Name of drink to change price of >> ");
		drinkName = MainExec.input.nextLine();

		idx = Drink.matchDrinks(drinks, drinkCount, drinkName);

		if (idx == drinkCount){
			System.out.println("Drink not found!");
			System.out.println();
			return;
		}

		System.out.print("Set price of " + drinkName + " >> ");
		price = MainExec.input.nextInt();
		MainExec.input.nextLine();
		System.out.println();

		drinks[idx].setPrice(price);
		System.out.println("Changed price of " + drinks[idx].getFullName() + " to " + price + "!");
		System.out.println();
	}

	public void customerMenu(Customer customer) {
		// [MENU] customer facing vending machine menu
		char selection;
		String label = this.getLabel();
		
		do {
			System.out.println("### Vending Machine: " + label + " ###");
			System.out.println("Credits: " + this.getCredit());
			System.out.println("[1] Insert coins");
			System.out.println("[2] View and purchase drinks");
			System.out.println("[3] Withdraw and leave " + label);
			System.out.print(" >> ");
			
			selection = MainExec.input.nextLine().toLowerCase().charAt(0);
			System.out.println();
			
			switch (selection) {
				case '1': // Insert coins
					this.insertCoins(customer);
					break;
					
				case '2': // View and purchase drinks
					this.purchaseDrinks(customer);
					break;
					
				case '3':
					break;
					
				default:
					System.out.println("Invalid selection [" + selection + "]!");
					System.out.println();
					break;
					
			} // end switch
		} while (selection != '3');

		if (this.getCredit() > 0) {
			System.out.println("You withdrew " + this.getCredit() + " and left " + label);
		} else {
			System.out.println("You left " + label);
		}
		System.out.println();

		customer.incWallet(this.getCredit());
		this.decCredit(this.getCredit());
	}

	private void insertCoins(Customer customer) {
		// [MENU] user interface for inserting coins
		int amount;
		
		System.out.println("How much coins to insert?");
		System.out.print(" >> ");
		
		amount = MainExec.input.nextInt();
		MainExec.input.nextLine();
		System.out.println();

		if (customer.getWallet() >= amount){
			customer.decWallet(amount);
			this.incCredit(amount);
			System.out.println("Increased machine credits by " + amount + "!");

		} else {
			System.out.println("You do not have enough money (of " + customer.getWallet() + ")!");
		
		}
		System.out.println();
	}
	
	private void purchaseDrinks(Customer customer) {
		// [PROMPT] user interface for purchasing drinks
		int idx, drinkCount = this.getDrinksCount();
		String drinkName;
		int price, credit;
		Drink[] drinks;
		drinkCount = this.getDrinksCount();
		drinks = this.getDrinks();

		do {
			credit = this.getCredit();

			Drink.printDrinks(drinks, drinkCount, this.getLabel());

			System.out.println("Name of drink to purchase");
			System.out.println("or type \"exit\" to stop purchasing drinks");
			System.out.print(" >> ");
			drinkName = MainExec.input.nextLine();
			System.out.println();
			
			if (drinkName.strip().equalsIgnoreCase("exit")) return; // exit condition

			idx = Drink.matchDrinks(drinks, drinkCount, drinkName);

			if (idx == drinkCount){  // if drink not found
				System.out.println("No drinks match your selection!");
				System.out.println();

			} else {
				int stock = drinks[idx].getAmount();
				price = drinks[idx].getPrice();
				
				if (stock == 0) { // if drink is out of stock
					System.out.println("Sorry but " + drinkName + " is out of stock!");
					System.out.println();
					
				} else if (credit < price) { // if not enough machine credits
					System.out.println("Not enough credits (of " + credit + ")!");
					System.out.println();
					
				} else {
					drinks[idx].decAmount();
					System.out.println("You took " + drinks[idx].getFullName() + " out of " + this.getLabel() + "!");
					System.out.println();
					this.incProfit(price);
					this.decCredit(price);
				}
			}

		} while (true); // if (drinkName.strip().equalsIgnoreCase("exit")) return;
	}
}
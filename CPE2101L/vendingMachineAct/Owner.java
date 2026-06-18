package vendingMachineAct;

public class Owner extends Person {
	private static int count = 0; // total number of owners
	private String password;
	
	// Owner constructor
	public Owner(String n, String p) {
		super(n, 0);
		this.setPassword(p);
		Owner.incCount();
	}

	// accessors and mutators
	public static int getCount() { return count; }
	public static void incCount() { Owner.count++; }

	public String getPassword() { return this.password; }
	public void setPassword(String password) { this.password = password; }

	// other methods
	public static void printOwners(Owner[] owners){
		// [TABLE] prints the list of owners
		System.out.println("@@@ List of Owners @@@");
		for(int i = 0; i < Owner.getCount(); i++) {
			System.out.println((i + 1) + ": " + owners[i].getName());
		}
		System.out.println();
	}

	public static int matchOwner(Owner[] owners, String name) {
		// [METHOD] returns index of owner if found, -1 if not
		int idx = -1;
		for(int i = 0; i < Owner.getCount(); i++) {
			if (owners[i].getName().equalsIgnoreCase(name)) {
				idx = i;
				break;
			}
		}
		return idx;
	}

	public boolean passwordCheck() {
		// [PROMPT] returns TRUE if password matches, FALSE otherwise
		String pass;
		
		System.out.print("Enter password >> ");
		pass = MainExec.input.nextLine();
		System.out.println();

		if (this.getPassword().equals(pass)) return true;
		else return false;
	}

	public static void ownerScreen(Owner[] owners, Machine[] machines) {
		// [MENU] initial owner mode menu
		int idx;
		char selection;
		
		do {
			System.out.println("### Owner Mode ###");
			System.out.println("[1] Create new owner");
			System.out.println("[2] Log in as an existing owner");
			System.out.println("[3] Exit owner mode");
			System.out.print(" >> ");
			
			selection = MainExec.input.nextLine().toLowerCase().charAt(0);
			System.out.println();
			
			switch (selection) {
				case '1': // Create new owner
					idx = Owner.newOwner(owners);
					if (idx == -1) break;

					owners[idx].existingOwnerMenu(machines);
					break;

				case '2': // Log in as an existing owner
					idx = Owner.loginOwner(owners);
					if (idx == -1) break;

					owners[idx].existingOwnerMenu(machines);
					break;
				
				case '3': // exit owner mode
					break;
					
				default:
					System.out.println("Invalid selection [" + selection + "]!");
					System.out.println();
					break;
					
			} // end switch
		} while (selection != '3');

		System.out.println("Exiting owner mode...");
		System.out.println();
	}

	public static int newOwner(Owner[] owners) {
		// [PROMPT] creates a new owner
		// returns index of new owner if successful, -1 otherwise
		String name, pass;
		char check;

		System.out.print("Name of new owner >> ");
		name = MainExec.input.nextLine();

		System.out.print("Set password >> ");
		pass = MainExec.input.nextLine();
		System.out.println();

		System.out.println("Are you sure with these details?");
		System.out.println("WARNING This action cannot be undone!");
		System.out.println("Name: " + name);
		System.out.println("Password: " + pass);
		System.out.print("(y/n) >> ");

		check = MainExec.input.nextLine().toLowerCase().charAt(0);
		System.out.println();

		if (check == 'y') {
			owners[Owner.count] = new Owner(name, pass);
			System.out.println("New owner created!");
			System.out.println();
			return (Owner.getCount() - 1);

		} else {
			System.out.println("New owner creation cancelled!");
			System.out.println();
			return -1;
		}
	}

	public static int loginOwner(Owner[] owners){
		// [PROMPT] selects an existing owner in the list of owners
		// returns index of owner if successful, -1 if not
		String name;
		int idx;
		printOwners(owners);

		System.out.print("Name of owner >> ");
		name = MainExec.input.nextLine();

		idx = matchOwner(owners, name);

		if (idx == -1) {
			System.out.println("Owner not found!");
			System.out.println();
			return -1;
		}

		if (owners[idx].passwordCheck()) {
			System.out.println("Login successful!");
			System.out.println();
			return idx;
		} else {
			System.out.println("Incorrect password!");
			System.out.println();
			return -1;
		}
	}

	public void existingOwnerMenu(Machine[] machines) {
		// [MENU] owner mode menu as this.getName()
		String name = this.getName();
		char selection;
		int idx;
		
		System.out.println("Good day, " + name + "!");
		System.out.println();

		do {
			System.out.println("=== Owner Mode: " + name + " ===");
			System.out.println("You currently have " + this.getWallet() + " as profit.");
			System.out.println("[1] See all machines");
			System.out.println("[2] Add new machine");
			System.out.println("[3] Enter machine maintenance mode");
			System.out.println("[4] Collect profit from machine");
			System.out.println("[5] Exit as " + name);
			System.out.print(" >> ");

			selection = MainExec.input.nextLine().charAt(0);
			System.out.println();

			switch(selection) {
				case '1': // See all machines
					Machine.printMachines(machines);
					break;

				case '2': // Add new machine
					idx = Machine.newMachine(machines, new String(name));
					if (idx == -1) break;

					// automatically enters maintenance mode for machine
					machines[idx].maintananceMenu();
					break;

				case '3': // Enter machine maintenance mode
					idx = Machine.loginMachine(machines);
					if (idx == -1) break;

					machines[idx].maintananceMenu();
					break;

				case '4': // Collect profit from machine
					this.collectProfit(machines);
					break;

				case '5':
					break;

				default:
					System.out.println("Invalid selection [" + selection + "]!");
					System.out.println();
					break;
			}
		} while (selection != '5');

		System.out.println("Have a nice day " + name + "!");
		System.out.println();
	}

	public void collectProfit(Machine[] machines) {
		// [PROMPT] collects profit from a machine
		int idx, profit;

		idx = Machine.matchMachine(machines);
		if (idx == -1) return;

		if (machines[idx].passwordCheck()) {
			profit = machines[idx].getProfit();
			this.incWallet(profit);
			System.out.println("Profit of " + profit + " collected!");
			machines[idx].setProfit(0);
			System.out.println();

		} else {
			System.out.println("Incorrect password!");
			System.out.println();
		}
	}
}
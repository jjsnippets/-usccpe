package vendingMachineAct;

public class Customer extends Person {
	// Customer constructor
	public Customer(String n, int w) {
		super(n, w);
	}
	
	// other methods
	public static void customerScreen(Machine[] machines) {
		// [MENU] initial customer mode menu
		String name;
		int idx, coins;
		char selection;
		
		System.out.println("You rush outside and grab your id hanging on the door");
		System.out.println("What is your name?");
		System.out.print(" >> ");
		name = MainExec.input.nextLine();
		System.out.println();
		
		
		System.out.println("You look at your wallet and see some amount of money");
		System.out.println("How much is in it?");
		System.out.print(" >> ");
		coins = MainExec.input.nextInt();
		MainExec.input.nextLine();
		System.out.println();
		
		Customer customer = new Customer(name, coins);
		
		do {
			name = customer.getName();
			coins = customer.getWallet();
			System.out.println("### Customer subconcious: " + name + " ###");
			System.out.println("You have " + coins + " in hand");
			System.out.println("[1] Peruse machines");
			System.out.println("[2] Leave machines");
			System.out.print(" >> ");
			
			selection = MainExec.input.nextLine().toLowerCase().charAt(0);
			System.out.println();
			
			switch (selection) {
				case '1': // Select a machine
					idx = Machine.matchMachine(machines);
					if (idx == -1) break;
					
					machines[idx].customerMenu(customer);
					break;

				case '2': // Leave machines altogether
					break;
					
				default:
					System.out.println("Invalid selection [" + selection + "]!");
					System.out.println();
					break;
					
			} // end switch
		} while (selection != '2');

		System.out.println("You left the alley-way running, as you were late...");
		System.out.println();
	}
}
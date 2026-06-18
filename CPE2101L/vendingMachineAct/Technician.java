package vendingMachineAct;

public class Technician extends Person{
	// Technician constructor
	public Technician(String n) {
		super(n, 0);
	}
	
	// other methods
	public static void technicianScreen(Machine[] machines) {
		// [MENU] initial technician mode menu
		String name;
		char selection;

		do {
			System.out.println("### Technician Mode ###");
			System.out.println("[1] Log in as a technician");
			System.out.println("[2] Exit technician mode");
			System.out.print(" >> ");

			selection = MainExec.input.nextLine().toLowerCase().charAt(0);
			System.out.println();

			switch (selection) {
				case '1': // Log in as a technician
					System.out.print("Enter name >> ");
					name = MainExec.input.nextLine();
					System.out.println();
					existingTechnicianMenu(name, machines);
					break;
					
				case '2': // Exit technician mode
					break;
					
				default:
					System.out.println("Invalid selection [" + selection + "]!");
					System.out.println();
					break;
					
			} // end switch
		} while (selection != '2');

		System.out.println("Leaving technician mode...");
		System.out.println();
	}

	public static void existingTechnicianMenu(String name, Machine[] machines) {
		// [MENU] technician menu for technician named 'name'
		System.out.println("Welcome " + name + "!");
		System.out.println();

		char selection;
		int idx;
		
		do {
			System.out.println("=== Technician Mode: " + name + " ===");
			System.out.println("[1] See list of machines");
			System.out.println("[2] Refill inventory of machine");
			System.out.println("[3] Exit as " + name);
			System.out.print(" >> ");
			
			selection = MainExec.input.nextLine().toLowerCase().charAt(0);
			System.out.println();
			
			switch (selection) {
				case '1': // See list of machines
					Machine.printMachines(machines);
					break;
					
				case '2': // Refill inventory of machine
					idx = Machine.loginMachine(machines);
					if (idx == -1) break;

					machines[idx].maintananceMenu();
					break;
					
				case '3': // Exit as 'name'
					break;
					
				default:
					System.out.println("Invalid selection [" + selection + "]!");
					System.out.println();
					break;
					
			} // end switch
		} while (selection != '3');
	}
}
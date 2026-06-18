package vendingMachineAct;

import java.util.Scanner;
 

public class MainExec {
	static final int MAX_OBJECTS = 30;
	static Scanner input = new Scanner(System.in);

	public static void main(String[] args) {
		Owner[] owners = new Owner[MAX_OBJECTS]; // shared array of owners
		Machine[] machines = new Machine[MAX_OBJECTS]; // shared array of machines
		char selection;
		
		do {
			System.out.println("Run as:");
			System.out.println("[1] Customer");
			System.out.println("[2] Technician");
			System.out.println("[3] Owner");
			System.out.println("[4] Terminate program");
			System.out.print(" >> ");

			selection = input.nextLine().toLowerCase().charAt(0);
			System.out.println();

			switch (selection) {
				case '1': // Customer mode
					Customer.customerScreen(machines);
					break;
					
				case '2': // Technician mode
					Technician.technicianScreen(machines);
					break;
				
				case '3': // Owner mode
					Owner.ownerScreen(owners, machines);
					break;
					
				case '4':
					break;
					
				default:
					System.out.println("Invalid mode [" + selection + "] selected!");
					System.out.println();
					break;

			} // end switch
		} while (selection != '4');
		
		System.out.println("Turning off...");
		System.out.println();
	}
}
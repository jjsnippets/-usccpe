// author: Joshua Sarcol
// contains main() method

package LE04;

import java.util.Scanner;

public class main {
    static Scanner input = new Scanner(System.in);

    public static void main(String[] args) {
        // declarations and initializations
        CashRegister credit = new CashRegister();
        DispenserType[] products = new DispenserType[4];
        char choice;
        boolean isSold;

        // set-up for the dispensers
        dispenserSetup(products);

        // initial welcome message
        System.out.println("Welcome to the Fruit Juice Machine!");
        System.out.println();

        // main menu loop
        do {
            // display products and other options
            choice = showSelection(products);
            
            // switch-case for user choice
            switch (choice) {
                case '1':
                case '2':
                case '3':
                case '4':
                    isSold = sellProduct(products[Character.getNumericValue(choice) - 1], credit);
                    if (isSold){
                        System.out.println("You bought " + DispenserType.productName(Character.getNumericValue(choice) - 1) + "!");
                        System.out.println("Enjoy and thank you for your purchase!");
                    }  
                    break;
                case 's':
                    System.out.println("Machine profit: " + credit.getProfit());
                    break;
                case 'e':
                    System.out.println("Thank you for using the Fruit Juice Machine!");
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
                    break;
            }
            System.out.println();

        } while (choice != 'e');
    }

    // initializes values for the dispensers / products
    public static void dispenserSetup(DispenserType[] products) {
        System.out.println("\n=== Setting Up Products ===\n");

        char choice;
        int cost, stock;

        for (int i = 0; i < products.length; i++) {
            //Would it be better if we said 'currently stocking' instead for the user to understand it better?
            //System.out.println("Currently Stocking: " + DispenserType.productName(i));
            
            System.out.println("[" + (i + 1) + "/4] " + DispenserType.productName(i));
            System.out.println("[a] Default values: cost -> 50, stock -> 50");
            System.out.println("[b] Custom values");
            System.out.print("\nSelect Stock Values >> ");

            choice = input.nextLine().toLowerCase().charAt(0);

            // if default values
            if (choice == 'a') {
                products[i] = new DispenserType();
            
            // otherwise
            } else {
                System.out.print("How much to stock? >> ");
                stock = input.nextInt();
                System.out.print("What is it's cost? >> ");
                cost = input.nextInt();
                products[i] = new DispenserType(stock, cost);

                input.nextLine();
            }
            System.out.println();
        }

        System.out.println();
    }

    // displays the products and other options
    public static char showSelection(DispenserType[] products) {
        char choice;
        System.out.println("=== Fruit Juice Machine ===\n");
        DispenserType.displayProducts(products);
        System.out.println("\nMACHINE OPERATIONS: ");
        System.out.println("[s] Display machine profit");
        System.out.println("[e] Leave the machine");
        System.out.print("\nInput choice >> ");
        choice = input.next().charAt(0);

        System.out.println();
        
        return choice;
    }

    // function to sell a product
    // returns false if no sale was made, true otherwise
    public static boolean sellProduct(DispenserType product, CashRegister credit) {
        // declarations
        int cost = product.getCost();
        int deposit, rem;
        credit.reduceAmount(credit.getCurrentBalance());

        // The first thing that this function does is check whether the dispenser holding
        // the product is empty. If the dispenser is empty, the function informs the customer
        // that this product is sold out
        if (product.getNoOfItems() == 0) {
            System.out.println("Sorry but this product is sold out\n");
            return false;
        }

        // If the dispenser is not empty, it tells the user to deposit the necessary amount
        // to buy the product.
        System.out.println("You need to deposit " + cost + " to buy this product");
        System.out.print("How much to deposit? >> "); // first attempt
        deposit = input.nextInt();
        credit.acceptAmount(deposit);
        System.out.println();

        // If the user does not deposit enough money to buy the product, it tells the user
        // how much additional money must be deposited.
        if (deposit < cost) {
            rem = cost - deposit;
            System.out.println("You need to deposit " + rem + " more to buy this product");
            System.out.println("Last attempt to deposit the remaining amount");
            System.out.print("How much to deposit? >> "); // second attempt
            deposit = input.nextInt();
            credit.acceptAmount(deposit);

            // If the user fails to deposit enough money, in two tries, to buy the product,
            // the function simply returns the money.
            if (credit.getCurrentBalance() < cost) {
                System.out.println("Sorry but you do not have enough credit!\n");
                System.out.println("Returning " + credit.getCurrentBalance() + "...\n");
                credit.reduceAmount(credit.getCurrentBalance());
                return false;
            }
        }

        // If the amount deposited by the user is sufficient, it accepts the money and sells
        // the product.
        credit.incProfit(cost);
        product.makeSale();
        System.out.println("Returning " + credit.getCurrentBalance() + "...\n");
        credit.reduceAmount(credit.getCurrentBalance());
        return true;
    }
}

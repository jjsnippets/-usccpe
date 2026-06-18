// author: Clarque Aloba

package LE04;

public class DispenserType {
    private int numberOfItems;
    private int cost;

    // no status printouts should be made here, only tabular printouts
    // try using this. to make code more readable
    // add comments as necessary

    public DispenserType() {
        numberOfItems = 50;
        cost = 50;
    }

    // Initializes the dispenser by setting their item count and respective costs.
    public DispenserType(int setNoOfItems, int setCost) {
        if (setNoOfItems >= 0){
            this.numberOfItems = setNoOfItems;
        } else {
            this.numberOfItems = 0; // no negatives
        }
        if (setCost >= 0) {
            this.cost = setCost;
        } else {
            this.cost = 0; // no negatives
        }
    }

    public void makeSale() {
        if (numberOfItems > 0){
            numberOfItems--;
        } else {
            System.out.println("Item Sold Out"); 
        }
    }

    public int getNoOfItems() {
        return this.numberOfItems;
    }

    public int getCost() {
        return this.cost;
    }

    // try using this. to make it more readable
    public void makeSale(int amount) {
        if (numberOfItems > 0){
            if (amount >= cost) {
                numberOfItems--;
                int change = amount - cost;
                  System.out.println("Your change is: " + change);
                 System.out.println("Here's your drink! Enjoy!");
            } else {
                 System.out.println("Insufficient Funds. Item Costs: " + cost);
                 System.out.println("You currently have: " + amount);
                 System.out.println((cost-amount) + " cents needed.");
            }
        } else {
             System.out.println("Item Sold Out");   
        }
    }

    // use productName() to display name of product along with stock and cost
    public static void displayProducts(DispenserType[] products) {
        System.out.println("PRODUCTS:");
        for (int i = 0; i < products.length; i++){
            System.out.println("[" + (i + 1) + "] " + productName(i) + ": " + products[i].getNoOfItems() + " items || cost " + products[i].getCost());
        }
    }

    public static String productName(int i) {
        switch (i) {
            case 0:
                return "Apple Juice";
            case 1:
                return "Orange Juice";
            case 2:
                return "Mango Lassi";
            case 3:
                return "Fruit Punch";
            default:
                return "Unknown";
        }
    }
}

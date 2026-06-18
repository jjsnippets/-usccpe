// author: Enzo Basuil

package LE04;

public class CashRegister {
    private int cashOnHand;
    private int profit;

    // some methods are not used, remove as necessary
    // add comments as necessary

    //Sets the value of cashOnHand to a certain value.
    public void setCurrentBalance(int newBalance){
        this.cashOnHand = newBalance;
    }

    //Gets the value of cashOnHand and makes it accessible. 
    public int getCurrentBalance() {
        return this.cashOnHand;
    }

    public CashRegister() {
        setCurrentBalance(500);
        this.profit = 0;
    }

    public CashRegister(int cashIn) {
        setCurrentBalance(cashIn);
    }

    //Updates and increases the value of cashOnHand
    public void acceptAmount(int amountIn) {
        setCurrentBalance(getCurrentBalance() + amountIn);
    }

    //Updates and decreases the value of cashOnHand
    public void reduceAmount(int amountOut) {
        setCurrentBalance(getCurrentBalance() - amountOut);
    }

    //Shows the user their current balance.
    public static void displayBalance(CashRegister cashRegister) {
        System.out.println("Your current balance is: " + cashRegister.getCurrentBalance());
    }

    // The cash register should also be able to show the juice machine’s owner the amount
    // of money in the register at any given time. (profit)
    public void incProfit(int amount) {
        this.profit += amount;
        // profit should also decrement machine credit
        setCurrentBalance(getCurrentBalance() - amount);
    }

    //This gets the value of profit and makes it accessible.
    public int getProfit() {
        return this.profit;
    }
}

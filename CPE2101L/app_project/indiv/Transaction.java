// A "reciept" class for a single transaction

package indiv;

import group.Stock;

public class Transaction {
    private Stock items;       // treat like a "cart" during a transaction
    private String customer;
    private int date;
    private double payment;    // Payment made by the customer
    private double worth;      // Worth of the cart

    // constructor for date only
    public Transaction(int date) {
        this.items = new Stock();  // empty cart
        this.setCustomer("NO_NAME");
        this.setDate(date);
        this.setPayment(0);
        this.setWorth(0);
    }

    public Stock getItems() { return items; }
    // adding/removing items from the cart
    public void addItem(Item item) { this.items.put(item.getName(), item); } // potential bug: if the item changes price in the middle
    public void removeItem(Item item) { this.items.remove(item.getName()); } //  of a purchase, then removeItem() will not remove item

    public String getCustomer() { return this.customer; }
    public void setCustomer(String name) { this.customer = name.strip(); }

    public int getDate() { return this.date; }
    public void setDate(int date) { this.date = Math.max(0, date); }

    public double getPayment() { return this.payment; }
    public void setPayment(double payment) { this.payment = payment; }

    public double getWorth() { return this.worth; }
    public void setWorth(double worth) { this.worth = worth; }
    public void incWorth(double worth) { this.worth += worth; }
    public void decWorth(double worth) { this.worth -= worth; }

    public double getRevenue() { return this.getPayment() - this.getWorth(); }

    public String toString() {
        String output = String.format(" %-15s %-15s %10s %5s %10s\n", "Name", "Category", "Price", "Qty", "");
        for (Item i : items.values()) {
            output += i.totalizedString() + "\n";
        }
        return output;
    }
}
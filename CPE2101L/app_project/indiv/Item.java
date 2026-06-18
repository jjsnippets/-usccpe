// Information for a single item class
// Stock.java keeps track of all items stocked

package indiv;

public class Item implements Cloneable, Comparable<Item> {
    private String name;
    private String category;
    private double price;
    private int quantity;   // for Transaction: amount sold to customer
                            // for Stock: total amount available to be sold

    // standard constructor
    public Item(String name, String category, double price, int quantity) {
        this.setName(name);
        this.setCategory(category);
        this.setPrice(price);
        this.setQuantity(quantity);
    }

    // accessors and mutators
    public String getName() { return this.name; }
    public void setName(String name) { this.name = name.strip(); }

    public String getCategory() { return this.category; }
    public void setCategory(String category) { this.category = category.strip(); }

    public double getPrice() { return price; }
    public void setPrice(double price) { this.price = Math.max(0, price); }

    public int getQuantity() { return quantity; }
    public void setQuantity(int quantity) { this.quantity = Math.max(0, quantity); }
    public void incQuantity(int quantity) { this.quantity = Math.max(0, this.quantity + quantity); }
    public void decQuantity(int quantity) { this.quantity = Math.max(0, this.quantity - quantity); }

    // clone method used in Transaction.java
    @Override
    public Item clone() {
        return new Item(this.name, this.category, this.price, this.quantity);
    }
    
    // comparison based on name (alphabetical order sorting)
    public int compareTo(Item other) {
        return this.name.compareTo(other.name);
    }

    public String toString() {
        return String.format(" %-20s %-15s %10.2f %5d", this.getName(), this.getCategory(), this.getPrice(), this.getQuantity());
    }

    public String totalizedString() {
        return this.toString() + String.format(" %10.2f", this.getPrice() * this.getQuantity());
    }
}
// Customer information class
// the system will only keep track of customers with credit != 0
// Contacts.java keeps track of all customers 

package indiv;

public class Customer implements Comparable<Customer> {
    private String name;
    private String contactNo;
    private double credit;      // negative means debt, positive means advance
    private int date;           // date of last payment
    
    // constructor: supply name only
    public Customer(String name) {
        this.setName(name);
        this.setContactNo("");
        this.setCredit(0);
        this.setDate(0);
    }

    // constructor used in file reading
    public Customer(String name, String contactNo, double credit, int date) {
        this.setName(name);
        this.setContactNo(contactNo);
        this.setCredit(credit);
        this.setDate(date);
    }

    // accessors and mutators
    public String getName() { return name; }
    public void setName(String name) { this.name = name.strip(); }

    public String getContactNo() { return contactNo; }
    public void setContactNo(String contactNo) { this.contactNo = contactNo.strip(); }
    
    public double getCredit() { return credit; }
    public void setCredit(double credit) { this.credit = credit; }
    
    public int getDate() { return date; } 
    public void setDate(int date) { this.date = Math.max(0, date); }

    // comparison based on credit (most debt to least debt)
    public int compareTo(Customer other) {
        return Double.compare(this.credit, other.credit);
    }

    public String toString() {
        return String.format(" %-10s %-15s %10.2f %7d", this.getName(), this.getContactNo(), this.getCredit(), this.getDate());
    }
}

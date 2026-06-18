// Class which stores all Customers

package group;

import java.io.*;
import java.util.*;

import indiv.Customer;

public class Contacts extends NamedMap<Customer> {
    private static double maxDebt = -200; // maximum debt allowed

    public static double getMaxDebt() { return Contacts.maxDebt; }
    public static void setMaxDebt(double newDebt) { Contacts.maxDebt = Math.min(newDebt, -1 * newDebt); }

    // prints the list of all customers
    public String toString() {
        String res = String.format(" %-10s %-15s %10s %7s\n", "Name", "Contact No.", "Credit", "Date");

        ArrayList<Customer> sortedCustomers = new ArrayList<>(this.values());
        Collections.sort(sortedCustomers);

        for (Customer customer : sortedCustomers) {
            res += customer + "\n";
        }

        return res + "\n";
    }

    public String search(String name) {
        Contacts filteredContacts = new Contacts();
        for (String key : this.keySet()) {
            if (key.toUpperCase().replace(" ", "").contains(name.toUpperCase().replace(" ", ""))) {
                filteredContacts.put(key, this.get(key));
            }
        }

        return (name.equals("") ? "" : "Search results for " + name + "\n" + filteredContacts.size() + " results\n\n") + filteredContacts.toString();
    }
    
    // file read and write operations
    public void fromFile() {
             try (BufferedReader br = new BufferedReader(new FileReader("data/customer.csv"))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length == 4) {
                    String name = parts[0].strip();
                    String contactNo = parts[1].strip();
                    double credit = Double.parseDouble(parts[2].strip());
                    int date = Integer.parseInt(parts[3].strip());
                    
                    // Only add customers with credit != 0
                    if (credit != 0) {
                        this.put(name, new Customer(name, contactNo, credit, date));
                    }
                }
            }
            System.out.println("Customers loaded from file!");
        } catch (IOException e) {
            System.err.println("Error reading from file: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.err.println("Error parsing number: " + e.getMessage());
        }
    }

    public void toFile() {
            try (BufferedWriter bw = new BufferedWriter(new FileWriter("data/customer.csv"))) {
            for (Map.Entry<String, Customer> entry : this.entrySet()) {
                Customer customer = entry.getValue();
                // Write only customers with credit != 0
                if (customer.getCredit() != 0) {
                    bw.write(customer.getName() + "," + customer.getContactNo() + "," + customer.getCredit() + "," + customer.getDate());
                    bw.newLine();
                }
            }
            System.out.println("Items loaded from file");
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}

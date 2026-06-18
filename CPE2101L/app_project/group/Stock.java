// Class which stores all items

package group;

import java.io.*;
import java.util.*;
import java.util.stream.*;

import indiv.Item;

public class Stock extends NamedMap<Item> {
    private static final int LOW_INVENTORY_THRESHOLD = 5;

    // adding a single item in the stock
    public void addItem(String name, Item item) {
        name = name.trim().toLowerCase();
        // if the item does not exist, then add the item to the stock
        if (!this.containsKey(name)) { 
            this.put(name, item);

        // if the item already exists, then increment only the amount specified
        } else { 
            this.get(name).incQuantity(item.getQuantity());
        }
    }

    // removing an item in the stock
    public void removeItem(String name) {
        String normalizedName = name.trim().toLowerCase();
        System.out.println("Trying to remove item: " + normalizedName); // Added for debugging
    
        if (this.containsKey(normalizedName)) {
            this.remove(normalizedName);
            System.out.println("Item removed: " + normalizedName);
        }
        else{
            System.out.println("Item not found: " + normalizedName);
        }
    }

    public String toString() {
        String inventory = String.format("  %-20s %-15s %10s %5s %10s", "Name", "Category", "Price", "Qty", "");
    
        // Group items by category
        Map<String, List<Item>> itemsByCategory = this.values().stream()
                .collect(Collectors.groupingBy(Item::getCategory));
    
        // Sort categories alphabetically
        List<String> sortedCategories = new ArrayList<>(itemsByCategory.keySet());
        Collections.sort(sortedCategories);
    
        // Print items by category, each sorted alphabetically within the category
        for (String category : sortedCategories) {
            inventory += "\n " + category.toUpperCase() + "\n";
    
            List<Item> itemsInCategory = itemsByCategory.get(category);
            itemsInCategory.sort((item1, item2) -> item1.getName().compareToIgnoreCase(item2.getName()));
    
            for (Item item : itemsInCategory) {
                inventory += " " + item.toString() + "\n"; // Adjust to control item format if needed
            }
        }
        inventory += "\n";

        return inventory;
    }
    
    public String search(String search) {
        Stock filteredStock = new Stock();
        for (String key : this.keySet()) {
            Item item = this.get(key);
            if (item.getName().toUpperCase().replace(" ", "").contains(search.toUpperCase().replace(" ", ""))) {
                filteredStock.addItem(key, item);
            }
        }
    
        return " " + (search.equals("") ? filteredStock.size() + " SKUs\n\n"
                : "Search results for " + search + "\n " + filteredStock.size() + " SKUs\n\n") + 
                filteredStock.toString();
    }

    public String lowInventoryNotifier(){
        String res = "";	
        for (String key : this.keySet()) {
            Item item = this.get(key);
            if (item.getQuantity() < LOW_INVENTORY_THRESHOLD) {
                res += "   Stock of " + item.getName() + " is low (" + item.getQuantity() + " remaining)!\n";
            }
        }
        return res;
    }

    // file read and write operations
    public void fromFile() {
        try(BufferedReader br = new BufferedReader(new FileReader("data/items.csv"))){
            String line;
            while((line = br.readLine()) != null){
                String[]parts = line.split(",");
                    if (parts.length == 4){
                        String itemName = parts[0].trim();
                        String itemCategory = parts[1].trim();
                        double itemPrice = Double.parseDouble(parts[2].trim());
                        int itemQuantity = Integer.parseInt(parts[3].trim());

                        Item item = new Item (itemName, itemCategory, itemPrice, itemQuantity);
                        addItem(itemName, item);
                    }
                }
                System.out.println("Items loaded from file");

            } catch (IOException e){
                System.err.println("Error reading from file: " + e.getMessage());
            } catch (NumberFormatException e) {
                System.err.println("Error parsing number: " + e.getMessage());
        }
    }

    public void toFile() {
        try(BufferedWriter bw = new BufferedWriter(new FileWriter("data/items.csv"))){
            for (String key : this.keySet()) {
                Item item = this.get(key);
                String line = String.format("%s,%s,%.2f,%d", item.getName(),item.getCategory(),item.getPrice(), item.getQuantity() );
                bw.write(line);
                bw.newLine();
                }
                System.out.println("Items saved to file");
            } catch (IOException e) {
                System.err.println("Error writing to file: " + e.getMessage());  
        }
    }
}

// Submenu for adding items to the inventory (stock)

package gui.InventoryGUI;

import javax.swing.*;

import group.Stock;
import gui.JInventory;
import indiv.Item;

public class JInventoryAdd extends JItemSelector {
    public JInventoryAdd(JInventory parentFrame, Stock stock) {
        super(parentFrame, "Add Item", stock, true, true, true);
    }

    // When user confirms of the item
    protected void confirm() {
        // Get item details from user
        String itemName = getItemName();
        String itemCategory = getItemCategory();
        int itemQuantity = getItemQuantity();
        double itemPrice = getItemPrice();

        Item newItem;

        // If any field is empty or invalid
        if (itemName.equals("") || itemCategory.equals("") || itemQuantity == 0 || itemPrice == 0.0) {
            JOptionPane.showMessageDialog(this, "Enter all fields properly first!");
            return;
        }

        // if item already exists, add quantity
        if (stock.containsKey(itemName)) {
            Item item = stock.get(itemName);
            newItem = new Item(itemName, item.getCategory(), item.getPrice(), itemQuantity + item.getQuantity());
            stock.put(itemName, newItem);
            this.updateText();
            JOptionPane.showMessageDialog(this, "Item restocked successfully");
        
        // otherwise, create new item
        } else {
            newItem = new Item(itemName, itemCategory, itemPrice, itemQuantity);
            stock.put(itemName, newItem);
            this.updateText();
            JOptionPane.showMessageDialog(this, "Item added successfully");
        }
    }
}

// Submenu for changing the price of an item in the inventory (stock)

package gui.InventoryGUI;

import javax.swing.*;

import group.Stock;
import gui.JInventory;

public class JInventoryChange extends JItemSelector {
    public JInventoryChange(JInventory parentFrame, Stock stock) {
        super(parentFrame, "Change price of item", stock, false, false, true);
    }

    // When user confirms of adding the item
    public void confirm() {
        // Get item details from user
        String itemName = getItemName();
        double itemPrice = getItemPrice();

        // If any field is empty or invalid
        if (itemName.equals("") || itemPrice == 0.0) {
            JOptionPane.showMessageDialog(this, "Enter all fields properly first!");
            return;
        }

        // if item exists, then change price
        if (stock.containsKey(itemName)) {
            stock.get(itemName).setPrice(itemPrice);
        
            this.updateText();
            JOptionPane.showMessageDialog(this, "Price changed: " + itemName + " to " + itemPrice + " successfully!");

        // otherwise notify that item does not exist
        } else {
            JOptionPane.showMessageDialog(this, itemName +  " not found!");
        }
    }
}

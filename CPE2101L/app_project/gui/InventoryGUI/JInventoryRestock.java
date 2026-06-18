// Submenu for restocking items in the inventory (stock)

package gui.InventoryGUI;

import group.Stock;
import gui.JInventory;
import javax.swing.JOptionPane;

public class JInventoryRestock extends JItemSelector {
    public JInventoryRestock(JInventory parentFrame, Stock stock) {
        super(parentFrame, "Restock Item", stock, false, true, false);
    }

    // When user confirms of restocking the item
    public void confirm() {
        String itemName = getItemName();
        int itemQuantity = getItemQuantity();

        // If any field is empty or invalid
        if (itemName.equals("") || itemQuantity == 0) {
            JOptionPane.showMessageDialog(this, "Enter an item name first!");
            return;
        }

        // if item exists, add to quantity
        if (stock.containsKey(itemName)) {
            stock.get(itemName).incQuantity(itemQuantity);

            this.updateText();
            JOptionPane.showMessageDialog(this, "Increased amount of " + itemName + " by " + itemQuantity + " successfully!");

        // otherwise notify that item does not exist
        } else {
            JOptionPane.showMessageDialog(this, itemName +  " not found!");
        }
    }
}

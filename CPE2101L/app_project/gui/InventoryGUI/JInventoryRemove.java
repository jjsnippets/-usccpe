// Submenu for removing items from the inventory (stock)

package gui.InventoryGUI;

import javax.swing.JOptionPane;

import group.Stock;
import gui.JInventory;

public class JInventoryRemove extends JItemSelector {
    public JInventoryRemove(JInventory parentFrame, Stock stock) {
        super(parentFrame, "Remove Item", stock, false, false, false);
    }

    // When user confirms of removing the item
    public void confirm() {
        String itemName = getItemName();

        if (itemName.equals("")) {
            JOptionPane.showMessageDialog(this, "Enter an item name first!");
            return;
        }

        // if item already exists, remove from stock
        if (stock.containsKey(itemName)) {
            stock.remove(itemName);
            
            this.updateText();
            JOptionPane.showMessageDialog(this, itemName + " removed successfully!");

        // otherwise notify that item does not exist
        } else {
            JOptionPane.showMessageDialog(this, itemName +  " not found!");
        }
    }
}

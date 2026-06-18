// Submenu for ading items to cart

package gui.PoSGUI;

import javax.swing.*;

import group.NamedMap;
import group.Stock;
import gui.JCustomFrame;
import indiv.*;

public class JPoSAdd extends JCartSelector {
    public JPoSAdd(JCustomFrame parentFrame, Stock stock, Transaction cart) {
        super(parentFrame, stock, cart, JCartSelector.DISPLAY_STOCK);
    }

    // When user confirms of the item
    protected void confirm(){
        String itemName = getItemName();
        int itemQuantity = getItemQuantity();

        NamedMap<Item> cartItems = cart.getItems();
        Item stockedItem;
        Item newItem;

        // Failure cases
            // if any field is empty
            if (itemName.equals("") || itemQuantity == 0) {
                JOptionPane.showMessageDialog(this, "Enter all fields properly first!");
                return;
            }

            // if item does not exist
            if (!stock.containsKey(itemName)) {
                JOptionPane.showMessageDialog(this, "Item does not exist in stock!");
                return;
            }

            stockedItem = stock.get(itemName);

            // if no stock left
            if (stockedItem.getQuantity() == 0) {
                JOptionPane.showMessageDialog(this, "No stock left for " + itemName + "!");
                return;
            }

            // if requested quantity is more than stock
            if (itemQuantity > stockedItem.getQuantity()) {
                JOptionPane.showMessageDialog(this, "Not enough stock for " + itemName + "!");
                return;
            }

            // if requested quantity is negative
            if (itemQuantity < 0) {
                JOptionPane.showMessageDialog(this, "Invalid quantity!");
                return;
            }

        stockedItem.decQuantity(itemQuantity);                  // decrement item quantity in stock
        cart.incWorth(itemQuantity * stockedItem.getPrice());   // increment transaction worth

        // if item already exists in cart
        if (cartItems.containsKey(itemName)) {
            cartItems.get(itemName).incQuantity(itemQuantity);
            this.updateText();
            JOptionPane.showMessageDialog(this, "Successfully added " + itemQuantity + " more " + itemName + " to cart.");

        // if item does not exist in cart
        } else {
            newItem = stockedItem.clone();
            newItem.setQuantity(itemQuantity);
            cartItems.put(itemName, newItem);
            this.updateText();
            JOptionPane.showMessageDialog(this, "Successfully added " + itemQuantity + " " + itemName + " to cart.");
        }
    }
}

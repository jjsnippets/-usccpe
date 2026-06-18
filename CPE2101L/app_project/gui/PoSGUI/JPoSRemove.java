// Submenu for removing items from cart

package gui.PoSGUI;

import javax.swing.*;

import group.Stock;
import gui.JPoS;
import indiv.*;

public class JPoSRemove extends JCartSelector {
    public JPoSRemove(JPoS parentFrame, Stock stock, Transaction cart) {
        super(parentFrame, stock, cart, JCartSelector.DISPLAY_CART);
    }

    // When user confirms of the item
    @Override
    protected void confirm(){
        String itemName = getItemName();
        int itemQuantity = getItemQuantity();

        Stock cartItems = cart.getItems();
        Item cartItem;

        // Failure cases
            // if any field is empty
            if (itemName.equals("") || itemQuantity == 0) {
                JOptionPane.showMessageDialog(this, "Enter all fields properly first!");
                return;
            }

            // if item is not in cart
            if (!cartItems.containsKey(itemName)) {
                JOptionPane.showMessageDialog(this, "Item not in cart!");
                return;
            }
        
        // otherwise, remove item from cart
        cartItem = cartItems.get(itemName);

        // value clamping
        if (cartItem.getQuantity() < itemQuantity) {
            itemQuantity = cartItem.getQuantity();
        }

        // reduce relevant values
        cartItem.setQuantity(cartItem.getQuantity() - itemQuantity);
        cart.decWorth(itemQuantity * cartItem.getPrice());

        // if quantity is 0, remove item from cart
        if (cartItem.getQuantity() == 0) {
            cartItems.remove(itemName);
        }

        // add removed quantites back to stock
        if (stock.containsKey(itemName)) {
            Item stockItem = stock.get(itemName);
            stockItem.setQuantity(stockItem.getQuantity() + itemQuantity);
        } else {
            stock.put(itemName, new Item(itemName, cartItem.getCategory(), cartItem.getPrice(), itemQuantity));
        }

        this.updateText();
        JOptionPane.showMessageDialog(this, "Item removed from cart successfully");
    }
}

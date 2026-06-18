// Main submenu for Point of Sale transactions

// Functionally cribbed from the TUI interface:
// [1] Add to cart
// [?] Remove item from cart
// [D] Show current cart
// [3] Finalize transaction
// [4] Cancel transaction

package gui;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import group.*;
import gui.PoSGUI.*;
import indiv.*;


public class JPoS extends JCustomFrame implements ActionListener {
    // Buttons
    private JButton addCart = new JButton("Add to cart");
    private JButton remCart = new JButton("Remove item from cart");
    private JButton finalize = new JButton("Finalize transaction");
    private JButton cancel = new JButton("Cancel transaction");

    // Text areas and fields
    private JTextArea cartList = new JTextArea();
    private JLabel priceTicker = new JLabel();

    // Saving constructor arguments to class
    private Contacts contacts;
    private History history;
    private Stock stock;

    // Constructor for the PoS window
    public JPoS(JCustomFrame parentFrame, Contacts contacts, History history, Stock stock){
        super("Transaction");
        this.parentFrame = parentFrame;
        this.contacts = contacts;
        this.history = history;
        this.stock = stock;
        
        this.cart = new Transaction(history.size());
        Container con = getContentPane();

        // Add buttons to the left of the window
        JPanel buttons = new JPanel();
            buttons.setLayout(new GridLayout(4, 1));
                buttons.add(addCart);
                buttons.add(remCart);
                buttons.add(finalize);
                buttons.add(cancel);
        con.add(buttons, BorderLayout.WEST);

        // Add cart details to the center of the window
        JPanel cartWindow = new JPanel(new BorderLayout());
            // Header for the cart list
            JLabel header = new JLabel("Current Cart: ");
            // Scrollable cart list
            JPanel cartPane = new JPanel();
            JScrollPane scroll = new JScrollPane(cartPane, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
                cartList.setEditable(false);
                cartList.setColumns(50);
                cartList.setText("Empty Default\n".repeat(50));
                cartPane.add(cartList);
            // Total price at the bottom
            JPanel subtotalPane = new JPanel(new FlowLayout(FlowLayout.LEFT));
                JLabel subtotalText = new JLabel("Subtotal: ");
                subtotalPane.add(subtotalText);
                subtotalPane.add(priceTicker);
            cartWindow.add(header, BorderLayout.NORTH);
            cartWindow.add(scroll, BorderLayout.CENTER);
            cartWindow.add(subtotalPane, BorderLayout.SOUTH);
        con.add(cartWindow, BorderLayout.CENTER);

        // Add action listeners
        addCart.addActionListener(this);
        remCart.addActionListener(this);
        finalize.addActionListener(this);
        cancel.addActionListener(this);

        // Decorating the frame
        header.setFont(Theme.HEADER2_FONT);
        subtotalText.setFont(Theme.HEADER3_FONT);
        priceTicker.setFont(Theme.HEADER3_FONT);
        cartList.setFont(Theme.MONO_FONT);
        cartList.setOpaque(false);

        updateText();
    }

    // Actions in order
    @Override
    public void actionPerformed(ActionEvent e){
        // Add item to cart
        if(e.getSource() == addCart){
            JPoSAdd submenu = new JPoSAdd(this, stock, cart);
            submenu.updateText();
            submenu.setVisible(true);
            this.setVisible(false);

        // Remove item from cart
        } else if(e.getSource() == remCart){
            JPoSRemove submenu = new JPoSRemove(this, stock, cart);
            submenu.updateText();
            submenu.setVisible(true);
            this.setVisible(false);

        // Finalize transaction
        } else if(e.getSource() == finalize){
            
            JPoSFinalize submenu = new JPoSFinalize(this, history, contacts, cart);
            submenu.updateText();
            submenu.setVisible(true);
            this.setVisible(false);
        
        // Cancel transaction and return to main menu
        } else if(e.getSource() == cancel){
            int choice = JOptionPane.showConfirmDialog(this, "Are you sure you want to cancel this transaction?", "Cancel Transaction", JOptionPane.YES_NO_OPTION);

            if (choice == JOptionPane.YES_OPTION) {
                for (Item item : cart.getItems().values()) {
                    stock.get(item.getName()).incQuantity(item.getQuantity());
                }

                returnToMenu();
                JOptionPane.showMessageDialog(this, "Transaction cancelled!");
            }
        }
    }

    public void returnToMenu(){
        this.dispose();
        parentFrame.updateText();
        parentFrame.setVisible(true);
    }

    public void updateText(){
        cartList.setText(cart.toString());
        priceTicker.setText("P" + cart.getWorth());
    }
}

// Template frame for item addition/removal to cart

package gui.PoSGUI;

import group.Stock;
import gui.*;
import indiv.Transaction;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class JCartSelector extends JCustomFrame implements ActionListener, DocumentListener {
    // Constants
    public static final int DISPLAY_STOCK = 1;
    public static final int DISPLAY_CART = 2;
    private int displayMode;
    
    // Buttons
    private JButton confirmButton = new JButton("Confirm");
    private JButton cancelButton = new JButton("Return");

    // Text areas and fields
    private JTextArea itemList = new JTextArea();         // Either stock or cart
    private JTextField itemName = new JTextField(20);
    private JTextField itemQuantity = new JTextField(20);

    // Frame constructor
    public JCartSelector(JCustomFrame parentFrame, Stock stock, Transaction cart, int displayMode){
        super("Point of Sale");
        this.parentFrame = parentFrame;
        this.stock = stock;
        this.cart = cart;
        this.displayMode = displayMode;
        Container con = getContentPane();

        // Item list at the center of the window (Either stock or cart)
        JPanel centerPanel = new JPanel(new BorderLayout());
            // Description of the scrollable list
            JLabel header = new JLabel(displayMode == DISPLAY_STOCK ? "Current Stock" : "Current cart contents");
            // Scrollable list
            JPanel itemWindow = new JPanel();
            JScrollPane scroll = new JScrollPane(itemWindow, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
                itemList.setEditable(false);
                itemList.setColumns(50);
                itemList.setText("Empty Default\n".repeat(50));
                itemWindow.add(itemList);
            centerPanel.add(header, BorderLayout.NORTH);
            centerPanel.add(scroll, BorderLayout.CENTER);
        con.add(centerPanel, BorderLayout.CENTER);

        // Item selection at the bottom of the window
        JPanel itemSelection = new JPanel(new BorderLayout());
            // Description at the top of the frame
            JLabel descriptionBox = new JLabel(displayMode == DISPLAY_STOCK ? "Add item to cart" : "Remove item from cart");
            // Fields at the bottom of the frame
            JPanel fields = new JPanel(new GridLayout(2, 1));
                // Item name field
                JPanel nameFields = new JPanel(new FlowLayout(FlowLayout.LEFT));
                    JLabel itemLabel = new JLabel("Item Name:");
                    nameFields.add(itemLabel);
                    nameFields.add(itemName);
                fields.add(nameFields);
                // Item quantity field
                JPanel quantityFields = new JPanel(new FlowLayout(FlowLayout.LEFT));
                    JLabel quantityLabel = new JLabel("Quantity:");
                    quantityFields.add(quantityLabel);
                    quantityFields.add(itemQuantity);
                fields.add(quantityFields);
            // buttons at the right of the frame
            JPanel buttons = new JPanel(new FlowLayout());
                buttons.add(confirmButton);
                buttons.add(cancelButton);
            itemSelection.add(descriptionBox, BorderLayout.NORTH);
            itemSelection.add(fields, BorderLayout.CENTER);
            itemSelection.add(buttons, BorderLayout.EAST);
        con.add(itemSelection, BorderLayout.SOUTH);

        // Add action listeners
        itemName.addActionListener(this);
        itemQuantity.addActionListener(this);
        confirmButton.addActionListener(this);
        cancelButton.addActionListener(this);
        itemName.getDocument().addDocumentListener(this);

        // Decorating the frame
        itemList.setFont(Theme.MONO_FONT);
        itemList.setOpaque(false);

        updateText();
    }

    // Accessors
    public String getItemName() {
        try {
            return itemName.getText().strip();
        } catch (Exception e) {
            e.printStackTrace();
            return "";
        }
    }
    public int getItemQuantity() {
        try {
            return Integer.parseInt(itemQuantity.getText());
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

	// Button actions and field completions
    @Override
    public void actionPerformed(ActionEvent e) {
        // When user confirms of the item
        // By pressing enter on any field
        if (e.getSource() == itemName) { confirm();
        } else if (e.getSource() == itemQuantity) { confirm();

        // By pressing the confirm button
        } else if (e.getSource() == confirmButton) { confirm();

        // Return to Transaction submenu
        } else if (e.getSource() == cancelButton) {
            this.dispose();
            parentFrame.updateText();
            parentFrame.setVisible(true); // Make the parent frame visible again
        }
    }

    // Field edits
    @Override public void insertUpdate(DocumentEvent e) { updateText(); }
    @Override public void changedUpdate(DocumentEvent e) { updateText(); }
    @Override public void removeUpdate(DocumentEvent e) { updateText(); }

    // Should be overriden
    protected void confirm(){
        throw(new UnsupportedOperationException("Method not implemented"));
    }

    // For updating all text areas
    public void updateText(){
        if (displayMode == DISPLAY_STOCK){
            String search = getItemName();
            itemList.setText(stock.search(search));
        } else if (displayMode == DISPLAY_CART){
            itemList.setText(cart.toString());
        }
    }
}

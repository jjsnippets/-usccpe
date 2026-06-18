// Template frame for all JInventory submenus

package gui.InventoryGUI;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

import group.Stock;
import gui.*;

public class JItemSelector extends JCustomFrame implements ActionListener, DocumentListener {
    // Buttons
    private JButton confirmButton = new JButton("Confirm");
    private JButton cancelButton = new JButton("Return");

    // Text areas and fields
    private JTextArea inventoryList = new JTextArea();
    private JTextField itemName = new JTextField(20);
    private JTextField itemCategory = new JTextField(20);
    private JTextField itemQuantity = new JTextField(20);
    private JTextField itemPrice = new JTextField(20);

    public JItemSelector(JCustomFrame parentFrame, String description, Stock stock, boolean enableCategory, boolean enableQuantity, boolean enablePrice) {
        super("Inventory List");
        Container con = getContentPane();
        this.parentFrame = parentFrame;
        this.stock = stock;

        // Inventory list at the center of the window
        JPanel inventoryWindow = new JPanel(new BorderLayout());
            JLabel header = new JLabel("Current Inventory");

            JPanel itemWindow = new JPanel();
                JScrollPane scroll = new JScrollPane(itemWindow, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
                inventoryList.setEditable(false);
                inventoryList.setColumns(50);
                inventoryList.setText("Empty Default\n".repeat(50));
                

                itemWindow.add(inventoryList);

            inventoryWindow.add(header, BorderLayout.NORTH);
            inventoryWindow.add(scroll, BorderLayout.CENTER);
            
        con.add(inventoryWindow, BorderLayout.CENTER);

        // Item selection at the bottom of the window
        JPanel itemSelection = new JPanel(new BorderLayout());

            // Description at the top of the frame
            JLabel descriptionBox = new JLabel(description);
            descriptionBox.setFont(new Font("Arial", Font.PLAIN, 20));

            // Fields at the bottome of the frame
            JPanel fields = new JPanel(new GridLayout(1+ (enableCategory ? 1 : 0) + (enableQuantity ? 1 : 0) + (enablePrice ? 1 : 0), 1));
                // Always able to input item name
                JPanel nameFields = new JPanel(new FlowLayout(FlowLayout.LEFT));
                        JLabel itemLabel = new JLabel("Item Name:");
                        nameFields.add(itemLabel);
                        nameFields.add(itemName);
                    fields.add(nameFields);

                if (enableCategory) {
                    JPanel categoryFields = new JPanel(new FlowLayout(FlowLayout.LEFT));
                        JLabel categoryLabel = new JLabel("Category:");
                            categoryLabel.setFont(Theme.HEADER4_FONT);
                        categoryFields.add(categoryLabel);
                        categoryFields.add(itemCategory);
                    fields.add(categoryFields);
                }
                
                if (enableQuantity) {
                    JPanel quantityFields = new JPanel(new FlowLayout(FlowLayout.LEFT));
                        JLabel quantityLabel = new JLabel("Quantity:");
                            quantityLabel.setFont(Theme.HEADER4_FONT);
                        quantityFields.add(quantityLabel);
                        quantityFields.add(itemQuantity);
                    fields.add(quantityFields);
                }

                if (enablePrice) {
                    JPanel priceFields = new JPanel(new FlowLayout(FlowLayout.LEFT));
                        JLabel priceLabel = new JLabel("Price:");
                            priceLabel.setFont(Theme.HEADER4_FONT);
                        priceFields.add(priceLabel);
                        priceFields.add(itemPrice);
                    fields.add(priceFields);
                }
            
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
        itemCategory.addActionListener(this);
        itemQuantity.addActionListener(this);
        itemPrice.addActionListener(this);
        confirmButton.addActionListener(this);
        cancelButton.addActionListener(this);
        itemName.getDocument().addDocumentListener(this);

        // Decorating the frame
        header.setFont(Theme.HEADER2_FONT);
        descriptionBox.setFont(Theme.HEADER3_FONT);
        itemLabel.setFont(Theme.HEADER4_FONT);
        inventoryList.setFont(Theme.MONO_FONT);
        inventoryList.setOpaque(false);

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
    public String getItemCategory() {
        try {
            return itemCategory.getText().strip();
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
    public double getItemPrice() {
        try {
            return Double.parseDouble(itemPrice.getText());
        } catch (Exception e) {
            e.printStackTrace();
            return 0.0;
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // When user confirms of the item
        // By pressing enter on any field
        if (e.getSource() == itemName) { confirm();
        } else if (e.getSource() == itemCategory) { confirm();
        } else if (e.getSource() == itemQuantity) { confirm();
        } else if (e.getSource() == itemPrice) { confirm();
        
        // By pressing the confirm button
        } else if (e.getSource() == confirmButton) { confirm();

        // Return to Inventory submenu
        } else if (e.getSource() == cancelButton) {
            this.dispose();
            parentFrame.updateText();
            parentFrame.setVisible(true);
        }
    }

    @Override public void insertUpdate(DocumentEvent e) { updateText(); }
    @Override public void changedUpdate(DocumentEvent e) { updateText(); }
    @Override public void removeUpdate(DocumentEvent e) { updateText(); }

    // Should be overriden
    protected void confirm(){
        throw(new UnsupportedOperationException("Method not implemented"));
    }

    // For updating all text areas
    public void updateText(){
        String search = getItemName();
        inventoryList.setText(stock.search(search));
    }
}
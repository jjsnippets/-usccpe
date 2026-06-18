// Main submenu for inventory management

// Functionally cribbed from the TUI interface:
// [1] Add item             // Will also add quantity if already present
// [2] Remove item
// [3] Change price
// [4] Stock an item
// [D] Show all inventory   // Always present at the side of the screen
// [5] Exit

package gui;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

import group.Stock;
import gui.InventoryGUI.*;

public class JInventory extends JCustomFrame implements ActionListener, DocumentListener {
    // Buttons
    private JButton addItem = new JButton("Add Item");
    private JButton remItem = new JButton("Remove Item");
    private JButton changePrice = new JButton("Change Price");
    private JButton restock = new JButton("Restock Item");
    private JButton exit = new JButton("Return to Main Menu");

    // Text areas and fields
    private JTextArea inventoryList = new JTextArea();
    private JTextField searchItem = new JTextField(20);

    // Constructor for the inventory management window
    public JInventory(JCustomFrame parentFrame, Stock stock){
        super("Inventory Manager");
        this.parentFrame = parentFrame;
        this.stock = stock;
        Container con = getContentPane();

        // Add buttons to the left of the window
        JPanel buttons = new JPanel();
            buttons.setLayout(new GridLayout(5, 1));
                buttons.add(addItem);
                buttons.add(remItem);
                buttons.add(changePrice);
                buttons.add(restock);
                buttons.add(exit);
        con.add(buttons, BorderLayout.WEST);

        // Inventory list at the center of the window
        JPanel inventoryWindow = new JPanel(new BorderLayout());
            // Header for the inventory list
            JLabel header = new JLabel("Current Inventory");
            // Scrollable inventory list
            JPanel itemWindow = new JPanel();
            JScrollPane scroll = new JScrollPane(itemWindow, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
                inventoryList.setEditable(false);
                inventoryList.setColumns(50);
                inventoryList.setText("Empty Default\n".repeat(50));
                itemWindow.add(inventoryList);
            // Field for searching items at the bottom of the frame
            JPanel searchField = new JPanel(new FlowLayout(FlowLayout.LEFT));
                JLabel searchLabel = new JLabel("Search Item:");
                searchField.add(searchLabel);
                searchField.add(searchItem);
            inventoryWindow.add(header, BorderLayout.NORTH);
            inventoryWindow.add(scroll, BorderLayout.CENTER);
            inventoryWindow.add(searchField, BorderLayout.SOUTH);
        con.add(inventoryWindow, BorderLayout.CENTER);

        // Add action listeners
        addItem.addActionListener(this);
        remItem.addActionListener(this);
        changePrice.addActionListener(this);
        restock.addActionListener(this);
        exit.addActionListener(this);
        searchItem.getDocument().addDocumentListener(this);

        // Decorating the frame
        header.setFont(Theme.HEADER2_FONT);
        inventoryList.setFont(Theme.MONO_FONT);
        inventoryList.setOpaque(false);

        updateText();
    }

    // Button actions in order
    @Override
    public void actionPerformed(ActionEvent e) {
        // Add item
        if (e.getSource() == addItem) {
            JInventoryAdd submenu = new JInventoryAdd(this, stock);
            submenu.updateText();
            submenu.setVisible(true);
            this.setVisible(false);

        // Remove item
        } else if (e.getSource() == remItem) {
            JInventoryRemove submenu = new JInventoryRemove(this, stock);
            submenu.updateText();
            submenu.setVisible(true);
            this.setVisible(false);

        // Change price
        } else if (e.getSource() == changePrice) {
            JInventoryChange submenu = new JInventoryChange(this, stock);
            submenu.updateText();
            submenu.setVisible(true);
            this.setVisible(false);

        // Restock item
        } else if (e.getSource() == restock) {
            JInventoryRestock submenu = new JInventoryRestock(this, stock);
            submenu.updateText();
            submenu.setVisible(true);
            this.setVisible(false);
        
        // Return to main menu
        } else if (e.getSource() == exit) {
            this.dispose();
            parentFrame.updateText();
            parentFrame.setVisible(true);
        }
    }

    // Update the inventory list at all times (any time the search field is changed in some way)
    @Override public void insertUpdate(DocumentEvent e) { updateText(); }
    @Override public void changedUpdate(DocumentEvent e) { updateText(); }
    @Override public void removeUpdate(DocumentEvent e) { updateText(); }

    // For updating all text areas
    public void updateText(){
        String search = searchItem.getText();
        inventoryList.setText(stock.search(search));
    }
}

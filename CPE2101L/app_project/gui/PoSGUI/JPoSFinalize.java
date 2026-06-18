// Submenu for finalizing the transaction

package gui.PoSGUI;

import group.*;
import gui.*;
import indiv.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class JPoSFinalize extends JCustomFrame implements ActionListener, DocumentListener {
    // Buttons
    private JButton confirmButton = new JButton("Checkout");
    private JButton cancelButton = new JButton("Return");

    // Text areas and fields
    private JTextArea cartList = new JTextArea();
    private JTextArea customerList = new JTextArea();
    private JTextField customerName = new JTextField(20);
    private JTextField payment = new JTextField(20);
    private JLabel cartWorth = new JLabel();

    // Frame constructor
    public JPoSFinalize(JCustomFrame parentFrame, History history, Contacts contacts, Transaction cart) {
        super("Finalize Transaction");
        Container con = getContentPane();

        this.parentFrame = parentFrame;
        this.history = history;
        this.contacts = contacts;
        this.cart = cart;

        // Dashboard at the center of the window
        JPanel dashboard = new JPanel(new GridLayout(2, 1));
            // Cart details on the upper half
            JPanel cartDetails = new JPanel(new BorderLayout());
                JLabel cartHeader = new JLabel("Contents of Cart");
                JPanel cartPane = new JPanel();
                JScrollPane scroll = new JScrollPane(cartPane, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
                    cartList.setEditable(false);
                    cartList.setColumns(50);
                    cartList.setText("Empty Default\n".repeat(50));
                    cartPane.add(cartList);
                JPanel worthLabels = new JPanel(new FlowLayout(FlowLayout.RIGHT));
                    JLabel cartWorthLabel = new JLabel("Subtotal: P");
                    worthLabels.add(cartWorthLabel);
                    worthLabels.add(cartWorth);
                cartDetails.add(cartHeader, BorderLayout.NORTH);
                cartDetails.add(scroll, BorderLayout.CENTER);
                cartDetails.add(worthLabels, BorderLayout.SOUTH);
            
            // customer list on the lower half
            JPanel customerDetails = new JPanel(new BorderLayout());
                JLabel customerHeader = new JLabel("Customer List");
                JPanel customerPane = new JPanel();
                JScrollPane scroll2 = new JScrollPane(customerPane, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
                    customerList.setEditable(false);
                    customerList.setColumns(50);
                    customerList.setText("Empty Default\n".repeat(50));
                    customerPane.add(customerList);
                customerDetails.add(customerHeader, BorderLayout.NORTH);
                customerDetails.add(scroll2, BorderLayout.CENTER);
            dashboard.add(cartDetails);
            dashboard.add(customerDetails);
        con.add(dashboard, BorderLayout.CENTER);

        // Fields at the bottom of the window
        JPanel fields = new JPanel(new BorderLayout());
            JPanel entryFields = new JPanel(new GridLayout(2, 1));
                JPanel customerField = new JPanel(new FlowLayout(FlowLayout.LEFT));
                    JLabel customerNameLabel = new JLabel("Customer Name:");
                    customerField.add(customerNameLabel);
                    customerField.add(customerName);
                JPanel paymentField = new JPanel(new FlowLayout(FlowLayout.LEFT));
                    JLabel paymentLabel = new JLabel("Payment:");
                    paymentField.add(paymentLabel);
                    paymentField.add(payment);
            entryFields.add(customerField);
            entryFields.add(paymentField);
            JPanel buttonFields = new JPanel(new FlowLayout(FlowLayout.RIGHT));
                buttonFields.add(confirmButton);
                buttonFields.add(cancelButton);
            fields.add(entryFields, BorderLayout.WEST);
            fields.add(buttonFields, BorderLayout.EAST);
        con.add(fields, BorderLayout.SOUTH);

        // Add action listeners
        customerName.getDocument().addDocumentListener(this);
        customerName.addActionListener(this);
        payment.addActionListener(this);
        confirmButton.addActionListener(this);
        cancelButton.addActionListener(this);

        // Decorating the frame
        cartHeader.setFont(Theme.HEADER2_FONT);
        customerHeader.setFont(Theme.HEADER2_FONT);
        customerNameLabel.setFont(Theme.HEADER3_FONT);
        paymentLabel.setFont(Theme.HEADER3_FONT);
        cartList.setFont(Theme.MONO_FONT);
        cartList.setOpaque(false);
        customerList.setFont(Theme.MONO_FONT);
        customerList.setOpaque(false);
        

        updateText();
    }

    // Accessors
    public String getCustomerName() {
        try {
            return customerName.getText().strip();
        } catch (Exception e) {
            e.printStackTrace();
            return "";
        }
    }
    public double getPayment() {
        try {
            return Double.parseDouble(payment.getText());
        } catch (Exception e) {
            e.printStackTrace();
            return 0.0;
        }
    }

    // Button actions and field completions
    public void actionPerformed(ActionEvent e) {
        // When user confirms of the transaction
        // By pressing enter on any field
        if (e.getSource() == customerName) { confirm();
        } else if (e.getSource() == payment) { confirm();
        
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
    
    // When user confirms of the entry
    public void confirm() {
        String customerName = getCustomerName();
        double payment = getPayment();

        Customer customer;
        double outstanding, revenue;

        // Failure cases
        // if there is no name entered
        // payment of 0 is valid
        if (customerName.equals("")) {
            JOptionPane.showMessageDialog(this, "Enter all fields properly first!");
            return;
        }
        
        // Otherwise
        // customer from customerName, either existing or new
        if (contacts.containsKey(customerName)) {
            customer = contacts.get(customerName);
        } else {
            customer = new Customer(customerName);
            contacts.put(customerName, customer);
        }

        // payment calculations
        outstanding = customer.getCredit() - cart.getWorth();
        revenue = outstanding + payment;

        // if payment is not enough such that the customer exceeds the maximum allowable debt
        if (Contacts.getMaxDebt() > revenue) {
            JOptionPane.showMessageDialog(this, "Current transaction will exceed maximum allowable debt!\nCannot Finalize transaction!");
            return;
        }

        // otherwise the transaction is approved
        // if the customer has paid off the debt
        if (revenue == 0) {
            contacts.remove(customerName);
        
        // if the customer has some remaining balance (either debt or advance)
        } else {
            customer.setCredit(revenue);
            customer.setDate(cart.getDate());
        }

        // update the transaction details
        cart.setCustomer(customerName);
        cart.setPayment(payment);

        // update the logs
        history.addTransaction(cart);

        // if the customer has no contact information in the contacts
        if (contacts.containsKey(customerName) && contacts.get(customerName).getContactNo().equalsIgnoreCase("")) {
            String contactNo = JOptionPane.showInputDialog(this, "Enter contact number for " + customerName + ":");
            contacts.get(customerName).setContactNo(contactNo);

            if (contactNo.equalsIgnoreCase("")) {
                JOptionPane.showMessageDialog(this, "No contact number entered.\nTransaction finalized!");
            } else {
                JOptionPane.showMessageDialog(this, "Contact number recorded.\nTransaction finalized!");
            }

        // otherwise, no need to ask for contact number
        } else {
            JOptionPane.showMessageDialog(this, "Transaction finalized!");
        }

        // return to parent frame
        this.dispose();
        parentFrame.returnToMenu();
    }

    // For updating all text areas
    public void updateText(){
        cartList.setText(cart.toString());
        cartWorth.setText(String.format("%.2f", cart.getWorth()));

        String search = getCustomerName();
        customerList.setText(contacts.search(search));
    }
}

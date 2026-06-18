// Main submenu for displaying current debtors/creditors

// Is also where the user can change the current maximum debt
// default of -200.0

package gui;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import group.Contacts;

public class JDirectory extends JCustomFrame implements ActionListener {
        // Buttons
        private JButton back = new JButton("Return to Main Menu");

        // Text areas and fields
        private JTextArea directoryList = new JTextArea();
        private JTextField changeField = new JTextField(15);
        private JLabel customerSize = new JLabel("Blank default");
        private JLabel maxDebtLabel = new JLabel("Blank default");

    // Constructor for the directory window
    public JDirectory(JCustomFrame parentFrame, Contacts contacts) {
        super("Directory");
        this.parentFrame = parentFrame;
        this.contacts = contacts;

        // Contacts list at the center of the window, with current max debt at the bottom
        JPanel center = new JPanel(new BorderLayout());
            // Header for the contacts list
            JPanel headerPanel = new JPanel(new BorderLayout());
                JLabel header = new JLabel ("Debtors list");
                JPanel customerInfo = new JPanel(new FlowLayout(FlowLayout.LEFT));
                    JLabel customerHeader = new JLabel("Number of Customers: ");
                    customerInfo.add(customerHeader);
                    customerInfo.add(customerSize);
                headerPanel.add(header, BorderLayout.NORTH);
                headerPanel.add(customerInfo, BorderLayout.SOUTH);
            // Scrollable contacts list
            JPanel directoryWindow = new JPanel();
            JScrollPane scroll = new JScrollPane(directoryWindow, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
                directoryList.setEditable(false);;
                directoryList.setColumns(50);
                directoryList.setText("Empty Default\n".repeat(50));
                directoryList.setEditable(false);
                directoryWindow.add(directoryList);
            // Current max debt at the bottom
            JPanel debtInfo = new JPanel(new FlowLayout());
                JLabel debtHeader = new JLabel("Current Max Debt: ");
                debtInfo.add(debtHeader);
                debtInfo.add(maxDebtLabel);
            center.add(headerPanel, BorderLayout.NORTH);
            center.add(scroll, BorderLayout.CENTER);
            center.add(debtInfo, BorderLayout.SOUTH);
            center.setBackground(Color.cyan);
        this.add(center, BorderLayout.CENTER);

        // Bottom panel for changing max debt and exiting
        JPanel bottom = new JPanel();
            JPanel changePanel = new JPanel();
                changePanel.setLayout(new BoxLayout(changePanel, BoxLayout.Y_AXIS));
                JLabel changeLabel = new JLabel("Change Max Debt");
                changePanel.add(changeLabel);
                changePanel.add(changeField);
                back.setPreferredSize(new Dimension(150, 50));
            bottom.add(changePanel);
            bottom.add(back);
            bottom.setLayout(new FlowLayout());
        this.add(bottom, BorderLayout.SOUTH);

        // Add action listeners
        changeField.addActionListener(this);
        back.addActionListener(this);

        // Decorating the frame
        header.setFont(Theme.HEADER2_FONT);
        debtHeader.setFont(Theme.HEADER3_FONT);
        maxDebtLabel.setFont(Theme.HEADER3_FONT);
        directoryList.setFont(Theme.MONO_FONT);
        directoryList.setOpaque(false);

        updateText();
    }
    
    // Actions in order
    public void actionPerformed(ActionEvent e) {
        // Change max debt
        if (e.getSource() == changeField) {
            try {
                double newDebt = Double.parseDouble(changeField.getText());
                Contacts.setMaxDebt(newDebt);
                updateText();
                JOptionPane.showMessageDialog(this, "Max debt changed to P" + (-1 * Contacts.getMaxDebt()) + " successfully!");

            } catch (NumberFormatException ex) {
                changeField.setText("Invalid input");
            }

        // Return to main menu
        } else if (e.getSource() == back) {
            this.dispose();
            parentFrame.updateText();
            parentFrame.setVisible(true);
        }
    }

    public void updateText() {
        directoryList.setText(contacts.toString());
        customerSize.setText(contacts.size() + "");
        maxDebtLabel.setText("P" + (-1 * Contacts.getMaxDebt()));
    }
}

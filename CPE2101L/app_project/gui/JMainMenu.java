// Main menu window

package gui;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import group.*;

public class JMainMenu extends JCustomFrame implements ActionListener{
    // Buttons
	private JButton transaction = new JButton("Transaction");
	private JButton inventory = new JButton("Inventory");
	private JButton	customerDirectory = new JButton("Customer Directory");
	private JButton nextDay = new JButton("Next Day");
	private JButton saveButton = new JButton("Save and Exit");
	private JButton dailyLogs = new JButton("Daily Logs");
	private JButton weeklyLogs = new JButton("Weekly Logs");
	private JButton monthlyLogs = new JButton("Monthly Logs");
	
	// Text areas and fields
	private JTextArea dayIndicatorLabel = new JTextArea();
	private JTextArea lowStock = new JTextArea();
	private JLabel period = new JLabel();

  public JMainMenu(History history, Stock stock, Contacts contacts) {
    super("Sari Sari Store Manager");
    this.history = history;
    this.stock = stock;
    this.contacts = contacts;

	  // Declarations
    JPanel mainPanel, panelOne, panelTwo, panelTwoButtons, panelTwoLogs;
    JPanel customerList;
    
    // Initialize panels, etc.
    mainPanel = new JPanel(new BorderLayout());
    panelOne = new JPanel(new GridLayout(5, 1));
    panelTwo = new JPanel(new BorderLayout());
    panelTwoButtons = new JPanel(new GridLayout(2,2));
    panelTwoLogs = new JPanel(new BorderLayout());
    customerList = new JPanel();
    
    // Configure components
    panelOne.add(transaction);
    panelOne.add(inventory);
    panelOne.add(customerDirectory);
    panelOne.add(nextDay);
    panelOne.add(saveButton);

    panelTwoButtons.add(period);
    panelTwoButtons.add(dailyLogs);
    panelTwoButtons.add(weeklyLogs);
    panelTwoButtons.add(monthlyLogs);
    
    period.setHorizontalAlignment(SwingConstants.CENTER);

    //Adding Inventory and Customer Data to the Logs
      JScrollPane scrollPane = new JScrollPane(customerList, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
      JPanel logPanel = new JPanel(new FlowLayout(FlowLayout.LEADING, 0, 5));

        // Add components
        dayIndicatorLabel.setAlignmentX(Component.LEFT_ALIGNMENT); // Align each component
        logPanel.add(dayIndicatorLabel);

        // lowStock.setText(stock.lowInventoryNotifier());
  
        scrollPane.setViewportView(logPanel);
        panelTwoLogs.add(scrollPane, BorderLayout.CENTER);
    
    panelTwo.add(panelTwoButtons, BorderLayout.NORTH);
    panelTwo.add(panelTwoLogs, BorderLayout.CENTER);
    panelTwo.add(lowStock, BorderLayout.SOUTH);

    mainPanel.add(panelOne, BorderLayout.WEST);
    mainPanel.add(panelTwo, BorderLayout.CENTER);

    add(mainPanel);

    // Add action listeners
    transaction.addActionListener(this);
    inventory.addActionListener(this);
    customerDirectory.addActionListener(this);
    nextDay.addActionListener(this);
    dailyLogs.addActionListener(this);
    weeklyLogs.addActionListener(this);
    monthlyLogs.addActionListener(this);
    saveButton.addActionListener(this);

    // Decorate the frame
    dayIndicatorLabel.setEditable(false);
    dayIndicatorLabel.setFont(Theme.MONO_FONT);
    dayIndicatorLabel.setOpaque(false);
    lowStock.setEditable(false);
    lowStock.setForeground(Color.RED);
    
    dailyLogs.setEnabled(false);
    period.setText("Day " + history.size());
    updateText();
}

 //Updating Data 
 public void updateText(){
    dayIndicatorLabel.setText(history.toString());
    lowStock.setText(stock.lowInventoryNotifier());
  }

    //Code for setting up action listeners
    @Override
    public void actionPerformed(ActionEvent e) {
       if(e.getSource() == transaction){
        JPoS transactionPage = new JPoS(this, contacts, history, stock);
        this.setVisible(false);
        transactionPage.setVisible(true);
       }
       else if(e.getSource() == inventory){
        JInventory inventoryPage = new JInventory(this, stock);
        this.setVisible(false);
        inventoryPage.updateText();
        inventoryPage.setVisible(true);
       } else if (e.getSource() == customerDirectory) {
        JDirectory customerDirectoryPage = new JDirectory(this, contacts);
        this.setVisible(false);
        // customerDirectoryPage.updateText();
        customerDirectoryPage.setVisible(true);
       } else if (e.getSource() == nextDay) {
        history.nextDay();
        this.updateText();
       }
      else if (e.getSource() == saveButton) {
        this.dispose();
        stock.toFile();
        contacts.toFile();
        history.toFile();
       }

       //Log Displays
       else if(e.getSource() == dailyLogs){
        dayIndicatorLabel.setText(history.toString());
        dailyLogs.setEnabled(false);
        weeklyLogs.setEnabled(true);
        monthlyLogs.setEnabled(true);
        period.setText("Day " + history.size()); 
        this.updateText();
       }
       else if(e.getSource() == weeklyLogs){
        dailyLogs.setEnabled(true);
        weeklyLogs.setEnabled(false);
        monthlyLogs.setEnabled(true);
        int currentWeek = ((history.size() - 1) / 7) + 1;
        period.setText("Week " + currentWeek); 
        this.updateText();
        dayIndicatorLabel.setText(history.weekSummary().toString());
       }
       else if(e.getSource() == monthlyLogs){
        dailyLogs.setEnabled(true);
        weeklyLogs.setEnabled(true);
        monthlyLogs.setEnabled(false);
        int currentMonth = ((history.size() - 1) / 30) + 1;
        period.setText("Month " + currentMonth);
        this.updateText();
        dayIndicatorLabel.setText(history.monthSummary().toString());
       }
    }
}


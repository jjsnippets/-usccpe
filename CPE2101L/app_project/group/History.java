// Class which stores all Logs

package group;

import java.io.*;
import java.util.ArrayList;

import indiv.Log;
import indiv.Transaction;

public class History extends ArrayList<Log> {
    public void addTransaction(Transaction cart) {
        this.get(this.size() - 1).addTransaction(cart);
    }

    //These are the functions to print out the profits based on different time periods
    public String toString(){
        String res = String.format(" %-7s %20s %20s %20s\n", "Day", "Total Payment", "Total Worth", "Revenue");
        int inc = 0;
        for (int i = this.size() - 1; i >= 0; i--) {
            Log log = this.get(i);
            int logNumber = this.size() - inc;
            res += String.format(" %-7s %20.2f %20.2f %20.2f\n", logNumber, log.getTotalPayment(), log.getTotalWorth(), log.getRevenue());
            inc++;
        }
        res += String.format("\n %-7s %20.2f %20.2f %20.2f\n", "Total", cumulativePayment(), cumulativeWorth(), cumulativeRevenue());
        return res;
    }

    public String weekSummary(){
        String res = String.format(" %-7s %20s %20s %20s\n", "Week", "Total Payment", "Total Worth", "Revenue");
        ArrayList<Log> weekLogs = new ArrayList<>();

        // adds information per week
        for (int i = 0; i < this.size(); i++) {
            if (i % 7 == 0) {
                weekLogs.add(new Log());
            }

            weekLogs.get(weekLogs.size() - 1).incTotalPayment(this.get(i).getTotalPayment());
            weekLogs.get(weekLogs.size() - 1).incTotalWorth(this.get(i).getTotalWorth());
        }

        // displays information per week in reverse order
        for (int i = weekLogs.size() - 1; i >= 0; i--) {
            Log log = weekLogs.get(i);
            res += String.format(" %-7s %20.2f %20.2f %20.2f\n", (i + 1), log.getTotalPayment(), log.getTotalWorth(), log.getRevenue());
        }
        res += String.format("\n %-7s %20.2f %20.2f %20.2f\n", "Total", cumulativePayment(), cumulativeWorth(), cumulativeRevenue());
        return res;
    }

    public String monthSummary(){
        String res = String.format(" %-7s %20s %20s %20s\n", "Month", "Total Payment", "Total Worth", "Revenue");
        ArrayList<Log> monthLogs = new ArrayList<>();

        // adds information per month
        for (int i = 0; i < this.size(); i++) {
            if (i % 30 == 0) {
                monthLogs.add(new Log());
            }

            monthLogs.get(monthLogs.size() - 1).incTotalPayment(this.get(i).getTotalPayment());
            monthLogs.get(monthLogs.size() - 1).incTotalWorth(this.get(i).getTotalWorth());
        }

        // displays information per month in reverse order
        for (int i = monthLogs.size() - 1; i >= 0; i--) {
            Log log = monthLogs.get(i);
            res += String.format(" %-7s %20.2f %20.2f %20.2f\n", (i + 1), log.getTotalPayment(), log.getTotalWorth(), log.getRevenue());
        }
        res += String.format("\n %-7s %20.2f %20.2f %20.2f\n", "Total", cumulativePayment(), cumulativeWorth(), cumulativeRevenue());
        return res;
    }

    public void nextDay(){
        this.add(new Log());                  // A new log entry at the start of the day
    }

    public double cumulativeWorth(){
        double totalWorth = 0;
        for(Log log : this){
            totalWorth += log.getTotalWorth();
        }
        return totalWorth;
    }

    public double cumulativePayment(){
        double totalPayment = 0;
        for(Log log : this){
            totalPayment += log.getTotalPayment();
        }
        return totalPayment;
    }

    public double cumulativeRevenue(){
        return cumulativePayment() - cumulativeWorth();
    }

    // file read and write operations
    public void fromFile() {
        try(BufferedReader br = new BufferedReader(new FileReader("data/log.csv"))){
            String line;
            while((line = br.readLine()) != null){
                String[] parts = line.split(",");
                if(parts.length == 2){
                    double totalPayment = Double.parseDouble(parts[0].strip());
                    double totalWorth = Double.parseDouble(parts[1].strip());
                    
                    Log log = new Log(totalPayment, totalWorth);
                    this.add(log);
                }
            }  
            System.out.println("Logs loaded from file!");     
            }catch(IOException e){
                e.printStackTrace(); // Handle exceptions
            }
    }

    public void toFile(){
        try(BufferedWriter bw = new BufferedWriter(new FileWriter("data/log.csv"))){
            for(Log log : this){
                bw.write(log.getTotalPayment() + ","+ log.getTotalWorth());
                bw.newLine();
            }
        
            System.out.println("Logs saved to file!");
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}

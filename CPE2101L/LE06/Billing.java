// LE 6.2: Patient-Billing
// Nov 5 2024
// Patient billing system, shows inheritance and polymorphism

/* Snippet program execution
Dr. A equals Dr. B? false
Alice equals Alice? true

====================
Doctor Information
Name: Dr. A
Specialty: General
Visit Fee: 1000.00

Patient Information
Name: Alice
Patient ID: P001

Billing Fee: 1000.00
====================

====================
Doctor Information
Name: Dr. B
Specialty: Pediatrician
Visit Fee: 1500.00

Patient Information
Name: Bob
Patient ID: P002

Billing Fee: 1500.00
====================

====================
Doctor Information
Name: Dr. C
Specialty: Surgeon
Visit Fee: 2000.00

Patient Information
Name: Charlie
Patient ID: P003

Billing Fee: 2000.00
====================

=== Income Statement ===
Dr. A from Alice        : 1000.00
Dr. B from Bob          : 1500.00
Dr. C from Charlie      : 2000.00

Total Billings          : 4500.00
====================



[B] ADD BILLING
[I] SHOW INCOME STATEMENT
[X] EXIT
 >> 
... */

package LE06;

import java.util.ArrayList;
import java.util.Scanner;

public class Billing {
    // class attributes
    private Doctor doctor;
    private Patient patient;

    // constructor
    public Billing(Doctor doctor, Patient patient) {
        this.doctor = doctor;
        this.patient = patient;
    }

    // polymorphic method
    public void writeOutput() {
        System.out.println("====================");
        System.out.println("Doctor Information");
        doctor.writeOutput();
        System.out.println();
        System.out.println("Patient Information");
        patient.writeOutput();
        System.out.println();
        System.out.printf("Billing Fee: %.2f\n", doctor.getVisitFee());
        System.out.println("====================");
    }

    public static void main(String[] args) {
        // declarations
        ArrayList<Billing> billings = new ArrayList<Billing>();

        // testing all methods
            // declarations and initializations
            Doctor doc1 = new Doctor("Dr. A", "General", 1000.0);
            Doctor doc2 = new Doctor("Dr. B", "Pediatrician", 1500.0);
            Doctor doc3 = new Doctor("Dr. C", "Surgeon", 2000.0);

            Patient pat1 = new Patient("Alice", "P001");
            Patient pat2 = new Patient("Bob", "P002");
            Patient pat3 = new Patient("Charlie", "P003");

            billings.add(new Billing(doc1, pat1));
            billings.add(new Billing(doc2, pat2));
            billings.add(new Billing(doc3, pat3));

            // testing equals methods
            System.out.println("Dr. A equals Dr. B? " + doc1.equals(doc2));
            System.out.println("Dr. C equals Dr. C? " + doc3.equals(doc3));
            System.out.println("Alice equals Bob? " + pat1.equals(pat2));
            System.out.println("Charlie equals Charlie? " + pat3.equals(pat3));
            System.out.println();

            // display all billings
            printBillings(billings);
            incomeStatement(billings);

            Patient.allPatients(billings);
            Doctor.allDoctors(billings);

            // reset for main code
            billings.clear();
            System.out.println();
            System.out.println();
            System.out.println();
        
        // driver code
        Scanner sc = new Scanner(System.in);
        char choice;

        do{
            // user menu prompt
			System.out.println("[B] ADD BILLING");
			System.out.println("[I] SHOW INCOME STATEMENT");
            System.out.println("[P] SHOW ALL PATIENTS");
            System.out.println("[D] SHOW ALL DOCTORS");
			System.out.println("[X] EXIT");
			System.out.print(" >> ");
			
			choice = Character.toUpperCase(sc.nextLine().strip().charAt(0));
			System.out.println();

            switch (choice) {
                case 'B': // add billing
                    addMenu(billings);
                    break;

                case 'I': // show income statement
                    incomeStatement(billings);
                    System.out.println();
                    break;

                case 'P': // show all patients
                    Patient.allPatients(billings);
                    break;

                case 'D': // show all doctors
                    Doctor.allDoctors(billings);
                    break;

                case 'X': // exit
                    break;

                default:
                    System.out.println("INVALID INPUT!");
                    System.out.println();

            }
        } while (choice != 'X');
        System.out.println("Thank you for using patient-billing system!");
        System.out.println();

        sc.close();
    }

    // utility methods
    // user menu for adding a bill
    public static void addMenu(ArrayList<Billing> billings){
        Doctor doctor = Doctor.addDoctor();
        System.out.println();
        Patient patient = Patient.addPatient();
        System.out.println();

        Billing billing = new Billing(doctor, patient);
        billings.add(billing);
        billing.writeOutput();
        System.out.println();

        System.out.println("Billing added successfully!");
    }

    // print all billings
    public static void printBillings(ArrayList<Billing> billings) {
        for (Billing billing : billings) {
            billing.writeOutput();
            System.out.println();
        }
    }

    // prints a summary of all billings with total
    public static void incomeStatement(ArrayList<Billing> billings) {
        System.out.println("=== Income Statement ===");
        double total = 0.0;
        for (Billing billing : billings) {
            System.out.printf("%-20s\t: %.2f\n", billing.doctor.getName() + " (" + billing.patient.getName() + ")", billing.doctor.getVisitFee());
            total += billing.doctor.getVisitFee();
        }
        System.out.println();
        System.out.printf("%-20s\t: %.2f\n", "Total Billings ", total);
        System.out.println("====================");
    }

    public Patient getPatient() {
        return this.patient;
    }

    public Doctor getDoctor() {
        return this.doctor;
    }
}

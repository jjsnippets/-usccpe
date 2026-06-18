package LE06;

import java.util.Scanner;
import java.util.ArrayList;

public class Patient extends Person {
    // class attributes
    private String patientID;

    private static Scanner sc = new Scanner(System.in); // for convenience

    // constructors
    public Patient() {
        super();
        this.patientID = "No ID yet";
    }

    public Patient(String name, String patientID) {
        super(name);
        this.patientID = patientID;
    }

    // accessors and mutators
    public void setPatientID(String patientID) {
        this.patientID = patientID;
    }

    public String getPatientID() {
        return this.patientID;
    }

    // polymorphic methods
    public void writeOutput() {
        super.writeOutput();
        System.out.println("Patient ID: " + this.patientID);
    }

    public boolean equals(Patient otherPatient) {
        return this.hasSameName(otherPatient) && this.patientID.equalsIgnoreCase(otherPatient.patientID);
    }

    // utility methods
    public static Patient addPatient() {
        Patient patient = new Patient();

        System.out.println("Enter Patient Information");
        System.out.print("Name >> ");
        patient.setName(sc.nextLine().strip());
        System.out.print("Patient ID >> ");
        patient.setPatientID(sc.nextLine().strip());

        return patient;
    }

    public String toString(){
        return "Patient Name: " + this.getName() + "\nPatient ID: " + this.getPatientID() + "\n";
    }

    public static void allPatients(ArrayList<Billing> billings){
        System.out.println("=== All Patients ===");
        for (Billing billing : billings) {
            System.out.println(billing.getPatient().toString());
        }
        System.out.println("====================");
    }
}

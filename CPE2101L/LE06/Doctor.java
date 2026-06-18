package LE06;

import java.util.Scanner;
import java.util.ArrayList;

public class Doctor extends Person {
    // class attributes
    private String specialty;
    private double visitFee;

    private static Scanner sc = new Scanner(System.in); // for convenience

    // constructors
    public Doctor() {
        super();
        this.specialty = "No specialty yet";
        this.visitFee = 0.00;
    }

    public Doctor(String name, String specialty, double visitFee) {
        super(name);
        this.specialty = specialty;
        this.visitFee = visitFee;
    }

    // accessors and mutators
    public void setSpecialty(String specialty) {
        this.specialty = specialty;
    }

    public String getSpecialty() {
        return this.specialty;
    }

    public void setVisitFee(double visitFee) {
        this.visitFee = visitFee;
    }

    public double getVisitFee() {
        return this.visitFee;
    }

    // polymorphic methods
    public void writeOutput() {
        super.writeOutput();
        System.out.println("Specialty: " + this.specialty);
        System.out.printf("Visit Fee: %.2f\n", this.visitFee);
    }


    public boolean equals(Doctor otherDoctor) {
        return this.hasSameName(otherDoctor) && this.specialty.equalsIgnoreCase(otherDoctor.specialty);
    }

    // utility methods
    public static Doctor addDoctor() {
        Doctor doctor = new Doctor();

        System.out.println("Enter Doctor Information");

        System.out.print("Name >> ");
        doctor.setName(sc.nextLine().strip());
        System.out.print("Specialty >> ");
        doctor.setSpecialty(sc.nextLine().strip());
        System.out.print("Visit fee >> ");
        doctor.setVisitFee(sc.nextDouble());
        sc.nextLine();

        return doctor;
    }

    public String toString(){
        return "Doctor name: " + this.getName() + "\nSpeciality: " + this.getSpecialty() + "\nVisit Fee: " + this.getVisitFee() + "\n";	
    }

    public static void allDoctors(ArrayList<Billing> billings){
        System.out.println("=== All Doctors ===");
        for (Billing billing : billings) {
            System.out.println(billing.getDoctor().toString());
        }
        System.out.println("====================");
    }
}

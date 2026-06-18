package LE06;
// as is from specifications

public abstract class Person {
    private String name;
    
    public Person() {
        this.name = "No name yet";
    }

    public Person(String name) {
        this.name = name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    public void writeOutput() {
        System.out.println("Name: " + this.name);
    }

    public boolean hasSameName(Person otherPerson) {
        return this.name.equalsIgnoreCase(otherPerson.name);
    }
}

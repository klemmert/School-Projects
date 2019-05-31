/*
 * This is to show an example of Inheritance as well as Encapsulation.
 *
 * Inheritance: GymLeader is the child class, Person is the parent class. I am reusing all the fields from the Person class and
 * implementing my own unique part to the child class.
 *
 * Encapsulation: I am keeping "sensitive" data hidden from users. I am using private variabes and providing public setters
 * and getters to access and update my private variables to the objects.
 */
package pokemon;

/**
 *
 * @author Kat
 */
public class GymLeader extends Person {
    
    //Badge is a variable where a Gym Leader is assigned a certain badge they hand out to trainers if beaten in a pokemon battle.
    private String badge;
    
    public GymLeader(String name, String[] pokemon, String badge) {
        super(name, pokemon);
        this.badge = badge;
    }
    
    //setters and getters
    public String getBadge(){
        return badge;
    }
    public void setBadge(String badge){
        this.badge = badge;
    }
}

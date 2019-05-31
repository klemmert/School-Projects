/*
 * This is to show an example of Inheritance as well as Encapsulation.
 *
 * Inheritance: Trainer is the child class, Person is the parent class. I am reusing all the fields from the Person class and
 * implementing my own unique part to the child class.
 *
 * Encapsulation: I am keeping "sensitive" data hidden from users. I am using private variabes and providing public setters
 * and getters to access and update my private variables to the objects.
 */
package pokemon;

import java.util.Arrays;

/**
 *
 * @author Kat
 */
public class Trainer extends Person {
    
    private int numOfBadges;
    private String[] badges = new String[8];
    
    public Trainer(String name, String[] pokemon, int numOfBadges, String[] badges) {
        super(name, pokemon);
        this.numOfBadges = numOfBadges;
        this.badges = Arrays.copyOf(badges, badges.length);
    }
    
    //setters and getters
    public int getBadgeNum(){
        return numOfBadges;
    }
    public String[] getBadges(){
        return Arrays.copyOf(badges, badges.length);
    }
    public void setBadgeNum(int numOfBadges){
        this.numOfBadges = numOfBadges;
    }
    public void setBadges(String[] badges){
        this.badges = Arrays.copyOf(badges, badges.length);
    }
}

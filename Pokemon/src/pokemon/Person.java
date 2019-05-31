/*
 * This is to show an example of Inheritance as well as Encapsulation.
 *
 * Inheritance: Person is the parent class while Trainer and GymLeader are its child classes. I am reusing all the fields from the Person class in
 * the child class as well as implementing their own unique parts.
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
public class Person {
    private String name;
    private String[] pokemon = new String[6];
    
    //constructor
    public Person(String name, String[] pokemon){
        this.name = name;
        this.pokemon = Arrays.copyOf(pokemon, pokemon.length);
    }
    
    //setters and getters
    public String getName(){
        return name;
    }
    public String[] getPokemon(){
        return Arrays.copyOf(pokemon, pokemon.length);
    }
    public void setName(String name){
        this.name = name;
    }
    public void setPokemon(String[] pokemon){
        this.pokemon = Arrays.copyOf(pokemon, pokemon.length);
    }
}

/*
 * This is a small self-made project to demonstrate OOP.
 * I am using the topic of Pokemon.
 */
package pokemon;

/**
 *
 * @author Kat Lemmert
 */
public class Pokemon {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        abstractSimulation start = new abstractSimulation();
        
        //only show information on trainers
        start.runTrainers();
        
        //only show information on people who aren't trainers or leaders
        //start.runPeople();
        
        //only show information on gym leaders
        //start.runGymLeaders();
        
        //show information on all the people in the abstract simulation start
        //start.runAll();
    }
    
}

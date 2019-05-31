/*
 * This is a small example of abstraction.
 *
 * Abstraction: There is the abstraction of importing files. We know it imports data to use arrays, but we don't know the gnitty gritty of how it all works.
 * There is also abstraction with this class. In this class, you can see all the instances of objects as well as the code needed to display the information. However,
 * this data will not be visible to the main function. The user will simply run it and all the data is listed based on what they want to see (trainers, leaders, people, or all).
 */
package pokemon;

import java.util.Arrays;

/**
 *
 * @author Kat
 */
public class abstractSimulation {
    private Trainer Kat = new Trainer("Kat", new String[] {"Eevee", "Charizard", "Arcanine" , "Dragonair"}, 3, new String[] {"Boulder Badge", "Cascade Badge", "Rainbow Badge"});
    private Pokedex eevee = new Eevee();
    private Pokedex charizard = new Charizard();
    private Pokedex arcanine = new Arcanine();
    private Pokedex dragonair = new Dragonair();
        
    private Trainer Michael = new Trainer("Michael", new String[] {"Pikachu", "Squirtle"}, 0, new String[] {""});
    private Pokedex pikachu = new Pikachu();
    private Pokedex squirtle = new Squirtle();
        
    private Person Ellie = new Person("Ellie", new String[] {"Persian"});
    private Pokedex persian = new Persian();
        
    private GymLeader Brock = new  GymLeader("Brock", new String[] {"Geodude", "Onix"}, "Boulder Badge");
    private Pokedex geodude = new Geodude();
    private Pokedex onix = new Onix();
        
    private GymLeader Misty = new  GymLeader("Misty", new String[] {"Staryu", "Starmie"}, "Cascade Badge");
    private Pokedex staryu = new Staryu();
    private Pokedex starmie = new Starmie();
        
    private GymLeader Surge = new  GymLeader("Lt. Surge", new String[] {"Voltorb", "Pikachu", "Raichu"}, "Thunder Badge");
    private Pokedex voltorb = new Voltorb();
    private Pokedex raichu = new Raichu();
        
    private GymLeader Erika = new  GymLeader("Erika", new String[] {"Victreebel", "Tangela", "Vileplume"}, "Rainbow Badge");
    private Pokedex victreebel = new Victreebel();
    private Pokedex tangela = new Tangela();
    private Pokedex vileplume = new Vileplume();
        
    private GymLeader Koga = new  GymLeader("Koga", new String[] {"Koffing", "Muk"}, "Soul Badge");
    private Pokedex koffing = new Koffing();
    private Pokedex muk = new Muk();
        
    private GymLeader Sabrina = new  GymLeader("Sabrina", new String[] {"Kadabra", "Mr. Mime", "Venomoth", "Alakazam"}, "Marsh Badge");
    private Pokedex kadabra = new Kadabra();
    private Pokedex mr_Mime = new Mr_Mime();
    private Pokedex venomoth = new Venomoth();
    private Pokedex alakazam = new Alakazam();
        
    private GymLeader Blaine = new  GymLeader("Blaine", new String[] {"Growlithe", "Ponyta", "Rapidash", "Arcanine"}, "Volcano Badge");
    private Pokedex growlithe = new Growlithe();
    private Pokedex ponyta = new Ponyta();
    private Pokedex rapidash = new Rapidash();
        
    private GymLeader Giovanni = new  GymLeader("Giovanni", new String[] {"Onix", "Rhyhorn", "Kangaskhan"}, "Earth Badge");
    private Pokedex rhyhorn = new Rhyhorn();
    private Pokedex kangaskhan = new Kangaskhan();
    
    public void runTrainers(){
        displayTrainers(Kat);
        System.out.println("Description of Pokemon in party: \n");
        eevee.pokemonEntry();
        charizard.pokemonEntry();
        arcanine.pokemonEntry();
        dragonair.pokemonEntry();
        
        System.out.println("\n");
        
        displayTrainers(Michael);
        System.out.println("Description of Pokemon in party:\n");
        pikachu.pokemonEntry();
        squirtle.pokemonEntry();
        
        System.out.println("\n");
    }
    
    public void runGymLeaders(){
        displayGymLeaders(Brock);
        System.out.println("Description of Pokemon in party:\n");
        geodude.pokemonEntry();
        onix.pokemonEntry();
        
        System.out.println("\n");
        
        displayGymLeaders(Misty);
        System.out.println("Description of Pokemon in party:\n");
        staryu.pokemonEntry();
        starmie.pokemonEntry();
        
        System.out.println("\n");
        
        displayGymLeaders(Surge);
        System.out.println("Description of Pokemon in party:\n");
        voltorb.pokemonEntry();
        pikachu.pokemonEntry();
        raichu.pokemonEntry();
        
        System.out.println("\n");
        
        displayGymLeaders(Erika);
        System.out.println("Description of Pokemon in party:\n");
        victreebel.pokemonEntry();
        tangela.pokemonEntry();
        vileplume.pokemonEntry();
        
        System.out.println("\n");
        
        displayGymLeaders(Koga);
        System.out.println("Description of Pokemon in party:\n");
        koffing.pokemonEntry();
        muk.pokemonEntry();
        
        System.out.println("\n");
        
        displayGymLeaders(Sabrina);
        System.out.println("Description of Pokemon in party:\n");
        kadabra.pokemonEntry();
        mr_Mime.pokemonEntry();
        venomoth.pokemonEntry();
        alakazam.pokemonEntry();
        
        System.out.println("\n");
        
        displayGymLeaders(Blaine);
        System.out.println("Description of Pokemon in party:\n");
        growlithe.pokemonEntry();
        ponyta.pokemonEntry();
        rapidash.pokemonEntry();
        arcanine.pokemonEntry();
        
        System.out.println("\n");
        
        displayGymLeaders(Giovanni);
        System.out.println("Description of Pokemon in party:\n");
        rhyhorn.pokemonEntry();
        kangaskhan.pokemonEntry();
    }
    
    public void runPeople(){
        displayPeople(Ellie);
        System.out.println("Description of Pokemon in party:\n");
        persian.pokemonEntry();
        
        System.out.println("\n");
    }
    
    public void runAll(){
        runTrainers();
        runPeople();
        runGymLeaders();
    }
    
    public void displayTrainers(Trainer trainer){
        System.out.println("Trainer Name: " + trainer.getName());
        System.out.println("Trainer Pokemon: " + Arrays.toString(trainer.getPokemon()));
        System.out.println("Num of Badges: " + trainer.getBadgeNum());
        System.out.println("Trainer Badges: " + Arrays.toString(trainer.getBadges()));
    }
    
    public void displayGymLeaders(GymLeader gymLeader){
        System.out.println("Leader Name: " + gymLeader.getName());
        System.out.println("Leader's Pokemon: " + Arrays.toString(gymLeader.getPokemon()));
        System.out.println("Type of Gym Badge: " + gymLeader.getBadge());
    }
    
    public void displayPeople(Person person){
        System.out.println("Person's Name: " + person.getName());
        System.out.println("Person's Pokemon: " + Arrays.toString(person.getPokemon()));
    }
}

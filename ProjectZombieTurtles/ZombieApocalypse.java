
public class ZombieApocalypse {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
        // set some number to be zombies
        int z = 20;
        //this is number of total ZombieTurtles, only z of which are initially zombies
        int zTurtles = 300;
        int N = 250;
        /*need a Universe object that we can put turtles into. turtles will be circles and change colors when they 
         * come in contact with other turtles that are inflicted with zombie-ism
         * 
         */
        Universe un = new Universe(zTurtles,z,600, 600);
        /*our simulation will run for N iterations */
        for(int i = 0; i < N; i++)
        {
            /*choose new random location for all Turtles in the Universe */
            un.moveZombies();
            /*Convert new zombies from Turtle population */
            un.zombieAttack();
           
        }
            

	}

}

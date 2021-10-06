import java.util.Scanner;
public class YahtzeeGame{

	public static void main(String[] args) {

		Scanner input = new Scanner(System.in);
		int [] dice = new int [5];
		int [] scorecard = new int [13];

		int i, j;
		int choice;
		int [] turnwise_options = new int[]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};            // This array would help us remember the choice user made in each turn so as to prevent user making that choice again

		for(j = 0; j <= 12 ; j++)                                                                           // Loop governing each turn
		{
	        System.out.println("Turn " + (j + 1) + " : ");

			dice = rollDice(dice);
			displayDice(dice);

	        dice = reroll(dice, 1);
	        displayDice(dice);

	        dice = reroll(dice, 2);
	        displayDice(dice);

	        dice = reroll(dice, 3);
	        displayDice(dice);
	        
		 	System.out.println("Which item would you like to score on your score card?:\n 0 = aces  1 = twos  2 = threes  3 = fours  4 = fives  5 = sixes 6 = three of a kind  7 = four of a kind  8 = full house 9 = small straight  10 = large straight 11 = yahtzee 12 = chance ");
		 	choice = input.nextInt(); 

		 	turnwise_options[j] = choiceCheck( turnwise_options, choice);                                 // checking the valididty of choice                             

		 	choice = turnwise_options[j];


		 	if(choice >= 0 && choice <= 5)                                                               
		 	{
		 		scorecard[choice] = sumOfDice( dice, choice + 1);                                        // Calling function to sum dice with particular face value
		 	}

		 	switch(choice){

		 		case 6 :
		 		        if(threeOfaKind(dice))
		 		        {
		 		            scorecard[choice] = sumAllDice(dice);
		 		        }

		 		        else
		 		        {
		 		        	errorDisplay();
		 		        	scorecard[choice] = 0;
		 		        }

		 		        break;

		 		case 7 :
		 		        if(fourOfaKind(dice))
		 		        {
		 		            scorecard[choice] = sumAllDice(dice);
		 		        }

		 		        else
		 		        {
		 		        	errorDisplay();
		 		        	scorecard[choice] = 0;
		 		        }
		 		        
		 		        break;
		 		case 8 :
		 		        if(fullHouse(dice))
		 		        {
		 		            scorecard[choice] = 25;
		 		        }
		 		        
		 		        else
		 		        {
		 		        	errorDisplay();
		 		        	scorecard[choice] = 0;
		 		        }

		 		        break;

		 		case 9 :
		 		        if(smallStraight(dice))
		 		        {
		 		            scorecard[choice] = 30;
		 		        }

		 		        else
		 		        {
		 		        	errorDisplay();
		 		        	scorecard[choice] = 0;
		 		        }
		 		        break;

		 	    case 10 :
		 	            if(largeStraight(dice))
		 	            {	
		 		             scorecard[choice] = 40;
		 		        }
		 		        
		 		        else
		 		        {
		 		        	errorDisplay();
		 		        	scorecard[choice] = 0;
		 		        }     
		 		        break;

		 		case 11 :
		 		        if(allSame(dice))
		 		        {
		 		            scorecard[choice] = 50;
		 		        }

		 		        else
		 		        {
		 		        	errorDisplay();
		 		        	scorecard[choice] = 0;
		 		        }

		 		        break;

		 		case 12 :
		 		        scorecard[choice] = sumAllDice(dice);
		 		        break;
		 		        
		 		default :
		 		        break;

		 	} 

		 	System.out.print("Updated Scoresheet : ["); 

	        for(i = 0; i <= 11 ; i++)                                                                           //Displaying scorecard
			{
		 		System.out.print(scorecard[i] + ", ");
	        }  

		    System.out.println(scorecard[i] + " ]"); 


	 	}

	 	finalScore(scorecard);                                                                                  // Total score

	}








	 public static int [] rollDice(int[] diceArray)                                     // Allows us to randomize each dice of the array diceArray
	 {
	 	int k;
	 	for(k = 0; k < diceArray.length ; k++)
	 	{
	 		diceArray[k] = (int) (Math.random() * 6 + 1);
	 	}

	 	return diceArray;
	 }


	 public static void displayDice(int[] diceArray)                                   // Allows us to display each dice value
	 {
	 	int k;

	 	System.out.print("[");

	 	for(k = 0; k < diceArray.length - 1 ; k++)
	 	{
	 		System.out.print(diceArray[k] + ", ");
	 	}

	 	System.out.println(diceArray[k] + "]");
	 
	 }




     public static int [] reroll(int[] diceArray, int attempt)                        // Allows us to re- roll the specific dices entered by the user..
	  {
	  	Scanner input = new Scanner(System.in);
	  	System.out.println("Reroll attempt " + attempt + " :-");
	  	System.out.print("How many dice would you like to reroll ? ");
	  	int number = input.nextInt();
        if(number > 0 && number < 5)
        {
		  	System.out.println("Indicate the dice number(s) 0-4 you would like to reroll");

	        
	        int index;
	        int i;

		  	for(i = 0; i < number ; i++)
		  	{
		  		index = input.nextInt();
		  		diceArray[index] = (int) (Math.random() * 6 + 1);

		  	} 

	    }

	    else if ( number == 5)
	    {
	    	diceArray = rollDice(diceArray);
	    }

	  	return diceArray;

	  }


	  public static int sumAllDice(int[] dice)                                       // It sums all the dice values
	  {
	  	int sum = 0;
	  	int i;

	  	for( i = 0; i < dice.length ; i++)
	  	{
	  		sum += dice[i];
	  	}

	  	return sum;

	  }


	  public static int sumOfDice(int[] dice, int faceValue)                      // This method sums all the dices have the value same as facevalue
	  {
	  	int sum = 0;
	  	int i;

	  	for( i = 0; i <  dice.length ; i++)
	  	{
	  		if(dice[i] == faceValue)
	  		sum += dice[i];
	  	}

	  	return sum;

	  }


	  public static void finalScore(int [] scorecard)                          // Method calculating each scorecard category to give user his final score
	  {
	  	int i;
	  	int sum = 0;

	  	for(i = 0; i < scorecard.length ; i++)
	  	{
           sum += scorecard[i];
	  	}

	  	System.out.println("Your final score is : " + sum);
	  }



	  public static int choiceCheck(int[] list_of_options, int current_option)  // This method compares user's current choice with the choices he made earlier
	  {
	  	Scanner input = new Scanner(System.in);
	  	
	  	for( int i = 0; i < list_of_options.length ; i++)
	  	{
	  		if(list_of_options[i] == current_option)                            // If the category was chosen earlier, it asks user to make another choice
	  		{
	  			System.out.println("Error!!\nYou've already chosen this category before !!");
	  			System.out.println("0 = aces  1 = twos  2 = threes  3 = fours  4 = fives  5 = sixes 6 = three of a kind  7 = four of a kind  8 = full house 9 = small straight  10 = large straight 11 = yahtzee 12 = chance ");
	  			System.out.print("Make another choice : ");
	  			current_option = input.nextInt();
	  			current_option = choiceCheck( list_of_options, current_option); // Reccursive call made to check the newly entered choice by the user
	  		}
	  	}

	  	return current_option;


	  }

	  public static boolean threeOfaKind( int[] dice)                           // Checking if any 3 dices have same facevalue
	  {
        int i, j, k;

	  	for( i = 0 ;i < dice.length ; i++)                                     // Fixing one die to compared it with other
	  	{
	  		for( j = i+1 ;j < dice.length ; j++)                               // Fixing another die            
	  		{
	  			for( k = j+1 ;k < dice.length ; k++)                           // considering the other die
	  			{
	  					if(dice[i] == dice[j] && dice [j] == dice[k])          // Comparing the three dies and returning true if they are alike
	  					{
	  						return true;
	  					}
	  	              
	  	        }

	  		}

	  	}

	  	return false;

	  }	


	  	public static boolean fourOfaKind( int[] dice)                       // Checking if any 4 dices have same facevalue
	  {
	  	int i, j, k, l;

	  	for( i = 0 ;i < dice.length ; i++)                                   // Here also fixing dices and comparing them
	  	{
	  		for( j = i+1 ;j < dice.length ; j++)
	  		{
	  			for( k = j+1 ;k < dice.length ; k++)
	  			{
	  				for(l = k+1; l < dice.length ; l++)
	  				{
                        if(dice[i] == dice[j] && dice [j] == dice[k] && dice[k] == dice[l])
	  					{
	  						return true;
	  					}

	  				}
	  					
	  	              
	  	        }

	  		}

	  	}

	  	return false;

	  }	

	  	public static boolean fullHouse( int[] dice)                                  // This method is used to confirm fullhouse criteria
	  	{
	  	    int i,j;
	  	    int value1, value2;
	  	    int v1count, v2count;

	  	    value1 = dice[0];                                                     // Getting value 1
            i = 0;
	  	    do
	  	    {
	  	    	i++;

	  	    }while(value1 == dice[i]);

	  	    value2 = dice[i];                                                   // Getting value2 different from value 1

	  	    v1count = 0;
	  	    v2count = 0;

	  	    for(j = 0 ; j < dice.length ; j++)                                 // Counting how many dices have value 1 and value 2
	  	    {
	  	    	if(dice[j] == value1)
	  	    	{
	  	    		v1count++;
	  	    	}

	  	    	else if(dice[j] == value2)
	  	    	{
	  	    		v2count++;
	  	    	}
	  	    }

	  	    if((v1count == 2 && v2count == 3) || (v1count ==3 && v2count ==2))       // If 2 dices have value1 and 3 dices have value2  or   3 dices have value2 and 2 dices have value1,  we return true
	  	    {
	  	    	return true;
	  	    }

	  	    else{
	  	    	return false;
	  	    }
	  	
       }


       public static boolean smallStraight(int[] dice)                           // This method fixes a dice and then try to find a dice with one less than its facevalue,   then again tries to find a dice with one lesser facevalue...to confirm if 4 such dice exists
       {
       	for( int i = 0; i < dice.length; i++)
       	{
       		for( int j = 0 ; j < dice.length ; j++)
       		{
       			if((dice[i] - 1) == dice[j])
       			{
       				for( int k = 0; k < dice.length; k++ )
       				{
       					if((dice[j] - 1)  == dice[k])
       					{
       						for(int l = 0; l < dice.length; l++)
       						{
       							if((dice[k] - 1) == dice[l])
       							{
       								return true;
       							}
       						}
       					}
       				}
       			} 
       		}
       	}

       	return false;
       }

       public static boolean largeStraight(int[] dice)                        // This method checks if there are five consecutive dices or not
       {                                                                      // 2-5 numbered dices should be present and atleast one of 1 or 6 should be present
       	int count2 = 0;
       	int count3 = 0;
       	int count4 = 0;
       	int count5 = 0;
       	int count1_6 = 0;
       	for( int i = 0; i < dice.length ; i++)
       	{
       		if( dice[i] == 2)
       		{
               count2++;
       		}

       		if( dice[i] == 3)
       		{
               count3++;
       		}

       		if( dice[i] == 4)
       		{
               count4++;
       		}

       		if( dice[i] == 5)
       		{
               count5++;
       		}

       		if( dice[i] == 1 || dice[i] == 6)
       		{
               count1_6++;
       		}

       	}
       	if( count1_6 == 1 && count2 == 1 && count3 == 1 && count4 == 1 && count5 == 1)
       	{
       		return true;
       	}
       	else
       	{
       		return false;
       	}

       }

       public static boolean allSame(int[] dice)                                                     // This method checks the Yahtzee category condition that all dices have same facevalue
       {
       	int i;
       	int count;
       	int value = dice[0];

       	i=0;
       	count = 0;
       	do
       	{
       		if(value == dice[i])
       		{
       			count++;
       		}
           i++;

       	}while((i < dice.length));

       	if(count == 5)
       	{
       		return true;
       	}

       	else
       	{
       		return false;
       	}

       }

       public static void errorDisplay()  //Method for displying one type of error
       {
       	System.out.println("ERROR!! \nYour selected option doesn't fullfill that category's criteria. So you will recieve 0 point in this category.");
       }
	  	

}



	  	


























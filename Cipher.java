
import java.util.Scanner;
public class Cipher{

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		String plaintext, ciphertext, decrypttext;
		int shift_key, guess;

		System.out.println("Enter a phrase to encrypt : "); // Asking for a phrase from the user
		plaintext = sc.nextLine();

		shift_key = (int)((Math.random() * 53) - 26);  // Generating a random shift key betwwen -26 an 26

    	ciphertext = caeserCipher(plaintext, shift_key);  // Calling encryption method

        System.out.println("Your Encrypted message : " + ciphertext);

        System.out.println("Enter your guess to decrypt the phrase (-26 to 26) : ");

		do{                                                                   
			guess = sc.nextInt();

			decrypttext = decrypt(ciphertext, guess);

			if(guess == shift_key)
			{
				System.out.println("Correct! Your phrase was encrypted using a shift of: " + shift_key);
			}
			else
			{
				System.out.println("That's not the exact right number, although it decrypts to: " + decrypttext);
			}

		  }while(guess != shift_key);

		
	}

	public static String caeserCipher(String plaintext, int shift)  // Encrypting message 
	{
		int i;
		char ch;
		String output = "";

		if(shift> 0) 
		{
			for(i = 0; i <plaintext.length(); i++ )  //Performing right shift
			{
               ch = rightShiftCharacter(plaintext.charAt(i), shift);
               output += ch;
			}

		}


		else 
		{                                                                                                     
			for(i = 0; i <plaintext.length(); i++ )  // Performing left shift
			{
               ch = leftShiftCharacter(plaintext.charAt(i),shift);
               output+= ch;
			}

		}

		return output;
	}

	

	public static char rightShiftCharacter(char ch, int shift) //Right Shift and checking if the character is lowercase, uppercase or a digit.                 
	{
		shift = Math.abs(shift); 
		if(digit(ch))                                                                                                                                                                             
		{
			int i = (int)ch + shift;
			ch = (char)i;
			if(ch >= '0' && ch <= '9')
			{
				return ch;
			}
			else
			{
				i = i - '9';

                if(i == 20)
				{
					i = 10;
				}
				else if( i > 10)
				{
					i = ( i % 10);
				}

				i = '0' + i - 1;
				ch = (char)i;
		    }
		}                                                                                   


		else if(lowercase(ch))                                                                                     
		{
			int i = (int)ch + shift;
			ch = (char)i;
			if(ch >= 'a' && ch <= 'z')
			{
				return ch;
			}
			else
			{
				i = i - 'z';
				i = 'a' + i - 1;
				ch = (char)i;
		    }
		}
		
		else if(uppercase(ch))
		{                                                                                   
			int i = (int)ch + shift;
			ch = (char)i;
			if(ch >= 'A' && ch <= 'Z')
			{
				return ch;
			}
			else
			{
				i = i - 'Z';
				i = 'A' + i - 1;
				ch = (char)i;
		    }
		}    

  
		return ch;
	}

    public static char leftShiftCharacter(char ch, int shift)   //Left Shift and  checking if the character is lowercase, uppercase or a digit.                    
	{
		shift = Math.abs(shift);


		if(digit(ch))
		{
			int i = (int)ch - shift;
			ch = (char)i;
			if(ch >= '0' && ch <= '9')
			{
				return ch;
			}
			else
			{
				i = '0' - i;

				if(i == 20)
				{
					i = 10;
				}

				else if( i > 10)
				{
					i = ( i % 10);
				}

				i = '9' - i + 1;
				ch = (char)i;
		    }
		}    



		else if(lowercase(ch))
		{
			int i = (int)ch - shift;
			ch = (char)i;
			if(ch >= 'a' && ch <= 'z')
			{
				return ch;
			}
			else
			{
			
				i = 'a' - i;
				i = 'z' - i + 1;
				ch = (char)i;
		    }
		}
		
		else if(uppercase(ch))
		{
			int i = (int)ch - shift;
			ch = (char)i;
			if(ch >= 'A' && ch <= 'Z')
			{
				return ch;
			}
			else
			{
			
				i = 'A' - i;
				i = 'Z' - i + 1;
				ch = (char)i;
		    }
		}    

        

		return ch;
	}

	

	public static boolean uppercase(char ch)  // Checking if character ch is uppercase                            
	{
		if(ch>= 'A' && ch<= 'Z')
		{
			return true;
		}

		else
		{
			return false;
		}
		
	}

	public static boolean lowercase(char ch)  // Checking if character ch is lowercase                                      
	{
		if(ch>= 'a' && ch<= 'z')
		{
			return true;
		}

		else
		{
			return false;
		}
		
	}

	public static boolean digit(char ch)  // Checking if character ch is a digit
	{
		if(ch>= '0' && ch<= '9')
		{
			return true;
		}

		else
		{
			return false;
		}

	}

	public static String decrypt( String text, int shift)  // Decrypting message
	{
		int i;
		char ch;
		String message = "";

		if(shift> 0)                                                                             
		{
			for(i = 0; i <text.length(); i++ )   // Performing left shift to obtain decrypted message
			{
               ch = leftShiftCharacter(text.charAt(i),shift);
               message = message + ch;
			}

		}

		else                                                                                    
		{
			for(i = 0; i <text.length(); i++ )  // Performing right shift to obtain decrypted message
			{
               ch = rightShiftCharacter(text.charAt(i),shift);
               message = message + ch;
			}

		}

		return message;

	}

}		
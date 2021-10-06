
import java.util.Scanner;
public class Encrypt{

	public static void main(String[] args) {

		Scanner scan = new Scanner(System.in);

		System.out.print("\nEnter a phrase to encrypt : ");
		String plaintext = scan.nextLine();
		int shift = (int)((Math.random() * 53) - 26);
    	String ciphertext = caeserCipher(plaintext, shift);
        System.out.println("\nEncrypted message is : " + ciphertext);
        System.out.print("\nEnter your guess to decrypt the phrase (-26 to 26) : ");
        int matching_key;

		do{
			matching_key = scan.nextInt();
			if(matching_key == shift){
				System.out.println("Correct! Your phrase was encrypted using a shift of: " + shift);
			}
			else{
				System.out.println("That's not the exact right number, although it decrypts to: " + decrypt(ciphertext, matching_key));
			}
		}while(matching_key != shift);

		


	}

	public static String caeserCipher(String plaintext, int shift)
	{
		int i;
		char ch;
		String output = "";

		if(shift> 0)
		{
			for(i = 0; i <plaintext.length(); i++ )
			{
               ch = rightShiftCharacter(plaintext.charAt(i), shift);
               output += ch;
			}

		}


		else
		{
			for(i = 0; i <plaintext.length(); i++ )
			{
               ch = leftShiftCharacter(plaintext.charAt(i),shift);
               output+= ch;
			}

		}

		return output;
	}

	

	public static char rightShiftCharacter(char ch, int shift)
	{
		shift = Math.abs(shift);

		if(isLowercase(ch))
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
		
		else if(isUppercase(ch))
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

        else if(isDigit(ch))
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
				i = '0' + i - 1;
				ch = (char)i;
		    }
		}    

	
		return ch;
	}

    public static char leftShiftCharacter(char ch, int shift)
	{
		shift = Math.abs(shift);

		if(isLowercase(ch))
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
		
		else if(isUppercase(ch))
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

        else if(isDigit(ch))
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
				i = '9' - i + 1;
				ch = (char)i;
		    }
		}    

		return ch;
	}

	public static boolean isDigit(char ch)
	{
		if(ch>= '0' && ch<= '9')
			return true;

		else
			return false;

	}

	public static boolean isUppercase(char ch)
	{
		if(ch>= 'A' && ch<= 'Z')
			return true;

		else
			return false;
		
	}

	public static boolean isLowercase(char ch)
	{
		if(ch>= 'a' && ch<= 'z')
			return true;

		else
			return false;
		
	}

	public static String decrypt( String ciphertext, int shift)
	{
		int i;
		char ch;
		String output = "";

		if(shift> 0)
		{
			for(i = 0; i <ciphertext.length(); i++ )
			{
               ch = leftShiftCharacter(ciphertext.charAt(i),shift);
               output += ch;
			}

		}

		else
		{
			for(i = 0; i <ciphertext.length(); i++ )
			{
               ch = rightShiftCharacter(ciphertext.charAt(i),shift);
               output+= ch;
			}

		}

		return output;

	}


	

}
		
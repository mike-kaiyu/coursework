package assignment;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Pattern;

/**
 * The Class stringMatch.
 *
 * @author Kai-Yu Lu16; ID:1614649.
 */
public class stringMatch {

    /**
     * The kb for getting input.
     */
    Scanner kb = new Scanner(System.in);

    /**
     * The userAll is to apply every tweet in this class.
     */
    List<String[]> userAll = new ArrayList<String[]>(); //Loaded and stored tweets from class "userClass".

    /**
     * Instantiates a new string match.
     *
     * @param uData the u data.
     * @throws Exception the exception.
     */
    public stringMatch(userData uData) throws Exception {    //Constructor
        userAll = uData.user;                          //Initialize uData which is user in userDta.
    }

    /**
     * Do match. Print the matched results.
     */
    public void doMatch() {          //Execute the string match.
        String keyWord = kb.next(); //Input one word for string match.
        String pattern = ".*" + keyWord + ".*"; //Set the pattern.
        String lower = "";
        pattern.toLowerCase();     //Lower the pattern.
        int totalMatched = 0;       //Initialize the number of matched result.
        for (int i = 0; i < userAll.size(); i++) { //Get tweets
            for (int j = 0; j < userAll.get(i).length; j++) {  //Get each cell of excel.
                lower = userAll.get(i)[j].toLowerCase(); //Get each cell of excel and lower it.

                if (Pattern.matches(pattern.toLowerCase(), lower)) { // Detect if the input is detected. 
                    getRow(userAll.get(i));     //Here the type is array, so use getRow to get the content in 
                    System.out.println("This is in row " + (i + 1) + " column: " + (j + 1) + " cell content: " + userAll.get(i)[j]); //Print the results. 
                    //System.out.println(getRow(userAll.get(i))); //For testing.
                    totalMatched += 1; //Count how many matches.
                }
            }
        }

        System.out.println(totalMatched + "matched results!");
    }

    /**
     * Gets the row is to extract the content in array type.
     *
     * @param test the test.
     * @return the row.
     */
    public String getRow(String[] test) { //Get the content in each row because the passed in parameter is array type.
        String getRow = "";
        for (int i = 0; i < test.length; i++) {
            getRow += test[i];
        }
        return getRow;
    }
}

package assignment;

import static java.lang.Integer.parseInt;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

/**
 * A class to find out top 10 users. It has the loaded data from class
 * "userData".
 *
 * @author Kai-Yu Lu16; ID:1614649
 */
public class FindTopUser {

    /**
     * The kb for getting input.
     */
    Scanner kb = new Scanner(System.in);

    /**
     * The userAll is to apply every tweet in this class
     */
    List<String[]> userAll = new ArrayList<String[]>();//Loaded and stored tweets from class "userClass".

    /**
     * Instantiates a new find top user.
     *
     * @param uData the u data
     */
    public FindTopUser(userData uData) {
        userAll = uData.user; //Constructor.
        //Initialize uData which is user in userDta.
    }

    /**
     * Find top user.
     */
    public void findTopUser() {
        User table;
        List<User> utable = new ArrayList<User>();
        for (int i = 1; i < userAll.size(); i++) {         //Pass every parameter to table.
            table = new User();
            table.setID(userAll.get(i)[0]);        //Set ID.
            table.setUserName(userAll.get(i)[3]);  //Set user name.
            table.setNickName(userAll.get(i)[4]);  //Set nick name.
            try {
                table.setFollowers(parseInt(userAll.get(i)[10])); //Get followers in userAll and change it into int type.
            } catch (Exception e) {
                table.setFollowers(0);
            }
            utable.add(table);            //Add the completed table to a arraylist called utable.
        }
        Collections.sort(utable);           //Sort the utable by followers.

        ArrayList<String> printedUsers = new ArrayList<String>();  //Stored the duplicated users.

        for (int i = 0; i < utable.size(); i++) {        //Filter the duplicated users. Just print the users at the moment they get the followers the most.
            if (printedUsers.size() == 10) {
                break;
            } else {
                if (printedUsers.contains(utable.get(i).getUserName())) {
                } else {
                    printedUsers.add(utable.get(i).getUserName());
                    System.out.println(utable.get(i).toString());
                }
            }
        }
    }
}

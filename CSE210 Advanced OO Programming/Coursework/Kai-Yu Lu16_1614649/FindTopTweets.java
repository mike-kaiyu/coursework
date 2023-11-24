package assignment;

import static java.lang.Integer.parseInt;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

/**
 * A class to find out top 10 tweets. It has the loaded data from class
 * "userData".
 *
 * @see userData.
 * @author Kai-Yu Lu16; ID:1614649
 */
public class FindTopTweets {

    /**
     * The kb for getting input.
     */
    Scanner kb = new Scanner(System.in);

    /**
     * The userAll is to apply every tweet in this class.
     */
    List<String[]> userAll = new ArrayList<String[]>();//Loaded and stored tweets from class "userClass".

    /**
     * Instantiates a new find top tweets. Constructor to initialize uData which
     * is user in userDta.
     *
     * @param uData the u data
     */
    public FindTopTweets(userData uData) {
        userAll = uData.user;

    }

    /**
     * This method is to find out top 10 tweets. It has the loaded data from
     * class "userData".
     *
     */
    public void findTopTweets() {
        Tweet table;
        List<Tweet> utable = new ArrayList<Tweet>();

        for (int i = 1; i < userAll.size(); i++) {  //Pass every parameter to table.
            int Favs = 0;
            int RTs = 0;
            /*Favs and RTs in userAll are both string, they will
                              be added later, so initialized them in int type.  
             */
            table = new Tweet();
            table.setID(userAll.get(i)[0]);             //Set ID.
            table.setDate(userAll.get(i)[1]);           //Set data.
            table.setHour(userAll.get(i)[2]);           //Set hour.           
            table.setUserName(userAll.get(i)[3]);       //Set user name.
            table.setNickName(userAll.get(i)[4]);       //Set nick name.
            table.setTweetContent(userAll.get(i)[5]);   //Set tweet content.
            try {
                Favs = parseInt(userAll.get(i)[6]); //Get Favs in userAll and change it into int type.
                table.setFavs(Favs); //Set Favs.    //Set modified Favs.                          
            } catch (Exception e) {
                table.setFavs(0);
            }
            try {
                RTs = parseInt(userAll.get(i)[7]);   //Get RTs in userAll and change it into int type.
                table.setRTs(RTs);                  //Set modified RTs.  
            } catch (Exception e) {
                table.setRTs(0);
            }
            table.setLatitude(userAll.get(i)[8]);  //Set latitude.
            table.setLongitude(userAll.get(i)[9]); //Set longitude
            try {
                table.setFollowers(parseInt(userAll.get(i)[10]));//Get followers in userAll and change it into int type.
            } catch (Exception e) {
                table.setFollowers(0);
            }
            table.setSumFR(Favs, RTs);  //Sum Favs and RTs, and set the added result.
            utable.add(table);          //Add the completed table to a arraylist called utable.
        }
        Collections.sort(utable);       //Sort the utable by the parameter SumFR.
        for (int i = 0; i < 10; i++) {       //Print the top 10 tweets.
            System.out.println(utable.get(i).toString());
        }
    }
}

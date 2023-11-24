package assignment;

import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * The Class main.
 *
 * @author Kai-Yu Lu16; ID:1614649.
 */
public class main {

    /**
     * The exit.
     *
     */
    private static boolean exit;

    /**
     * Sentence is to input the string for matching.
     *
     * @return the string.
     */
    public static String sentence() { //To avoid the conflict of changing input type.
        Scanner s = new Scanner(System.in);
        System.out.println("Please input the keyword");
        String keySentence = s.next();

        return keySentence;
    }

    /**
     * The main method.
     *
     * @param args the arguments.
     * @throws Exception the exception.
     */
    public static void main(String[] args) throws Exception {
        String sentence = null;
        userData uData = new userData();
        uData.loadDate();
        stringMatch sMatch = new stringMatch(uData);
        FindTopUser topUser = new FindTopUser(uData);
        FindTopTweets topTweet = new FindTopTweets(uData);
        IndexCreater indexCreater = new IndexCreater(uData);
        exit = false;

        while (!exit) {
            Scanner kb = new Scanner(System.in);
            System.out.println("1-Print top 10 tweets\n"
                    + "2-Print top 10 user\n"
                    + "3-Tweet search based on string matching\n"
                    + "4-tweet search based on full text searching using Lucene.\n");
            try {
                int input = kb.nextInt();
                switch (input) {                  //Use switch to call the corresponding function.
                    case 1:
                        System.out.println("These are top 10 tweets!");
                        topTweet.findTopTweets();
                        break;

                    case 2:
                        System.out.println("These are top 10 users!");
                        topUser.findTopUser();
                        break;

                    case 3:
                        System.out.println("Please input the keyword(only one word)");
                        sMatch.doMatch();
                        break;

                    case 4:
                        indexCreater.indexCreater();        //Firstly creating index is necessary.
                        searcher.search(sentence());        //Then search the sentence by full-text searching.
                        break;

                    default:
                        System.out.println("Invalid option");
                        break;
                }
            } catch (InputMismatchException e) {            //To avoid the non-number input.
                System.out.println("Invalid input! Please input again!");
            }
        }
    }
}

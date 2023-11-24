package assignment;

import java.util.List;

/**
 * An arraylist to store the loaded excel. It will be used for sorting top 10
 * users, top 10 tweets, string mtach and full- text match.
 * @author Kai-Yu Lu16; ID:1614649.
 */
public class userData {
    /**
     * user.
     *
     */
    public List<String[]> user;

    /**
     * Load date from the aimed excel file.
     *
     * @return the list
     * @throws Exception the exception
     * @see ExcelReader
     */
    public List<String[]> loadDate() throws Exception {
        ExcelReader reader = new ExcelReader("CSE210_CW_twitterDataset.xlsx"); //The address of the excel file.
        user = reader.readRows();
//        for (int i=0; i<user.size();i++){              //For testing if the excel is loaded.
//            for (int j=0; j<user.get(i).length;j++){
//                System.out.println(user.get(i)[j]);
//            }
//         System.out.println("---------------");
//    }
        return user;
    }
}

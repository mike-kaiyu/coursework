package assignment;

/**
 * The Class User.
 *
 * @author Kai-Yu Lu16; ID:1614649.
 */
public class User implements Comparable<User> {

    /**
     * The id.
     */
    private String id;

    /**
     * The user name.
     */
    private String userName;

    /**
     * The nick name.
     */
    private String nickName;

    /**
     * The followers.
     */
    private int followers;

    /**
     * Compare to is to compare the followers.
     *
     * @param o the o
     * @return the int
     */
    public int compareTo(User o) {
        if (this.getFollowers() >= o.getFollowers()) {
            return -1;
        } else {
            return 1;
        }
    }

    /**
     * To string.
     *
     * @return the string
     */
    public String toString() {
        return " ID: " + getID() + "====" + " User name: " + getUserName() + "====" + " Nick name:" + getNickName() + "====" + " Followers: " + getFollowers();
    }

    /**
     * Gets the id.
     *
     * @return the id
     */
    public String getID() {
        return id;
    }

    /**
     * Sets the id.
     *
     * @param id the new id
     */
    public void setID(String id) {
        this.id = id;
    }

    /**
     * Gets the followers.
     *
     * @return the followers
     */
    public int getFollowers() {
        return followers;
    }

    /**
     * Sets the followers.
     *
     * @param followers the new followers
     */
    public void setFollowers(int followers) {
        this.followers = followers;
    }

    /**
     * Gets the user name.
     *
     * @return the user name
     */
    public String getUserName() {
        return userName;
    }

    /**
     * Sets the user name.
     *
     * @param userName the new user name
     */
    public void setUserName(String userName) {
        this.userName = userName;
    }

    /**
     * Gets the nick name.
     *
     * @return the nick name
     */
    public String getNickName() {
        return nickName;
    }

    /**
     * Sets the nick name.
     *
     * @param nickName the new nick name
     */
    public void setNickName(String nickName) {
        this.nickName = nickName;
    }

    /**
     * Instantiates a new user.
     */
    public User() {
    }

    /**
     * Instantiates a new user.
     *
     * @param id the id of the tweet
     * @param userName the user name
     * @param nickName the nick name
     * @param followers the followers
     */
    public User(String id, String userName, String nickName, int followers) {
        this.id = id;
        this.userName = userName;
        this.nickName = nickName;
        this.followers = followers;
    }
}

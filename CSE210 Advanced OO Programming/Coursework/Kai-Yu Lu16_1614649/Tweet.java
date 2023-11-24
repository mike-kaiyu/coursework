package assignment;

/**
 * The Class Tweet is to generate tweet.
 *
 *
 */
public class Tweet implements Comparable<Tweet> {

    /**
     * The id.
     */
    private String id;

    /**
     * The date.
     */
    private String date;

    /**
     * The hour.
     */
    private String hour;

    /**
     * The user name.
     */
    private String userName;

    /**
     * The nick name.
     */
    private String nickName;

    /**
     * The tweet content.
     */
    private String tweetContent;

    /**
     * The Favs.
     */
    private int Favs;

    /**
     * The RTs.
     */
    private int RTs;

    /**
     * The latitude.
     */
    private String latitude;

    /**
     * The longitude.
     */
    private String longitude;

    /**
     * The followers.
     */
    private int followers;

    /**
     * The sum FR.
     */
    private int sumFR;

    /**
     * Compare to is to compare the sum of Favs and RTs.
     *
     * @param o the o
     * @return the int
     */
    @Override
    public int compareTo(Tweet o) {
        if (this.getSumFR() > o.getSumFR()) {
            return -1;
        } else if (this.getSumFR() < o.getSumFR()) {
            return 1;
        } else {
            return 0;
        }
    }

    /**
     * To string.
     *
     * @return the string
     */
    @Override
    public String toString() {
        return "ID: " + getID() + " == " + "Data: " + getDate() + " == " + "Hour: " + getHour() + " == " + "User Name: " + getUserName() + " == " + "Nich name: " + getNickName() + " == "
                + "Tweet Content: " + getTweetContent() + " == " + "Favs: " + getFavs() + " == " + "RTs:" + getRTs() + " == " + "Latitude: " + getLatitude() + " == " + "Longitude: " + getLongitude() + " == " + "Followers" + getFollowers() + " == " + "Favs + RTs:" + getSumFR();

    }

    /**
     * Gets the sum FR.
     *
     * @return the sum FR
     */
    public int getSumFR() {
        return sumFR;
    }

    /**
     * Sets the sum FR.
     *
     * @param Favs the favs
     * @param RTs the r ts
     */
    public void setSumFR(int Favs, int RTs) {
        this.sumFR = Favs + RTs;
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
     * Gets the favs.
     *
     * @return the favs
     */
    public int getFavs() {
        return Favs;
    }

    /**
     * Sets the favs.
     *
     * @param Favs the new favs
     */
    public void setFavs(int Favs) {
        this.Favs = Favs;
    }

    /**
     * Gets the r ts.
     *
     * @return the r ts
     */
    public int getRTs() {
        return RTs;
    }

    /**
     * Sets the r ts.
     *
     * @param RTs the new r ts
     */
    public void setRTs(int RTs) {
        this.RTs = RTs;
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
     * Gets the date.
     *
     * @return the date
     */
    public String getDate() {
        return date;
    }

    /**
     * Sets the date.
     *
     * @param date the new date
     */
    public void setDate(String date) {
        this.date = date;
    }

    /**
     * Gets the hour.
     *
     * @return the hour
     */
    public String getHour() {
        return hour;
    }

    /**
     * Sets the hour.
     *
     * @param hour the new hour
     */
    public void setHour(String hour) {
        this.hour = hour;
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
     * Sets the tweet content.
     *
     * @param tweetContent the new tweet content
     */
    public void setTweetContent(String tweetContent) {
        this.tweetContent = tweetContent;
    }

    /**
     * Gets the tweet content.
     *
     * @return the tweet content
     */
    public String getTweetContent() {
        return tweetContent;
    }

    /**
     * Sets the latitude.
     *
     * @param latitude the new latitude
     */
    public void setLatitude(String latitude) {
        this.latitude = latitude;
    }

    /**
     * Gets the latitude.
     *
     * @return the latitude
     */
    public String getLatitude() {
        return latitude;
    }

    /**
     * Sets the longitude.
     *
     * @param longitude the new longitude
     */
    public void setLongitude(String longitude) {
        this.longitude = longitude;
    }

    /**
     * Gets the longitude.
     *
     * @return the longitude
     */
    public String getLongitude() {
        return longitude;
    }

    /**
     * Instantiates a new tweet.
     */
    public Tweet() {
    }

    /**
     * Instantiates a new tweet.
     *
     * @param id the tweet ID.
     * @param date the tweet date.
     * @param hour hour.
     * @param userName the tweet user name.
     * @param nickName the tweet nick name.
     * @param tweetContent the tweet content.
     * @param Favs the tweet Favs.
     * @param RTs the tweet RTs.
     * @param latitude the tweet latitude.
     * @param longitude the tweet longitude.
     * @param followers the tweet followers.
     * @param sumFR the sum FR.
     */
    public Tweet(String id, String date, String hour, String userName, String nickName, String tweetContent, int Favs, int RTs, String latitude, String longitude, int followers, int sumFR) {
        this.id = id;
        this.date = date;
        this.hour = hour;
        this.userName = userName;
        this.nickName = nickName;
        this.tweetContent = tweetContent;
        this.Favs = Favs;
        this.RTs = RTs;
        this.latitude = latitude;
        this.longitude = longitude;
        this.followers = followers;
        this.sumFR = sumFR;
    }
}

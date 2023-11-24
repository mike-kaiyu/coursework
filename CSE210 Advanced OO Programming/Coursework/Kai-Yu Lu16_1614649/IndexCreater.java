package assignment;

import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.TextField;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;

/**
 * A class to create the index. It has the loaded data from class "userData".
 *
 * @author Kai-Yu Lu16; ID:1614649
 */
public class IndexCreater {

    /**
     * The user all.
     */
    List<String[]> userAll = new ArrayList<String[]>();//stored

    /**
     * Instantiates a new index creater.
     *
     * @param uData the u data
     * @throws Exception the exception
     */
    public IndexCreater(userData uData) throws Exception {
        userAll = uData.user; //have uData which is userDta. Then get the user
    }

    /**
     * Index creater.
     *
     * @throws Exception the exception
     */
    public void indexCreater() throws Exception {
        List<Document> documents = new ArrayList<>();
        StandardAnalyzer standardAnalyzer = new StandardAnalyzer();
        String path = System.getProperty("user.dir") + "/hello";
        Directory directory = FSDirectory.open(Paths.get(path));
        IndexWriterConfig config = new IndexWriterConfig(standardAnalyzer);
        //Create a writer
        IndexWriter writer = new IndexWriter(directory, config);

        for (int i = 1; i < userAll.size(); i++) {
            Document document = new Document();
            document.add(new TextField("content", makeString(userAll.get(i)), Field.Store.YES));
            documents.add(document);
        }
        writer.deleteAll();
        writer.addDocuments(documents);
        writer.commit();
        writer.close();
        System.out.println("Indexer created");
    }

    /**
     * Make string to have the desired searched parameters.
     *
     * @param table the table
     * @return the string
     */
    public String makeString(String[] table) {
        return table[5];
    }
}

package assignment;

import java.io.IOException;
import java.nio.file.Paths;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;

/**
 * A class to execute full text searching. 
 * It has the loaded data from class "userData".
 *
 * @author Kai-Yu Lu16; ID:1614649
 */
public class searcher {

    /**
     * Search.
     *
     * @param findingSentence the input sentence that want to be searched.
     * @throws IOException Signals that an I/O exception has occurred.
     * @throws ParseException the parse exception
     */
    public static void search(String findingSentence) throws IOException, ParseException {
        String path = System.getProperty("user.dir") + "/hello";     //The index is in a file called hello.
        Directory directory = FSDirectory.open(Paths.get(path));
        StandardAnalyzer standardAnalyzer = new StandardAnalyzer();
        IndexReader reader = DirectoryReader.open(directory);
        IndexSearcher searcher = new IndexSearcher(reader);
        QueryParser parser = new QueryParser("content", standardAnalyzer);
        Query query = parser.parse(findingSentence);
        TopDocs results = searcher.search(query, 6);   //6 is number of the desired prints.
        System.out.println(results.totalHits);
        for (ScoreDoc result : results.scoreDocs) {
            Document document = searcher.doc(result.doc);
            System.out.println(String.format(document.get("content")));
        }
    }
}

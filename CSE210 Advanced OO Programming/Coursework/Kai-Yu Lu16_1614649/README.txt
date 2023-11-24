==Description==
The objective of the coursework is to develop a practical application for data processing, 
analysis and content search based on the object-oriented principles from the CSE210 module. 
The programming will load the excel dataset whose file name is "CSE210_CW_twitterDataset.xlsx".

==Environment==
Any JAVA IDE is welcome.

==Execution==
When starting the program, you need to wait for few second because it is loading the data. 
After that, the interface for choosing will show up:
**Input 1 and press "ENTER", it will print the top 10 tweets.
**Input 2 and press "ENTER", it will print the top 10 users.
**Input 3 and press "ENTER", then you need to input the one desired key word, then the program wii
        find how many this key words the excel has, print out all of them and then show their locations in excel.
**Input 4 and press "ENTER",you need to input the desired sentence, then the program wii
        find how many this key words the excel has and print out some of them.
Other inputs are invalid.

==Library==
1. Apache POI (the Java API for Microsoft Documents) library. The API is available at: 
    https://poi.apache.org/download.html#POI-3.17 
2. Full text search engine based on the original Lucene API, only for limited amount of Twitter data. 
   Lucene can be downloaded at: https://lucene.apache.org/core/. 

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.InputMismatchException;
import static java.lang.Integer.parseInt;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;

import org.apache.poi.openxml4j.opc.OPCPackage;
import org.apache.poi.openxml4j.opc.PackageAccess;
import org.apache.poi.ss.util.CellReference;
import org.apache.poi.xssf.eventusermodel.ReadOnlySharedStringsTable;
import org.apache.poi.xssf.eventusermodel.XSSFReader;
import org.apache.poi.xssf.usermodel.XSSFRichTextString;

import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.TextField;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;

import java.io.IOException;
import java.nio.file.Paths;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;

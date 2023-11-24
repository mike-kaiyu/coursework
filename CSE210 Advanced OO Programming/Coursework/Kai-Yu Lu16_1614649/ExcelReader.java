package assignment;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;

import org.apache.poi.openxml4j.opc.OPCPackage;
import org.apache.poi.openxml4j.opc.PackageAccess;
import org.apache.poi.ss.util.CellReference;
import org.apache.poi.xssf.eventusermodel.ReadOnlySharedStringsTable;
import org.apache.poi.xssf.eventusermodel.XSSFReader;
import org.apache.poi.xssf.usermodel.XSSFRichTextString;

/**
 * The Class ExcelReader is to read the excel. The method is event model.
 *
 * @author Kai-Yu Lu16; ID:1614649
 */
public class ExcelReader {

    /**
     * The row num.
     */
    private int rowNum = 0;

    /**
     * The opc pkg.
     */
    private OPCPackage opcPkg;

    /**
     * The strings table.
     */
    private ReadOnlySharedStringsTable stringsTable;

    /**
     * The xml reader.
     */
    private XMLStreamReader xmlReader;

    /**
     * Instantiates a new excel reader.
     *
     * @param excelPath the excel path
     * @throws Exception the exception
     */
    public ExcelReader(String excelPath) throws Exception {
        opcPkg = OPCPackage.open(excelPath, PackageAccess.READ);
        this.stringsTable = new ReadOnlySharedStringsTable(opcPkg);

        XSSFReader xssfReader = new XSSFReader(opcPkg);
        XMLInputFactory factory = XMLInputFactory.newInstance();
        InputStream inputStream = xssfReader.getSheetsData().next();
        xmlReader = factory.createXMLStreamReader(inputStream);

        while (xmlReader.hasNext()) {
            xmlReader.next();
            if (xmlReader.isStartElement()) {
                if (xmlReader.getLocalName().equals("sheetData")) {
                    break;
                }
            }
        }
    }

    /**
     * Read rows.
     *
     * @return the list
     * @throws XMLStreamException the XML stream exception
     */
    public List<String[]> readRows() throws XMLStreamException {
        String elementName = "row";
        List<String[]> dataRows = new ArrayList<String[]>();
        while (xmlReader.hasNext()) {
            xmlReader.next();
            if (xmlReader.isStartElement()) {
                if (xmlReader.getLocalName().equals(elementName)) {
                    rowNum++;
                    dataRows.add(getDataRow());
                }
            }
        }
        return dataRows;
    }

    /**
     * Gets the data row.
     *
     * @return the data row
     * @throws XMLStreamException the XML stream exception
     */
    private String[] getDataRow() throws XMLStreamException {
        List<String> rowValues = new ArrayList<String>();
        while (xmlReader.hasNext()) {
            xmlReader.next();
            if (xmlReader.isStartElement()) {
                if (xmlReader.getLocalName().equals("c")) {
                    CellReference cellReference = new CellReference(xmlReader.getAttributeValue(null, "r"));
                    // Fill in the possible blank cells!
                    while (rowValues.size() < cellReference.getCol()) {
                        rowValues.add("");
                    }
                    String cellType = xmlReader.getAttributeValue(null, "t");
                    rowValues.add(getCellValue(cellType));
                }
            } else if (xmlReader.isEndElement() && xmlReader.getLocalName().equals("row")) {
                break;
            }
        }
        return rowValues.toArray(new String[rowValues.size()]);
    }

    /**
     * Gets the cell value.
     *
     * @param cellType the cell type
     * @return the cell value
     * @throws XMLStreamException the XML stream exception
     */
    private String getCellValue(String cellType) throws XMLStreamException {
        String value = ""; // by default
        while (xmlReader.hasNext()) {
            xmlReader.next();
            if (xmlReader.isStartElement()) {
                if (xmlReader.getLocalName().equals("v")) {
                    if (cellType != null && cellType.equals("s")) {
                        int idx = Integer.parseInt(xmlReader.getElementText());
                        return new XSSFRichTextString(stringsTable.getEntryAt(idx)).toString();
                    } else {
                        return xmlReader.getElementText();
                    }
                }
            } else if (xmlReader.isEndElement() && xmlReader.getLocalName().equals("c")) {
                break;
            }
        }
        return value;
    }
}

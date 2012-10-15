using System;
using System.Collections.Generic;
using System.Linq;
using SbtReports.Models;
using DocumentFormat.OpenXml.Packaging;
using DocumentFormat.OpenXml.Spreadsheet;
using DocumentFormat.OpenXml;

namespace Sbt.General
{
  public class Integrator
  {
    private const string fileName = @"C:\Users\Masha\report.xlsx";
    public static void GenerateReport(List<DataObject> objects)
    {
      SheetData data = new SheetData();

      //add column names to the first row  
      Row header = new Row();
      header.RowIndex = (UInt32)1;

      foreach (DataObject obj in objects)
      {
        Cell headerCell = createTextCell(objects.IndexOf(obj) + 1, 1, obj.Name);
        header.AppendChild(headerCell);
      }
      data.AppendChild(header);
      SpreadsheetDocument doc = CreateDoc(data);
      /*using (SpreadsheetDocument spreadsheet = SpreadsheetDocument.Open(fileName, true))
      {
        WorkbookPart workbook = spreadsheet.WorkbookPart;
        //create a reference to Sheet1  
        WorksheetPart worksheet = workbook.WorksheetParts.Last();
        
        
        ///loop through each data row  DataRow contentRow;
        for (int i = 0; i < table.Rows.Count; i++)
        {
          contentRow = table.Rows[i];
          data.AppendChild(createContentRow(contentRow, i + 2));
        }
       }  */          
    }
    private static string getColumnName(int columnIndex)
    {
      int dividend = columnIndex;
      string columnName = String.Empty;
      int modifier;

      while (dividend > 0)
      {
        modifier = (dividend - 1) % 26;
        columnName = Convert.ToChar(65 + modifier).ToString() + columnName;
        dividend = (int)((dividend - modifier) / 26);
      }
      return columnName;
    }
    private static Cell createTextCell(int columnIndex, int rowIndex, object cellValue)
    {
      Cell cell = new Cell();

      cell.DataType = CellValues.InlineString;
      cell.CellReference = getColumnName(columnIndex) + rowIndex;

      InlineString inlineString = new InlineString();
      Text t = new Text();

      t.Text = cellValue.ToString();
      inlineString.AppendChild(t);
      cell.AppendChild(inlineString);

      return cell;
    }
    /*private Row createContentRow(
    DataRow dataRow,
    int rowIndex)
    {
      Row row = new Row
      {
        RowIndex = (UInt32)rowIndex
      };

      for (int i = 0; i < dataRow.Table.Columns.Count; i++)
      {
        Cell dataCell = createTextCell(i + 1, rowIndex, dataRow[i]);
        row.AppendChild(dataCell);
      }
      return row;
    }*/
    private static SpreadsheetDocument CreateDoc(SheetData data)
    {
      using (SpreadsheetDocument doc = SpreadsheetDocument.Create(fileName, SpreadsheetDocumentType.Workbook))
      {
        doc.AddWorkbookPart();
        doc.WorkbookPart.Workbook = new Workbook();
        doc.WorkbookPart.Workbook.Save();
        doc.WorkbookPart.Workbook.Sheets = new Sheets();
        doc.WorkbookPart.Workbook.Save();
        Sheets sheets = doc.WorkbookPart.Workbook.GetFirstChild<Sheets>();

        // Add the worksheetpart
        WorksheetPart worksheetPart = doc.WorkbookPart.AddNewPart<WorksheetPart>();
        worksheetPart.Worksheet = new Worksheet(data);
        worksheetPart.Worksheet.Save();

        // Add the sheet and make relation to workbook
        Sheet sheet = new DocumentFormat.OpenXml.Spreadsheet.Sheet()
        {
          Id = doc.WorkbookPart.GetIdOfPart(worksheetPart),
          SheetId = (uint)(doc.WorkbookPart.Workbook.Sheets.Count() + 1),
          Name = "sheet"
        };
        sheets.Append(sheet);
        doc.WorkbookPart.Workbook.Save();
        return doc;
      }
    }
  }
}
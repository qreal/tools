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
    public static void GenerateReport(List<DataObject> objects)
    {
      const string fileName = @"C:\Users\Masha\report.xlsx";
      using (SpreadsheetDocument doc = SpreadsheetDocument.Create(fileName, SpreadsheetDocumentType.Workbook))
      {
        WorkbookPart workbook = doc.WorkbookPart;
        WorksheetPart worksheet = workbook.WorksheetParts.Last();
        SheetData data = worksheet.Worksheet.GetFirstChild<SheetData>();

        //add column names to the first row  
        Row header = new Row();
        header.RowIndex = (UInt32)1;

        Cell headerCell = createTextCell(1, 1, "header");
        header.AppendChild(headerCell);
        data.AppendChild(header);

        for (int i = 0; i < objects.Count; i++)
        {
          data.AppendChild(createContentRow(i + 2, objects[i].Name));
        }
      }
    }

    private static Cell createTextCell(int columnIndex, int rowIndex, string cellValue)
    {
      Cell cell = new Cell();

      cell.DataType = CellValues.InlineString;
      //cell.CellReference = getColumnName(columnIndex) + rowIndex;

      InlineString inlineString = new InlineString();
      Text t = new Text(cellValue);
      inlineString.AppendChild(t);
      cell.AppendChild(inlineString);

      return cell;
    }
    private static Row createContentRow(
      int rowIndex, string text)
    {
      Row row = new Row { RowIndex = (UInt32)rowIndex };

      Cell dataCell = createTextCell(1, rowIndex, text);
      row.AppendChild(dataCell);
      return row;
    }
  }
}
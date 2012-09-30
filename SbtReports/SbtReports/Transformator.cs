using System;
using System.Collections.Generic;
using System.Linq;
using SbtReports.Models;
using System.Data.SqlClient;

namespace Sbt.General
{
  public class Transformator
  {
    private static string query = @"SELECT * FROM Objects";
    private static string connectionString = @"Data Source=.\SQLExpress;Integrated Security=true;AttachDbFilename=|DataDirectory|Objects.mdf;User Instance=true;";
    public static List<DataObject> ExecuteQuery ()
    {
      List<DataObject> toReturn = new List<DataObject>();
      using (SqlConnection connection = new SqlConnection(connectionString))
      {
        connection.Open();
        SqlCommand command = new SqlCommand(query, connection);
        SqlDataReader sqlReader = command.ExecuteReader();
        while (sqlReader.Read())
        {
          DataObject obj = new DataObject();
          obj.Name = sqlReader.GetString(1);
          toReturn.Add(obj);
        }
      }
      return toReturn;
    }
  }
}
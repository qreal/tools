using System;
using System.Collections.Generic;
using System.Linq;
using SbtReports.Models;
using System.Data.SqlClient;
using SbtReports;

namespace Sbt.General
{
  public class Transformator
  {
    public static List<DataObject> ExecuteQuery ()
    {
      ObjectsEntities context = new ObjectsEntities();
      var query = from Objects in context.Objects
                  orderby Objects.ID
                  select Objects;
      List<DataObject> toReturn = new List<DataObject>();
      foreach (Objects obj in query)
      {
        DataObject dataObject = new DataObject();
        dataObject.ID = obj.ID;
        dataObject.Name = obj.Name;
      }
      return toReturn;
    }
  }
}
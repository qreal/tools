using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Entity;

namespace SbtReports.Models
{
    public class DataObject
    {
      public string Name { get; set; }
      public int ID { get; set; }
      private static int nextID = 0;
      public DataObject()
      {
        ID = nextID;
        nextID ++;
      }
    }

    //public class DataObjectDBContext : DbContext
    //{
    //    public DbSet<DataObject> DataObjects { get; set; }
    //}
}
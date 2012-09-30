using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using SbtReports.Models;
using Sbt.General;

namespace SbtReports.Controllers
{
  public class ObjectController : Controller
  {
    private static List<DataObject> dataObjects = new List<DataObject>();
    private static bool fillList = false;
    //
    // GET: /Object/

    public ViewResult Index()
    {
      if (!fillList)
      {
        dataObjects = Transformator.ExecuteQuery();
        fillList = true;
      }
      //Integrator.GenerateReport(dataObjects);
      return View(dataObjects);
    }

    //
    // GET: /Object/Details/5

    public ViewResult Details(int id)
    {
      DataObject returnObject = new DataObject();
      foreach (DataObject dataObject in dataObjects)
      {
        if (dataObject.ID == id)
        {
          returnObject = dataObject;
        }
      }
      return View(returnObject);
    }

    //
    // GET: /Object/Create

    public ActionResult Create()
    {
      return View();
    }

    //
    // POST: /Object/Create

    [HttpPost]
    public ActionResult Create(DataObject dataobject)
    {
      if (ModelState.IsValid)
      {
        dataObjects.Add(dataobject);
        return RedirectToAction("Index");
      }
      return View(dataobject);
    }

    //
    // GET: /Object/Edit/5

    public ActionResult Edit(int id)
    {
      DataObject returnObject = new DataObject();
      foreach (DataObject dataObject in dataObjects)
      {
        if (dataObject.ID == id)
        {
          returnObject = dataObject;
        }
      }
      return View(returnObject);
    }

    //
    // POST: /Object/Edit/5

    [HttpPost]
    public ActionResult Edit(DataObject dataobject)
    {
      if (ModelState.IsValid)
      {
        foreach (DataObject dataObject in dataObjects)
        {
          if (dataobject.ID == dataObject.ID)
          {
            dataObjects.Remove(dataObject);
            dataObjects.Add(dataobject);
            return RedirectToAction("Index");
          }
        }
      }
      return View(dataobject);
    }

    //
    // GET: /Object/Delete/5

    public ActionResult Delete(int id)
    {
      return Edit(id);
    }

    //
    // POST: /Object/Delete/5

    [HttpPost, ActionName("Delete")]
    public ActionResult DeleteConfirmed(int id)
    {
      foreach (DataObject dataObject in dataObjects)
      {
        if (dataObject.ID == id)
        {
          dataObjects.Remove(dataObject);
          return RedirectToAction("Index");
        }
      }
      return RedirectToAction("Index");
    }

    protected override void Dispose(bool disposing)
    {
      base.Dispose(disposing);
    }
  }
}
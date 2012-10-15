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
    //private static List<DataObject> dataObjects = new List<DataObject>();
    //
    // GET: /Object/

    public ViewResult Index()
    {
      /*if (!fillList)
      {
        dataObjects = Transformator.ExecuteQuery();
        fillList = true;
      }
      Integrator.GenerateReport(dataObjects);*/
      return View();
    }

    //
    // GET: /Object/Create

    public ActionResult Create()
    {
      return View();
    }

    //
    // POST: /Object/Create
    //TODO::generate reports here!
    [HttpPost]
    public ActionResult Create(DataObject dataobject)
    {
      if (ModelState.IsValid)
      {
        Transformator.ExecuteQuery();
        return RedirectToAction("Index");
      }
      return View(dataobject);
    }

    protected override void Dispose(bool disposing)
    {
      base.Dispose(disposing);
    }
  }
}
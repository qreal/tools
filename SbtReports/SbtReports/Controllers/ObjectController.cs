using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using SbtReports.Models;

namespace SbtReports.Controllers
{ 
    public class ObjectController : Controller
    {
        private DataObjectDBContext db = new DataObjectDBContext();

        //
        // GET: /Object/

        public ViewResult Index()
        {
            return View(db.DataObjects.ToList());
        }

        //
        // GET: /Object/Details/5

        public ViewResult Details(int id)
        {
            DataObject dataobject = db.DataObjects.Find(id);
            return View(dataobject);
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
                db.DataObjects.Add(dataobject);
                db.SaveChanges();
                return RedirectToAction("Index");  
            }

            return View(dataobject);
        }
        
        //
        // GET: /Object/Edit/5
 
        public ActionResult Edit(int id)
        {
            DataObject dataobject = db.DataObjects.Find(id);
            return View(dataobject);
        }

        //
        // POST: /Object/Edit/5

        [HttpPost]
        public ActionResult Edit(DataObject dataobject)
        {
            if (ModelState.IsValid)
            {
                db.Entry(dataobject).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(dataobject);
        }

        //
        // GET: /Object/Delete/5
 
        public ActionResult Delete(int id)
        {
            DataObject dataobject = db.DataObjects.Find(id);
            return View(dataobject);
        }

        //
        // POST: /Object/Delete/5

        [HttpPost, ActionName("Delete")]
        public ActionResult DeleteConfirmed(int id)
        {            
            DataObject dataobject = db.DataObjects.Find(id);
            db.DataObjects.Remove(dataobject);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
#include <gtkmm/main.h>
#include <gtkmm/table.h>
#include <gtkmm/window.h>

#include "SortedListLinked.h"
#include "CD.h"
using CSC2110::CD;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "ListBox.h"
#include <iostream>
using namespace std;

void addCDs(ListArray<CD>* list, ListBox<CD>* lb)
{
   ListArrayIterator<CD>* iter = list->iterator();

   //DO THIS
   //iterate over and add the cds to the list box (use lb->addItem)




   delete iter;
}

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   //DO THIS  
   //iterate over and delete the cds




   delete iter;
}

int main(int argc, char* argv[])
{
   Gtk::Main kit(argc, argv);  //this must be first
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   //DO THIS
   //create the sorted linked list (call it sorted_list)




   String title("CDs");
   ListBox<CD>* lstCDs = new ListBox<CD>(&title, sorted_list);
   addCDs(cds, lstCDs);

   Gtk::Window win;

   win.set_title("Music!");
   win.set_position(Gtk::WIN_POS_CENTER);

   //the size of the window
   int width = 640;
   int height = 520;

   win.set_size_request(width, height);
   win.set_resizable(false);  

   //10 rows, 1 column
   Gtk::Table tbl(10, 1, true);

   Gtk::Button btnRemove("Remove");

   //left attach, right attach, top attach, bottom attach
   tbl.attach(*lstCDs, 0, 1, 0, 9, Gtk::FILL | Gtk::EXPAND, Gtk::FILL | Gtk::EXPAND, 0, 0);
   tbl.attach(btnRemove, 0, 1, 9, 10, Gtk::FILL | Gtk::EXPAND, Gtk::FILL | Gtk::EXPAND, 0, 0);
   win.add(tbl);

   //a button must register with a method that has a void return type
   btnRemove.signal_clicked().connect(sigc::mem_fun(lstCDs, &ListBox<CD>::removeSelectedItem));

   win.show_all_children();
   Gtk::Main::run(win);

   deleteCDs(cds);
   delete cds;
   delete lstCDs;

   return 0;
}

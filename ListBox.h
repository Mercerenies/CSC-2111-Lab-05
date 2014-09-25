#ifndef LISTBOX_H
#define LISTBOX_H

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>

#include "SortedListLinked.h"
#include "ModelColumns.h"
#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

template < class T >
class ListBox : public Gtk::ScrolledWindow
{
   private:
      SortedListLinked<T>* sl;
      void fillListBox();
      void clearListBox();

   public:
      ListBox(String* title, SortedListLinked<T>* sorted_list);
      virtual ~ListBox();
      void addItem(T* item);
      int size();
      int getSelectedIndex();
      void removeSelectedItem();
      T* getSelectedItem();
      void on_selection_changed();

   protected:
      //Tree model columns:
      ModelColumns* mc;

      //Child widgets:
      Gtk::TreeView treeView;
      Glib::RefPtr<Gtk::ListStore> refTreeModel;

};

template < class T >
ListBox<T>::ListBox(String* str_title, SortedListLinked<T>* sorted_list) : Gtk::ScrolledWindow()
{
   mc = new ModelColumns();

   //Add the TreeView (inside a ScrolledWindow)
   add(treeView);

   //Only show the scrollbars when they are necessary:
   set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

   //Create the Tree model:
   refTreeModel = Gtk::ListStore::create(*mc);

   treeView.set_model(refTreeModel);
   const char* char_title = str_title->getText();
   treeView.append_column(char_title, *(mc->getKeyCol()));
   delete[] char_title;
   delete str_title;

   Gtk::CellRendererText* cell = (Gtk::CellRendererText*) treeView.get_column_cell_renderer(0);
   Pango::FontDescription verdana_12 = Pango::FontDescription("verdana 12"); 
   cell->property_font_desc() = verdana_12;

   Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = treeView.get_selection();
   refTreeSelection->signal_changed().connect(sigc::mem_fun(*this, &ListBox::on_selection_changed));

   sl = sorted_list;
}

template < class T >
void ListBox<T>::on_selection_changed()
{
   
}

template < class T >
ListBox<T>::~ListBox()
{
   delete mc;
   delete sl;
}

template < class T >
void ListBox<T>::addItem(T* item)
{
   sl->add(item);
   clearListBox();
   fillListBox();  
}

template < class T >
void ListBox<T>::removeSelectedItem()
{
   int index = getSelectedIndex();
   if (index > 0)
   {
      T* item = sl->get(index);
      sl->remove(item);
      clearListBox();
      fillListBox();
   }
}

template < class T >
void ListBox<T>::clearListBox()
{
   refTreeModel->clear();
}

template < class T >
void ListBox<T>::fillListBox()
{
   Gtk::TreeModelColumn<unsigned int> col_id = *(mc->getIDCol());
   Gtk::TreeModelColumn<Glib::ustring> col_key = *(mc->getKeyCol());

   int count = 1;
   ListLinkedIterator<T>* iter = sl->iterator();
   while (iter->hasNext())
   {
      T* item = iter->next();
      Gtk::TreeModel::Row row = *(refTreeModel->append());
      String* str = item->getKey();
      const char* text = str->getText();
      row[col_id] = count;  
      row[col_key] = text;
      count++;
   }
   delete iter;
}

template < class T >
int ListBox<T>::size()
{
   return sl->size();
}

//1-based, -1 if nothing is selected
template < class T >
int ListBox<T>::getSelectedIndex()
{
   Gtk::TreeModelColumn<unsigned int> col_id = *(mc->getIDCol());

   int index = -1;
   Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = treeView.get_selection();
   Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
   if(iter) //if anything is selected
   {
      Gtk::TreeModel::Row row = *iter;
      index = row[col_id];
   }
   return index;
}

template < class T >
T* ListBox<T>::getSelectedItem()
{
   T* item = NULL;
   int index = getSelectedIndex();

   if (index > 0)
   {
      item = sl->get(index);
   }
   return item;
}

#endif 

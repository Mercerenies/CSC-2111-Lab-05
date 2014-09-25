#include "ModelColumns.h"

ModelColumns::ModelColumns()
{
   col_id = new Gtk::TreeModelColumn<unsigned int>();
   col_key = new Gtk::TreeModelColumn<Glib::ustring>();
   add(*col_id);
   add(*col_key);
}

ModelColumns::~ModelColumns()
{
   delete col_id;
   delete col_key;
}

Gtk::TreeModelColumn<Glib::ustring>* ModelColumns::getKeyCol()
{
   return col_key;
}

Gtk::TreeModelColumn<unsigned int>* ModelColumns::getIDCol()
{
   return col_id;
}

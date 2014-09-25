#if !defined (MODELCOLUMNS_H)
#define MODELCOLUMNS_H

#include <gtkmm/treemodel.h>

class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
   public:
      ModelColumns();
      virtual ~ModelColumns();
      Gtk::TreeModelColumn<unsigned int>* getIDCol();
      Gtk::TreeModelColumn<Glib::ustring>* getKeyCol();

   private:
      Gtk::TreeModelColumn<unsigned int>* col_id;
      Gtk::TreeModelColumn<Glib::ustring>* col_key;
};

#endif

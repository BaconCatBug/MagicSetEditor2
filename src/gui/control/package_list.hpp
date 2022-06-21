//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/error.hpp>
#include <gui/control/gallery_list.hpp>
#include <data/filter.hpp>

DECLARE_POINTER_TYPE(Packaged);
DECLARE_POINTER_TYPE(PackageData);

// Information about a package
class PackageData : public IntrusivePtrVirtualBase, public IntrusiveFromThis<PackageData> {
public:
    PackageData() {};
    PackageData(const PackagedP& package, const Bitmap& image) : package(package), image(image) {};
    PackagedP package;
    Bitmap    image;

    bool contains(QuickFilterPart const& query) const;

    DECLARE_REFLECTION();
};

typedef intrusive_ptr<Filter<PackageData>> PackageDataFilterP;

// ----------------------------------------------------------------------------- : PackageList

/// A list of Packages of a specific type
class PackageList : public GalleryList {
public:
  PackageList(Window* parent, int id, int direction = wxHORIZONTAL, bool always_focused = true);
  
  /// Shows packages that match a specific patern, and that are of the given type
  template <typename T>
  void showData(const String& pattern = _("*")) {
    showData(pattern + _(".mse-") + T::typeNameStatic());
  }
  
  /// Shows packages that match a specific patern
  void showData(const String& pattern = _("*"));
  
  /// Clears this list
  void clear();
    
  /// Get the selected package, T should be the same type used for showData
  /** @pre hasSelection()
   *  Throws if the selection is not of type T */
  template <typename T>
  intrusive_ptr<T> getSelection(bool load_fully = true) const {
    intrusive_ptr<T> ret = dynamic_pointer_cast<T>(filtered_packages.at(getSelectionId())->package);
    if (!ret) throw InternalError(_("PackageList: Selected package has the wrong type"));
    if (load_fully) ret->loadFully();
    return ret;
  }
  
  /// Select the package with the given name, if it is not found, selects nothing
  void select(const String& name, bool send_event = true);
  
  /// Required width to show all items
  int requiredWidth() const;
  using GalleryList::column_count;

  void setFilter(const PackageDataFilterP& filter);
  
protected:
  /// Draw an item
  void drawItem(DC& dc, int x, int y, size_t item) override;
  /// Return how many items there are in the list
  size_t itemCount() const override;
  
private:
  void applyFilter();

  struct ComparePackagePosHint;
  /// The displayed packages
  vector<PackageData> packages;
  vector<PackageDataP> filtered_packages;
  PackageDataFilterP filter;
};

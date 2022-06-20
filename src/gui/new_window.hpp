//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <gui/control/filter_ctrl.hpp>

class PackageList;
class Game;
DECLARE_POINTER_TYPE(Set);
DECLARE_POINTER_TYPE(StyleSheet);

// ----------------------------------------------------------------------------- : NewSetWindow

/// Show the new set window, return the new set, if any
SetP new_set_window(Window* parent);

/// "Create a new set" dialog. First select game, then matching style.
class NewSetWindow : public wxDialog {
public:
  /// The newly created set, if any
  SetP set;
  
  NewSetWindow(Window* parent);
  
  // --------------------------------------------------- : data
private:
  DECLARE_EVENT_TABLE();

  // gui items
  PackageList*  game_list, *stylesheet_list;
  FilterCtrl* filter;
  String filter_value;
    
  // --------------------------------------------------- : events
  
  void onGameSelect  (wxCommandEvent&);
  
  void onStyleSheetSelect  (wxCommandEvent&);
  void onStyleSheetActivate(wxCommandEvent&);
  void onFilterUpdate(wxCommandEvent&);
    
  virtual void OnOK(wxCommandEvent&);
  
  void onUpdateUI(wxUpdateUIEvent&);
  void onIdle(wxIdleEvent&);
  
  // we are done, close the window
  void done();
};

// ----------------------------------------------------------------------------- : SelectStyleSheetWindow
// very similair, so in the same file

/// Show the select stylesheet window, return the selected stylesheet, if any
StyleSheetP select_stylesheet(const Game& game, const String& failed_name);

/// "Create a new set" dialog. First select game, then matching style.
class SelectStyleSheetWindow : public wxDialog {
public:
  /// The selected stylesheet, if any
  StyleSheetP stylesheet;
  
  SelectStyleSheetWindow(Window* parent, const Game& game, const String& failed_name);
  
  // --------------------------------------------------- : data
private:
  DECLARE_EVENT_TABLE();
  
  const Game& game;
  
  // gui items
  PackageList*  stylesheet_list;
    
  // --------------------------------------------------- : events
  
  void onStyleSheetSelect  (wxCommandEvent&);
  void onStyleSheetActivate(wxCommandEvent&);
    
  virtual void OnOK(wxCommandEvent&);
  
  void onUpdateUI(wxUpdateUIEvent&);
  void onIdle(wxIdleEvent&);
  
  // we are done, close the window
  void done();
};


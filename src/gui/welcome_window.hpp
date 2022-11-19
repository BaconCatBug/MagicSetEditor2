//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <gui/about_window.hpp> // for HoverButton

DECLARE_POINTER_TYPE(Set);

// ----------------------------------------------------------------------------- : WelcomeWindow

/// Welcome window, first window you see at startup
/** Shows the following choices for the user:
 *    - new set
 *    - open set
 *    - open last opened set
 *  in the future also:
 *    - new game, new style?
 */
class WelcomeWindow : public wxFrame {
public:
  WelcomeWindow();
  
private:
  DECLARE_EVENT_TABLE();
  
  // MSE logos
  Bitmap logo;
  #if USE_BETA_LOGO
  Bitmap logo2;
  #endif
  wxComboBox* language;
    
  void onPaint(wxPaintEvent&);
  void draw(DC& dc);
    
  void onOpenSet     (wxCommandEvent&);
  void onNewSet      (wxCommandEvent&);
  void onOpenLast    (wxCommandEvent&);
  void onCheckUpdates(wxCommandEvent&);
  void onApplyLanguage(wxCommandEvent&);
//  void onIdle    (wxIdleEvent& ev);
  
  /// Close the welcome window, and show the given set
  void close(const SetP& set);
};

// ----------------------------------------------------------------------------- : Hover button with label

/// An extended hover button, not only has base images, but also has two labels
class HoverButtonExt : public HoverButton {
public:
  HoverButtonExt(Window* parent, int id, const wxImage& icon_name, const String& label, const String& sub_label);
  
private:
  Bitmap icon;
  String label, sub_label;
  wxFont font_large, font_small;
  
protected:
  void draw(DC& dc) override;
};


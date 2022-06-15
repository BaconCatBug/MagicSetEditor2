//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#undef near
#include "hunspell.hxx"

DECLARE_POINTER_TYPE(SpellChecker);

#ifdef UNICODE
  typedef wxCharBuffer CharBuffer;
#else
  typedef const char* CharBuffer;
#endif

// ----------------------------------------------------------------------------- : Spell checker

/// A spelling checker for a particular language
class SpellChecker : public Hunspell, public IntrusivePtrBase<SpellChecker> {
public:
  SpellChecker(const char* aff_path, const char* dic_path);
  /// Get a SpellChecker object for the given language.
  /** Returns nullptr on error
   *  Note: This is not threadsafe yet */
  static SpellChecker* get(const String& language);
  /// Get a SpellChecker object for the given language and filename
  /** Returns nullptr on error
   *  Note: This is not threadsafe yet */
  static SpellChecker* get(const String& filename, const String& language);
  /// Destroy all cached SpellChecker objects
  static void destroyAll();

  /// Check the spelling of a single word
  bool spell(const String& word);

  /// Give spelling suggestions
  void suggest(const String& word, vector<String>& suggestions_out);

private:
  /// Convert between String and dictionary encoding
  wxCSConv encoding;
  bool convert_encoding(const String& word, CharBuffer& out);

  static map<String,SpellCheckerP> spellers; //< Cached checkers for each language
};


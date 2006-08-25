/*
 * This file is part of FBIde, an open-source (cross-platform) IDE for
 * FreeBasic compiler.
 * Copyright (C) 2005 - 2006 Albert Varaksin
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Contact e-mail: Albert Varaksin <vongodric@hotmail.com>
 * Program URL   : http://fbide.sourceforge.net
 */

#ifndef StyleInfo_H_INCLUDED
#define StyleInfo_H_INCLUDED

  #define STYLE_BOLD                1
  #define STYLE_ITALIC              (1 << 1)
  #define STYLE_UNDERLINED          (1 << 2)

  #define STYLE_DEFAULT_FONT_SIZE   10
  #define STYLE_DEFAULT_FG          _T("black")
  #define STYLE_DEFAULT_BG          _T("white")
  #define STYLE_DEFAULT_FONT        _T("Courier New")
  #define STYLE_DEFAULT_STYLE       0


  /**
   * This class is used to simplify manageing
   * style info in editors.
   * It provides easy way to manage
   * font, font style and text bg / fg colors.
   * Also ability to export/import data to/from string
   * for easy saving / loading or storing in the registry
   */
  class StyleInfo
  {
    private:
      bool isBold;
      bool isItalic;
      bool isUnderlined;
      wxColour m_fg;
      wxColour m_bg;
      size_t m_Size;
      wxString m_font;

    public:

      /**
       * Constructor for building StyleInfo
       * explicitly
       */
      StyleInfo (const wxColour & fg = STYLE_DEFAULT_FG, const wxColour & bg = STYLE_DEFAULT_BG,
                    int style = STYLE_DEFAULT_STYLE, size_t size = STYLE_DEFAULT_FONT_SIZE,
                    const wxString & font = STYLE_DEFAULT_FONT) : m_fg(fg), m_bg(bg), m_Size(size), m_font(font)
      {
        SetStyle (style);
      }

      /**
       * Constructing from a string containing data
       */
      StyleInfo (const wxString & data) { Set (data); }

      /**
       * From another styleinfo object
       */
      StyleInfo (const StyleInfo & data) { Set (data); }

      /**
       * Assignment operators
       */
      void operator = (const StyleInfo & data) { Set (data); }
      void operator = (const wxString & data) { Set (data); }

      /**
       * Set data
       */
      void Set (const StyleInfo & data)
      {
        isBold = data.isBold;
        isItalic = data.isItalic;
        isUnderlined = data.isUnderlined;
        m_Size = data.m_Size;
        m_fg = data.m_fg;
        m_bg = data.m_bg;
        m_font = data.m_font;
      }
      void Set (wxString data);

      /**
       * Get data as string
       */
      wxString GetAsString () const;


      /**
       * == operator
       */
      bool operator == (const StyleInfo & data) const
      {
        return isBold == data.isBold && isItalic == data.isItalic && isUnderlined == data.isUnderlined &&
               m_Size == data.m_Size && m_fg == data.m_fg && m_bg == data.m_bg && m_font == data.m_font;
      }

      /**
       * != operator
       */
      bool operator != (const StyleInfo & data) const
      {
        return !(*this == data);
      }

      /**
       * Set font style
       */
      void SetStyle (int style)
      {
        isBold = style & STYLE_BOLD;
        isItalic = style & STYLE_ITALIC;
        isUnderlined = style & STYLE_UNDERLINED;
      }

      /**
       * Get font styles
       */
      int GetStyle () const
      {
        int ret = 0;
        if (isBold) ret |= STYLE_BOLD;
        if (isItalic) ret |= STYLE_ITALIC;
        if (isUnderlined) ret |= STYLE_UNDERLINED;
        return ret;
      }

      /**
       * Individual setters / getters
       */
      void SetBold (bool bold) { isBold = bold; }
      bool IsBold () const { return isBold; }

      void SetItalic (bool italic) { isItalic = italic; }
      bool IsItalic () const { return isItalic; }

      void SetUnderlined (bool underlined) { isUnderlined = underlined; }
      bool IsUnderlined () const { return isUnderlined; }

      void SetSize (size_t size) { m_Size = size; }
      size_t GetSize () const { return m_Size; }

      void SetFG (const wxColour & fg) { m_fg = fg; }
      wxColour GetFG () const { return m_fg; }

      void SetBG (const wxColour & bg) { m_bg = bg; }
      wxColour GetBG () const { return m_bg; }

      void SetFont (const wxString & font) { m_font = font; }
      wxString GetFont () const { return m_font; }
  };

#endif // StyleInfo_H_INCLUDED

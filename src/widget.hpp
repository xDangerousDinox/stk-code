//
//  SuperTuxKart - a fun racing game with go-kart
//  This code originally from Neverball copyright (C) 2003 Robert Kooima
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

/* This file should only be used directly by the widget manager. Also, all
 * the coordinates in the widget.* and widget_manager.* are based on OpenGL,
 * which means that the 0 in the Y-axis is in the bottom, not the top.
 */

#ifndef HEADER_WIDGET_H
#define HEADER_WIDGET_H

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#else
#  ifdef WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <windows.h>
#  endif
#  include <GL/gl.h>
#endif

#include <string>
#include "gui/font.hpp"

enum WidgetFontSize { WGT_FNT_SML = 18, WGT_FNT_MED = 24, WGT_FNT_LRG = 30};

enum WidgetArea //One of the uses of this, is for rounded corners
{
    WGT_AREA_NONE = 0,
    WGT_AREA_NW = 1, WGT_AREA_SW = 2, WGT_AREA_NE = 4, WGT_AREA_SE = 8,
    WGT_AREA_LFT = (WGT_AREA_NW  | WGT_AREA_SW),
    WGT_AREA_RGT = (WGT_AREA_NE  | WGT_AREA_SE),
    WGT_AREA_TOP = (WGT_AREA_NW  | WGT_AREA_NE),
    WGT_AREA_BOT = (WGT_AREA_SW  | WGT_AREA_SE),
    WGT_AREA_ALL = (WGT_AREA_TOP | WGT_AREA_BOT)
};

//The lowest scroll values here must be bigger or lower than
//Widget::MAX_SCROLL
enum WidgetScrollPos
{
    //For the X axis
    WGT_SCROLL_START_LEFT = 2000001,
    WGT_SCROLL_START_RIGHT = 2000002,
    WGT_SCROLL_END_LEFT = -2000001,
    WGT_SCROLL_END_RIGHT = -2000002,
    //For the Y axis
    WGT_SCROLL_START_TOP = 1000001,
    WGT_SCROLL_START_BOTTOM = 1000002,
    WGT_SCROLL_END_TOP = -1000001,
    WGT_SCROLL_END_BOTTOM = -1000002,
    //Works for both axis
    WGT_SCROLL_CENTER = 3000000
};

//I suggest that you do not use the white or light colors for the rects in
//most cases, because they don't have lighter versions that can be used to
//highlight those rects and then revert them, for example, when you select a
//widget. For textures, you should use WGT_WHITE usually, thought you can get
//nice effects by using other colors.
extern const GLfloat WGT_WHITE  [4];
extern const GLfloat WGT_GRAY  [4];
extern const GLfloat WGT_BLACK  [4];
extern const GLfloat WGT_YELLOW [4];
extern const GLfloat WGT_RED    [4];
extern const GLfloat WGT_GREEN  [4];
extern const GLfloat WGT_BLUE   [4];
extern const GLfloat WGT_TRANS_WHITE  [4];
extern const GLfloat WGT_TRANS_GRAY   [4];
extern const GLfloat WGT_TRANS_BLACK  [4];
extern const GLfloat WGT_TRANS_YELLOW [4];
extern const GLfloat WGT_TRANS_RED    [4];
extern const GLfloat WGT_TRANS_GREEN  [4];
extern const GLfloat WGT_TRANS_BLUE   [4];

extern const GLfloat WGT_LIGHT_GRAY   [4];
extern const GLfloat WGT_LIGHT_BLACK  [4];
extern const GLfloat WGT_LIGHT_YELLOW [4];
extern const GLfloat WGT_LIGHT_RED    [4];
extern const GLfloat WGT_LIGHT_GREEN  [4];
extern const GLfloat WGT_LIGHT_BLUE   [4];
extern const GLfloat WGT_LIGHT_TRANS_GRAY   [4];
extern const GLfloat WGT_LIGHT_TRANS_BLACK  [4];
extern const GLfloat WGT_LIGHT_TRANS_YELLOW [4];
extern const GLfloat WGT_LIGHT_TRANS_RED    [4];
extern const GLfloat WGT_LIGHT_TRANS_GREEN  [4];
extern const GLfloat WGT_LIGHT_TRANS_BLUE   [4];


class Widget
{
    //The only class that can access the Widget class is WidgetManager;
    //they are meant to always be used together, and the widgets should only
    //be used through the WidgetManager class.
    friend class WidgetManager;

    /* Basic widget properties that will always be used. */
    int  m_x, m_y;
    int  m_width, m_height;

    /* On/off features, these are not dependant on the delta time and are not
     * animated. They are off by default. */
    bool m_enable_rect;
    GLuint  m_rect_list; //A display list number that draws the rectangle with
                      //possibly rounded corners.
    const GLfloat *m_rect_color; //This const cannot change the value it points to, but it
                                 //can change where it points to.
    WidgetArea m_round_corners;

    bool m_enable_texture;
    GLuint m_texture;

    bool m_enable_text;
    std::string m_text;
    WidgetFontSize m_text_size;


    static const int MAX_SCROLL;
    bool m_enable_scroll;
    float m_scroll_pos_x;
    float m_scroll_pos_y;
    float m_scroll_speed_x;
    float m_scroll_speed_y;

    /* Delta time dependant features, these deactivate after a certain time,
     * and are dependant on the delta time. They have animations. */
    static const float MAX_TEXT_SCALE;
    static const float MIN_TEXT_SCALE;
    float m_text_scale; //Used for the pulse effect

/*public:*/
    Widget
    (
        const int X_,
        const int Y_,
        const int WIDTH_,
        const int HEIGHT_
    );
    ~Widget();

    void update(const float DELTA);

/*    int get_x_pos() const { return m_x; }
    int get_y_pos() const { return m_y; }
    int get_width() const { return m_width; }
    int get_height() const { return m_height; }

    void set_x_pos( const int X ) { m_x = X; }
    void set_y_pos( const int Y ) { m_y = Y; }
    void set_width( const int WIDTH ) { m_width = WIDTH; }
    void set_height( const int HEIGHT ) { m_height = HEIGHT; }*/
    void resize_to_text(); //This checks if the widget is smaller than the
                           //text, and if so, changes the width and height.
    bool create_rect(int radius);

    /* Switch features functions. */
/*    void enable_rect() {m_enable_rect = true;}
    void disable_rect() {m_enable_rect = false;}*/
//    void toggle_rect() {m_enable_rect = m_enable_rect ? false : true;}
/*    void set_rect_color(const GLfloat *COLOR) {m_rect_color = COLOR;}
    const GLfloat* get_rect_color() const {return m_rect_color;}*/

/*    void enable_texture() {m_enable_texture = true;}
    void disable_texture() {m_enable_texture = false;}*/
//    void toggle_texture() {m_enable_texture = m_enable_texture ? false : true;}
/*    void set_texture(const int TEXTURE) {m_texture = TEXTURE;}
    int get_texture () const {return m_texture;}*/

/*    void enable_text() {m_enable_text = true;}
    void disable_text() {m_enable_text = false;}
    void toggle_text() {m_enable_text = m_enable_text ? false : true;}
    void set_text(const char* TEXT) {m_text.assign(TEXT);}
    void set_text(const std::string TEXT) {m_text.assign(TEXT);}
    std::string get_text() const {return m_text;}
    void set_text_size( const WidgetFontSize SIZE ) { m_text_size = SIZE; }
    WidgetFontSize get_text_size() { return m_text_size; }*/

    /* Time limited features' functions. */
    void pulse() {m_text_scale = MAX_TEXT_SCALE;}

    /* Convenience functions. */
    void lighten_color();
    void darken_color();

};

#endif

/* EOF */

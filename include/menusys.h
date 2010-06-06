#ifndef __MENUSYS_H
#define __MENUSYS_H

#include "include/texcache.h"

/// Forward decls.
struct menu_item_t;
struct menu_list_t;

/// a single submenu item
struct submenu_item_t {
	/// Icon used for rendering of this item
	int icon_id;
	
	/// item description
	char *text;
	
	/// item description in localised form (used if value is not negative)
	int text_id;
	
	/// item id
	int id;
	
	/// do we have a pixmap at all? 0 no, 1 yes, 2 not sure yet
	int pixmap_state[3];
	
	/// pointers to cache entries (used by cache code)
	cache_entry_t *cache_entry_ref[3];
};

struct submenu_list_t {
	struct submenu_item_t item;
	
	struct submenu_list_t *prev, *next;
};

struct menu_hint_item_t {
	int icon_id;
	int text_id;
	
	struct menu_hint_item_t *next;
};

/// a single menu item. Linked list impl (for the ease of rendering)
struct menu_item_t {
	/// Icon used for rendering of this item
	int icon_id;
	
	/// item description
	char *text;
	
	/// item description in localised form (used if value is not negative)
	int text_id;
	
	void *userdata;
	
	/// submenu, selection and page start (only used in static mode)
	struct submenu_list_t *submenu, *current, *pagestart;
	
	/// execute a menu/submenu item (id is the submenu id as specified in AppendSubMenu)
	void (*execute)(struct menu_item_t *self, int id);
	
	void (*refresh)(struct menu_item_t *self, short forceRefresh);
	
	/// Alternate execution (can be used for item configuration for example)
	void (*altExecute)(struct menu_item_t *self, int id);
	
	/// hint list
	struct menu_hint_item_t *hints;
};

struct menu_list_t {
	struct menu_item_t *item;
	
	struct menu_list_t *prev, *next;
};

void menuInit();
void menuEnd();

void menuAppendItem(struct menu_item_t* item);

struct submenu_list_t* submenuAppendItem(struct submenu_list_t** submenu, int icon_id, char *text, int id, int text_id);
void submenuRemoveItem(struct submenu_list_t** submenu, int id);
void submenuDestroy(struct submenu_list_t** submenu);
void submenuSort(struct submenu_list_t** submenu);

/// Get the text of the item (considers localised version of the string)
char *submenuItemGetText(struct submenu_item_t* it);

/// callback from the defered pixmap load ended operation
void submenuPixmapLoaded(icon_cache_t* cache, void *centry, int result);

void menuDrawStatic();

void menuNextH();
void menuPrevH();
void menuNextV();
void menuPrevV();
struct menu_item_t* menuGetCurrent();
GSTEXTURE* menuGetCurrentArt();
void menuItemExecute();
void menuItemAltExecute();

// Sets the selected item if it is found in the menu list
void menuSetSelectedItem(struct menu_item_t* item);
void submenuRefresh(short forceRefresh);

void menuSetInactiveFrames(unsigned int frames);

void menuAddHint(struct menu_item_t *menu, int text_id, int icon_id);
void menuRemoveHints(struct menu_item_t *menu);

#endif
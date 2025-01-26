#ifndef MENU_HPP
#define MENU_HPP

#include <LiquidCrystal_I2C.h>

// Funktionszeiger für Menüaktionen
typedef void (*MenuAction)(); 

// Struktur für Menüeinträge
struct MenuItem {
  String name;         // Name des Menüeintrags
  MenuAction action;   // Aktion des Menüeintrags
};

// Menüklasse
class Menu {
public:
  // Konstruktor
  Menu() : items(nullptr), totalItems(0), cursorPosition(0), scrollOffset(0), lcdRows(0), lcd(nullptr) {}

  // Setup-Methode für das Menü
  void begin(MenuItem *items, int itemCount, int lcdRows, LiquidCrystal_I2C &lcdRef) {
    this->items = items;
    this->totalItems = itemCount;
    this->lcdRows = lcdRows;
    this->lcd = &lcdRef;  // LCD-Referenz speichern
    display();  // Menü anzeigen
  }

  // Menü anzeigen
  void display() {
    lcd->clear();
    for (int i = 0; i < lcdRows; i++) {
      int itemIndex = i + scrollOffset;
      if (itemIndex < totalItems) {
        lcd->setCursor(0, i);
        if (i == cursorPosition) {
          lcd->print("> ");  // Cursor anzeigen
        } else {
          lcd->print("  ");  // Kein Cursor
        }
        lcd->print(items[itemIndex].name);  // Menüeintrag anzeigen
      }
    }
  }

  // Navigation durch das Menü
  void navigate(int direction) {
    int newPosition = cursorPosition + direction;
    if (newPosition >= 0 && newPosition < lcdRows) {
      cursorPosition = newPosition;  // Cursor verschieben
    } else if (newPosition < 0 && scrollOffset > 0) {
      scrollOffset--;  // Nach oben scrollen
    } else if (newPosition >= lcdRows && scrollOffset + lcdRows < totalItems) {
      scrollOffset++;  // Nach unten scrollen
    }
    display();  // Menü nach Navigation aktualisieren
  }

  // Menüpunkt auswählen
  void select() {
    int selectedIndex = scrollOffset + cursorPosition;
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Gewaehlt:");
    lcd->setCursor(0, 1);
    lcd->print(items[selectedIndex].name);

    // Falls eine Aktion definiert ist, führe sie aus
    if (items[selectedIndex].action) {
      items[selectedIndex].action();
    }

    delay(500);
    display();  // Menü nach Auswahl aktualisieren
  }

private:
  MenuItem *items;        // Menüeinträge
  int totalItems;         // Gesamtanzahl der Menüeinträge
  int cursorPosition;     // Position des Cursors
  int scrollOffset;       // Scroll-Offset
  int lcdRows;            // Anzahl der Zeilen des LCDs
  LiquidCrystal_I2C *lcd; // Zeiger auf das LCD-Objekt
};

#endif

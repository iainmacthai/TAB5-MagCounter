
#include <M5Unified.h>
#include <M5GFX.h>

#include "NotoSansBold15.h"
#include "tinyFont.h"
#include "smallFont.h"
#include "midleFont.h"
#include "bigFont.h"
#include "font18.h"

// Button dimensions (same as clear button)
const int BUTTON_WIDTH = 180;
const int BUTTON_HEIGHT = 70;
const int BUTTON_RADIUS = 6;

// Button positions - evenly spaced near top middle
const int BUTTON_Y = 18;
const int BUTTON_SPACING = 40; // Space between buttons
const int TOTAL_BUTTONS_WIDTH = (3 * BUTTON_WIDTH) + (2 * BUTTON_SPACING);
const int BUTTON_START_X = (1280 - TOTAL_BUTTONS_WIDTH) / 2; // Center the group

// Button coordinates
const int BUTTON1_X = BUTTON_START_X;
const int BUTTON2_X = BUTTON_START_X + BUTTON_WIDTH + BUTTON_SPACING;
const int BUTTON3_X = BUTTON_START_X + 2*(BUTTON_WIDTH + BUTTON_SPACING);

// Button colors
const unsigned short BUTTON1_COLOR = 0x322A;  // Blue-ish
const unsigned short BUTTON2_COLOR = 0x59A1;  // Green-ish  
const unsigned short BUTTON3_COLOR = 0x11C8;  // Purple-ish
const unsigned short BACKGROUND_COLOR = 0x10E4;

bool deb = 0; // Debounce touch input

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Display.setRotation(3);
    M5.Display.fillScreen(BACKGROUND_COLOR);
    
    // Set display brightness
    M5.Display.setBrightness(30);

    // Set initial volume (0-255
    M5.Speaker.setVolume(128);

    // Initialize synth
    Serial.begin(115200);
    Serial.println("Simple UI with Three Buttons");
        
    // Draw the three buttons
    drawButtons();
    
    // Add title
    M5.Display.loadFont(midleFont); // Use middleFont from your original includes
    M5.Display.setTextColor(WHITE, BACKGROUND_COLOR);
    M5.Display.setTextDatum(middle_center);
    M5.Display.drawString("SIMPLE CONTROL PANEL", 640, 120);
    M5.Display.unloadFont();

}

void drawButtons() {
    // Load a larger font
    M5.Display.loadFont(bigFont); // Use bigFont from your original includes
    
    // Button 1 - Count Reset
    M5.Display.fillRoundRect(BUTTON1_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_RADIUS, BUTTON1_COLOR);
    M5.Display.setTextColor(WHITE, BUTTON1_COLOR);
    M5.Display.setTextDatum(middle_center);
    M5.Display.drawString("BUTTON 1", BUTTON1_X + BUTTON_WIDTH/2, BUTTON_Y + BUTTON_HEIGHT/2);
    
    // Button 2 - Spare 1
    M5.Display.fillRoundRect(BUTTON2_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_RADIUS, BUTTON2_COLOR);
    M5.Display.setTextColor(WHITE, BUTTON2_COLOR);
    M5.Display.drawString("BUTTON 2", BUTTON2_X + BUTTON_WIDTH/2, BUTTON_Y + BUTTON_HEIGHT/2);
    
    // Button 3 - Spare 2
    M5.Display.fillRoundRect(BUTTON3_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_RADIUS, BUTTON3_COLOR);
    M5.Display.setTextColor(WHITE, BUTTON3_COLOR);
    M5.Display.drawString("BUTTON 3", BUTTON3_X + BUTTON_WIDTH/2, BUTTON_Y + BUTTON_HEIGHT/2);
    
    // Unload font to free memory
    M5.Display.unloadFont();
}

void loop() {
    M5.update();
    auto touchDetail = M5.Touch.getDetail();

    if (touchDetail.isPressed()) {
        // Button 1 - Count Reset
        if (touchDetail.x > BUTTON1_X && touchDetail.x < BUTTON1_X + BUTTON_WIDTH && 
            touchDetail.y > BUTTON_Y && touchDetail.y < BUTTON_Y + BUTTON_HEIGHT) {
            if (deb == 0) {
                deb = 1;
                Serial.println("Count Reset pressed");
                // Add your Count Reset functionality here
                M5.Speaker.tone(3000, 50);
            }
        }
        
        // Button 2 - Spare 1
        else if (touchDetail.x > BUTTON2_X && touchDetail.x < BUTTON2_X + BUTTON_WIDTH && 
                 touchDetail.y > BUTTON_Y && touchDetail.y < BUTTON_Y + BUTTON_HEIGHT) {
            if (deb == 0) {
                deb = 1;
                Serial.println("Spare 1 pressed");
                // Add your Spare 1 functionality here
                M5.Speaker.tone(3000, 50);
            }
        }
        
        // Button 3 - Spare 2
        else if (touchDetail.x > BUTTON3_X && touchDetail.x < BUTTON3_X + BUTTON_WIDTH && 
                 touchDetail.y > BUTTON_Y && touchDetail.y < BUTTON_Y + BUTTON_HEIGHT) {
            if (deb == 0) {
                deb = 1;
                Serial.println("Spare 2 pressed");
                // Add your Spare 2 functionality here
                M5.Speaker.tone(3000, 50);
            }
        }
    } else {
        deb = 0;
    }
}
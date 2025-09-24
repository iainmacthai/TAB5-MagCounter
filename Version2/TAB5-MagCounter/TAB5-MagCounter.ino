#include <M5Unified.h>
#include <M5GFX.h>

#include "NotoSansBold15.h"
#include "tinyFont.h"
#include "smallFont.h"
#include "middleFont.h"
#include "bigFont.h"
#include "font18.h"

// Button dimensions 
const int BUTTON_WIDTH = 220;
const int BUTTON_HEIGHT = 80;
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

// Brightness control buttons
const int BRIGHT_BUTTON_WIDTH = 80;
const int BRIGHT_BUTTON_HEIGHT = 80;
const int BRIGHT_BUTTON_SPACING = 20;
const int BRIGHT_GROUP_X = 1280 - (2 * BRIGHT_BUTTON_WIDTH + BRIGHT_BUTTON_SPACING) - 40; // 40px from right edge
const int BRIGHT_GROUP_Y = 720 - BRIGHT_BUTTON_HEIGHT - 40; // 40px from bottom

const int BRIGHT_MINUS_X = BRIGHT_GROUP_X;
const int BRIGHT_PLUS_X = BRIGHT_GROUP_X + BRIGHT_BUTTON_WIDTH + BRIGHT_BUTTON_SPACING;

// Button colors
const unsigned short BUTTON1_COLOR = 0xb9f2;  // Pink-ish
const unsigned short BUTTON2_COLOR = 0xb9f2;  // Pink-ish  
const unsigned short BUTTON3_COLOR = 0xb9f2;  // Pink-ish
const unsigned short BRIGHT_BUTTON_COLOR = 0xb9f2; // 0xb9f2;  // Pink-ish
const unsigned short BACKGROUND_COLOR = 0x10E4;

int brightness = 125; // Default brightness (125/255)
bool deb = 0; // Debounce touch input

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Display.setRotation(3);
    M5.Display.fillScreen(BACKGROUND_COLOR);
    
    // Set display brightness to default
    M5.Display.setBrightness(brightness);

    // Set initial volume (0-255)
    M5.Speaker.setVolume(128);

    // Initialize synth
    Serial.begin(115200);
    Serial.println("Simple UI with Three Buttons");
        
    // Draw all UI elements
    drawButtons();
    drawBrightnessControls();
    
    // Add title
    M5.Display.loadFont(middleFont);
    M5.Display.setTextColor(WHITE, BACKGROUND_COLOR);
    M5.Display.setTextDatum(middle_center);
    M5.Display.drawString("SIMPLE CONTROL PANEL", 640, 120);
    M5.Display.unloadFont();
}

void drawButtons() {
    // Load a larger font
    M5.Display.loadFont(bigFont);
    
    // Button 1 - 
    M5.Display.fillRoundRect(BUTTON1_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_RADIUS, BUTTON1_COLOR);
    M5.Display.setTextColor(WHITE, BUTTON1_COLOR);
    M5.Display.setTextDatum(middle_center);
    M5.Display.drawString("BUTTON 1", BUTTON1_X + BUTTON_WIDTH/2, BUTTON_Y + BUTTON_HEIGHT/2);
    
    // Button 2 - 
    M5.Display.fillRoundRect(BUTTON2_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_RADIUS, BUTTON2_COLOR);
    M5.Display.setTextColor(WHITE, BUTTON2_COLOR);
    M5.Display.drawString("BUTTON 2", BUTTON2_X + BUTTON_WIDTH/2, BUTTON_Y + BUTTON_HEIGHT/2);
    
    // Button 3 - 
    M5.Display.fillRoundRect(BUTTON3_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_RADIUS, BUTTON3_COLOR);
    M5.Display.setTextColor(WHITE, BUTTON3_COLOR);
    M5.Display.drawString("BUTTON 3", BUTTON3_X + BUTTON_WIDTH/2, BUTTON_Y + BUTTON_HEIGHT/2);
    
    // Unload font to free memory
    M5.Display.unloadFont();
}

void drawBrightnessControls() {
    // Draw brightness title - MOVED HIGHER UP
    M5.Display.loadFont(middleFont);
    M5.Display.setTextColor(WHITE, BACKGROUND_COLOR);
    M5.Display.setTextDatum(middle_center);
    int titleX = BRIGHT_GROUP_X + (2 * BRIGHT_BUTTON_WIDTH + BRIGHT_BUTTON_SPACING) / 2;
    int titleY = BRIGHT_GROUP_Y - 50;  // Changed from -30 to -50 (moved up by 30 pixels)
    M5.Display.drawString("Brightness", titleX, titleY);
    M5.Display.unloadFont();
    
    // Draw brightness value - MOVED HIGHER UP
    M5.Display.loadFont(smallFont);
    M5.Display.drawString(String(brightness), titleX, titleY + 25);  // Still relative to titleY
    M5.Display.unloadFont();
    
    // Draw brightness buttons with big font
    M5.Display.loadFont(bigFont);
    
    // Minus button
    M5.Display.fillRoundRect(BRIGHT_MINUS_X, BRIGHT_GROUP_Y, BRIGHT_BUTTON_WIDTH, BRIGHT_BUTTON_HEIGHT, BUTTON_RADIUS, BRIGHT_BUTTON_COLOR);
    M5.Display.setTextColor(WHITE, BRIGHT_BUTTON_COLOR);
    M5.Display.setTextDatum(middle_center);
    M5.Display.drawString("-", BRIGHT_MINUS_X + BRIGHT_BUTTON_WIDTH/2, BRIGHT_GROUP_Y + BRIGHT_BUTTON_HEIGHT/2);
    
    // Plus button
    M5.Display.fillRoundRect(BRIGHT_PLUS_X, BRIGHT_GROUP_Y, BRIGHT_BUTTON_WIDTH, BRIGHT_BUTTON_HEIGHT, BUTTON_RADIUS, BRIGHT_BUTTON_COLOR);
    M5.Display.setTextColor(WHITE, BRIGHT_BUTTON_COLOR);
    M5.Display.drawString("+", BRIGHT_PLUS_X + BRIGHT_BUTTON_WIDTH/2, BRIGHT_GROUP_Y + BRIGHT_BUTTON_HEIGHT/2);
    
    M5.Display.unloadFont();
}

void updateBrightnessDisplay() {
    // Clear the area where brightness value is displayed
    int titleX = BRIGHT_GROUP_X + (2 * BRIGHT_BUTTON_WIDTH + BRIGHT_BUTTON_SPACING) / 2;
    int titleY = BRIGHT_GROUP_Y - 60;  // Match the change made above
    
    M5.Display.loadFont(smallFont);
    M5.Display.setTextColor(WHITE, BACKGROUND_COLOR);
    M5.Display.setTextDatum(middle_center);
    
    // Clear previous value by drawing a background-colored rectangle
    M5.Display.fillRect(titleX - 30, titleY + 15, 60, 20, BACKGROUND_COLOR);
    
    // Draw new brightness value
    M5.Display.drawString(String(brightness), titleX, titleY + 25);
    M5.Display.unloadFont();
}

void loop() {
    M5.update();
    auto touchDetail = M5.Touch.getDetail();

    if (touchDetail.isPressed()) {
        // Button 1 - 
        if (touchDetail.x > BUTTON1_X && touchDetail.x < BUTTON1_X + BUTTON_WIDTH && 
            touchDetail.y > BUTTON_Y && touchDetail.y < BUTTON_Y + BUTTON_HEIGHT) {
            if (deb == 0) {
                deb = 1;
                Serial.println("Button 1 pressed");
                M5.Speaker.tone(3000, 50);
            }
        }
        
        // Button 2 - 
        else if (touchDetail.x > BUTTON2_X && touchDetail.x < BUTTON2_X + BUTTON_WIDTH && 
                 touchDetail.y > BUTTON_Y && touchDetail.y < BUTTON_Y + BUTTON_HEIGHT) {
            if (deb == 0) {
                deb = 1;
                Serial.println("Button 2 pressed");
                M5.Speaker.tone(3000, 50);
            }
        }
        
        // Button 3 - 
        else if (touchDetail.x > BUTTON3_X && touchDetail.x < BUTTON3_X + BUTTON_WIDTH && 
                 touchDetail.y > BUTTON_Y && touchDetail.y < BUTTON_Y + BUTTON_HEIGHT) {
            if (deb == 0) {
                deb = 1;
                Serial.println("Button 3 pressed");
                M5.Speaker.tone(3000, 50);
            }
        }
        
        // Brightness Minus Button
        else if (touchDetail.x > BRIGHT_MINUS_X && touchDetail.x < BRIGHT_MINUS_X + BRIGHT_BUTTON_WIDTH && 
                 touchDetail.y > BRIGHT_GROUP_Y && touchDetail.y < BRIGHT_GROUP_Y + BRIGHT_BUTTON_HEIGHT) {
            if (deb == 0) {
                deb = 1;
                brightness = max(0, brightness - 10); // Decrease by 10, minimum 0
                M5.Display.setBrightness(brightness);
                updateBrightnessDisplay();
                Serial.println("Brightness decreased to: " + String(brightness));
                M5.Speaker.tone(2000, 30);
            }
        }
        
        // Brightness Plus Button
        else if (touchDetail.x > BRIGHT_PLUS_X && touchDetail.x < BRIGHT_PLUS_X + BRIGHT_BUTTON_WIDTH && 
                 touchDetail.y > BRIGHT_GROUP_Y && touchDetail.y < BRIGHT_GROUP_Y + BRIGHT_BUTTON_HEIGHT) {
            if (deb == 0) {
                deb = 1;
                brightness = min(255, brightness + 10); // Increase by 10, maximum 255
                M5.Display.setBrightness(brightness);
                updateBrightnessDisplay();
                Serial.println("Brightness increased to: " + String(brightness));
                M5.Speaker.tone(2500, 30);
            }
        }
    } else {
        deb = 0;
    }
}

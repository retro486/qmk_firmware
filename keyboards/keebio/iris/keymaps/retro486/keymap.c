#include QMK_KEYBOARD_H

bool colemak_enabled = false;

enum layer_number {
  _BASE = 0,
  _COLEMAK,
  _ALT
};

// Toggle layers
#define TG_COLEMAK TG(_COLEMAK)
#define TT_ALT TT(_ALT)

// Tap dance
enum tapdances {
  TD_ZP = 0,
  TD_LBRB
};

#define KC_ZP TD(TD_ZP)
#define KC_LBRB TD(TD_LBRB)

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ZP] = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_EQL),
  [TD_LBRB] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC)
};

enum custom_keycodes {
  COLEMAKRGB = SAFE_RANGE,
  ALTRGB
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAKRGB:
      if (record->event.pressed) {
        layer_invert(_COLEMAK);
        if(colemak_enabled) {
          // toggle rgb off
          rgblight_disable();
          colemak_enabled = false;
         } else {
           rgblight_enable();
           rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
           colemak_enabled = true;
         }
      } else {
        // when keycode COLEMAKRGB is released
      }
      break;
   case ALTRGB:
      if (record->event.pressed) {
         layer_on(_ALT);
         rgblight_enable();
         rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT);
      } else {
         layer_off(_ALT);
         if(colemak_enabled) {
            rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
         } else {
            // toggle rgb off
            rgblight_disable();
         }
      }
      break;
  }
  return true;
};

// Actual keymapping
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_ZP,   KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     ALTRGB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS,          COLEMAKRGB, KC_N,  KC_M,   KC_COMM,  KC_DOT,  KC_SLSH, ALTRGB,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_RALT,  KC_LCTRL , KC_ENT,                  KC_RSFT, KC_SPC, KC_LBRB
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______,    KC_R,    KC_S,    KC_T,    KC_D,                            _______,    KC_N,    KC_E,    KC_I,  KC_O,   _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______,  KC_K,   _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, RGB_MODE_KNIGHT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ALT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TILD,  KC_F1,    KC_F2,  KC_F3,   KC_F4,  KC_F5,                              _______, KC_F10,   KC_F11,  KC_F12,  KC_EQL,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRV,  _______, KC_PGDN,  KC_UP,   KC_PGUP, _______,                             KC_P7,   KC_P8,   KC_P9,  _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_HOME, KC_LEFT, KC_DOWN ,KC_RGHT , KC_END,                             KC_P4,  KC_P5,   KC_P6,  _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,  DM_PLY1,         _______,  KC_P1,   KC_P2,   KC_P3,  _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     DM_REC1,_______, DM_RSTP,                   _______,   KC_P0,  KC_RBRC
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

};

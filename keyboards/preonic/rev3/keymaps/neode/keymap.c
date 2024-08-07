/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "print.h"

enum preonic_layers {
  _QWERTY,
  _L1,
  _L3,
  _L3MOUSE,
  _L4,
  _L5,
  _ADJUST,
};

enum preonic_keycodes {
  L1 = SAFE_RANGE,
  L3,
  L3MOUSE,
  L4,
  ADJUST,
  QWERTY
};


enum unicode_names {
    Null,
  /// Umlaute ///
    AE_small,
    OE_small,
    UE_small,
    AE_capital,
    OE_capital,
    UE_capital,
  /// Emoji ///
    Emoji_ElePhant,
    Emoji_Smile,
    Emoji_Grin,
    Emoji_Wink,
    Emoji_Blush,
    Emoji_SmileSweat,
  /// Punctuation and Misc. Signs ///
    EUR_Sgn,
    Quote_Low_99,
    Quote_High_66,
    Quote_High_99,
    Ellipsis,
    Bullet_Point,
    Single_Low_9,
    Single_High_6,
    Single_High_9,
    Superscript_1,
    Superscript_2,
    Superscript_3,
    Subscript_0,
    Subscript_1,
    Subscript_2,
    Subscript_3,
    Feminine_Ordinal,
    Masculine_Ordinal,
    Degree_Sign,
    Quote_angle_left,
    Quote_angle_right,
    SQuote_angle_left,
    SQuote_angle_right,
    Inverted_QM,
    Inverted_EXM,
    En_Dash,
    Em_Dash,
    Horizontal_Bar,
    Female_Sign,
    Trans_Inter_Sign,
    Male_Sign,
    Left_angle_bracket,
    Right_angle_bracket,
  /// Greek letters ///
    Xi_small,
    Xi_capital,
    Lambda_small,
    Lambda_capital,
    Chi_small,
    Omega_small,
    Omega_capital,
    Kappa_small,
    Psi_small,
    Psi_capital,
    Gamma_small,
    Gamma_capital,
    Curly_Phi,
    Phi_small,
    Phi_capital,
    Stigma_small,
    Iota_small,
    Alpha_small,
    Curly_Epsilon,
    Omicron_small,
    Sigma_small,
    Sigma_capital,
    Nu_small,
    Rho_small,
    Tau_small,
    Delta_small,
    Delta_capital,
    Upsilon_small,
    Epsilon_small,
    Eta_small,
    Pi_small,
    Pi_capital,
    Zeta_small,
    Beta_small,
    Mu_small,
    Rho_Symbol,
    Curly_Theta,
    Theta_small,
    Theta_capital,
    Var_kappa,
  /// Mathematical symbols ///
    Partial,
    Infinity,
    Radix,
    Integral,
    Nabla,
    Rightarrow,
    Leftarrow,
    Leftrightarrow,
    Rightwards,
    Mapsto,
    ForAll,
    Exists,
    PropTo,
    ElementOf,
    EmptySet,
    Subset,
    And,
    Or,
    Intersection,
    Union,
    Alef,
    RealNumbers,
    NaturalNumbers,
    RationalNumbers,
    ComplexNumbers,
    Integers,
    Times,
    ParallelTo,
    Angle,
    Dagger,
    Tee,
    Not_Sign,

};

const uint32_t PROGMEM unicode_map[] = {
    [Null] = 0x0000, //
  /// Umlaute ///
    [AE_small] = 0x00E4,  // ä
    [OE_small] = 0x00F6,  // ö
    [UE_small] = 0x00FC, // ü
    [AE_capital] = 0x00C4,  // Ä
    [OE_capital] = 0x00D6,  // Ö
    [UE_capital] = 0x00DC, // Ü
    [Quote_Low_99] = 0x201E, // „
    [Quote_High_66] = 0x201C, // “
    [Quote_High_99] = 0x201D, // ”
  /// Emoji ///
    [Emoji_ElePhant] = 0x1F418, // 🐘
    [Emoji_Smile] = 0x1F642, // 🙂
    [Emoji_Grin] = 0x1F600, // 😀
    [Emoji_Wink] = 0x1F609, // 😉
    [Emoji_Blush] = 0x1F60A, // 😊
    [Emoji_SmileSweat] = 0x1F605, // 😅
   /// Punctuation and Misc. Signs ///
    [EUR_Sgn]  = 0x20AC, // €
    [Ellipsis] = 0x2026, // …
    [Bullet_Point] = 0x2022, // •
    [Single_Low_9] = 0x201A, // ‚
    [Single_High_6] = 0x2018, // ‘
    [Single_High_9] = 0x2019, // ’
    [Superscript_1] = 0x00B9, // ¹
    [Superscript_2] = 0x00B2, // ²
    [Superscript_3] = 0x00B3, // ³
    [Subscript_0] = 0x2080, //
    [Subscript_1] = 0x2081, //
    [Subscript_2] = 0x2082, //
    [Subscript_3] = 0x2083, //
    [Degree_Sign] = 0x00B0, //
    [Feminine_Ordinal] = 0x00AA, //
    [Masculine_Ordinal] = 0x00BA, //
    [SQuote_angle_left] = 0x203A, // ›
    [SQuote_angle_right] = 0x2039, // ‹
    [Quote_angle_left] = 0x00BB, // »
    [Quote_angle_right] = 0x00AB, // «
    [Inverted_QM] = 0x00BF, // ¿
    [Inverted_EXM] = 0x00A1, // ¡
    [En_Dash] = 0x2013, //
    [Em_Dash] = 0x2014, //
    [Horizontal_Bar] = 0x2015, //
    [Female_Sign] = 0x2640, //
    [Trans_Inter_Sign] = 0x26A6, //
    [Male_Sign] = 0x2642, //
    [Left_angle_bracket] = 0x3008, //
    [Right_angle_bracket] = 0x3009, //
  /// Greek letters ///
    [Xi_small] = 0x03BE, // ξ
    [Xi_capital] = 0x039E, // Ξ
    [Lambda_small] = 0x03BB, // λ
    [Lambda_capital] = 0x039B, // Λ
    [Chi_small] = 0x03C7, // χ
    [Omega_small] = 0x03C9, // ω
    [Omega_capital] = 0x03A9, // Ω
    [Kappa_small] = 0x03BA, // κ
    [Psi_small] = 0x03C8, // ψ
    [Psi_capital] = 0x03A8, // Ψ
    [Gamma_small] = 0x03B3, // γ
    [Gamma_capital] = 0x0393, // Γ
    [Curly_Phi] = 0x03C6, // φ
    [Phi_small] = 0x03D5, // ϕ
    [Phi_capital] = 0x03A6, // Φ
    [Stigma_small] = 0x03DA, // ς
    [Iota_small] = 0x03B9, // ι
    [Alpha_small]= 0x03B1, // α
    [Curly_Epsilon] = 0x03B5, // ε
    [Omicron_small] = 0x03BF, // ο
    [Sigma_small] = 0x03C3, // σ
    [Sigma_capital] = 0x03A3, // Σ
    [Nu_small] = 0x03BD, // ν
    [Rho_small] = 0x03C1, // ρ
    [Tau_small] = 0x03C4, // τ
    [Delta_small] = 0x03B4, // δ
    [Delta_capital] = 0x0394, // Δ
    [Upsilon_small] = 0x03C5, // υ
    [Epsilon_small] = 0x03F5, // ϵ
    [Eta_small] = 0x03B7, // η
    [Pi_small] = 0x03C0, // π
    [Pi_capital] = 0x03A0, // Π
    [Zeta_small] = 0x03B6, // β
    [Beta_small] = 0x03B2, // β
    [Mu_small] = 0x03BC, // μ
    [Rho_Symbol] = 0x03F1, // ϱ
    [Curly_Theta] = 0x03D1, // ϑ
    [Theta_small] = 0x03B8, // θ
    [Theta_capital] = 0x0398, // Θ
    [Var_kappa] = 0x03F0, //
  /// Mathematical symbols ///
    [Partial] = 0x2202, // ∂
    [Infinity] = 0x221E, // ∞
    [Radix] = 0x221A, // √
    [Integral] = 0x222B, // ∫
    [Nabla] = 0x2207, // ∇
    [Rightarrow] = 0x21D2, // ⇒
    [Leftarrow] = 0x21D0, // ⇐
    [Leftrightarrow] = 0x21D4, // ⇔
    [Rightwards] = 0x2192, // ↦
    [Mapsto] = 0x21A6, // ↦
    [ForAll] = 0x2200, // ∀
    [Exists] = 0x2203, // ∃
    [PropTo] = 0x221D, // ∝
    [ElementOf] = 0x2208, // ∈
    [EmptySet] = 0x2205, // ∅
    [Subset] = 0x2282, // ⊂
    [And] = 0x2227, // ∧
    [Or] = 0x2228, // ∨
    [Intersection] = 0x2229, // ∩
    [Union] = 0x222A, // ∪
    [Alef] = 0x05D0, // ℵ
    [RealNumbers] = 0x211D, // ℝ
    [NaturalNumbers] = 0x2115, // ℕ
    [RationalNumbers] = 0x211A, // ℚ
    [ComplexNumbers] = 0x2102, // ℂ
    [Integers] = 0x2124, // ℤ
    [Times] = 0x00D7, // ×
    [ParallelTo] = 0x2225, // ∥
    [Angle] = 0x2221, // ∡
    [Dagger] = 0x2020, // †
    [Tee] = 0x22A4, // ⊤
    [Not_Sign] = 0x00AC, //

};

/// Tap dances ///
enum {
    CT_E,
    CT_O,
    CT_C,
};

// e, é, è, ê //
void dance_e_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_E); // e
    } else if (state->count == 2) {
        SEND_STRING(SS_LALT("00E9")); // é
    } else  if (state->count == 3) {
      SEND_STRING(SS_LALT("00E8")); // è
    } else {
      SEND_STRING(SS_LALT("00EA")); // ê
    }
}

void dance_e_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_E);
    }
}
///////////////////

// o, ô, œ //
void dance_o_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_O); // o
    } else if (state->count == 2) {
        SEND_STRING(SS_LALT("00F4")); // ô
    } else {
      SEND_STRING(SS_LALT("0153")); // œ
    }
}

void dance_o_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_O);
    }
}
////////////////////

// c,  //
void dance_c_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_C); // c
    } else {
        SEND_STRING(SS_LALT("00E7")); //  ç
    }
}

void dance_c_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_C);
    }
}
//////////////////

// All tap dance functions go here
tap_dance_action_t tap_dance_actions[] = {
    [CT_E] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_e_finished, dance_e_reset),
    [CT_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_o_finished, dance_o_reset),
    [CT_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_c_finished, dance_c_reset),
};

/// END tap dances ///


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Neo2 Layer 1
 * ,-----------------------------------------------------------------------------------.
 * |   ^  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   X  |   V  |   L  |   C  |   W  |   K  |   H  |   G  |   F  |   Q  |Enter |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   U  |   I  |   A  |   E  |   O  |   S  |   N  |   R  |   T  |   D  |  Y   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Ü  |   Ö  |   Ä  |   P  |   Z  |   B  |   M  |   ,  |   .  |   J  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ADJUS| Ctrl | Alt  | GUI  |  L4  |    Space    |  L3  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

  // ẞ implemented as combo s+z

/* Neo2 Layer 2 = Layer 1 shifted
 * ,-----------------------------------------------------------------------------------.
 * |   ˇ  |  🙂  |  😀 |  😊  |   😉 |   😅 |   $  |   €  |   „  |   “  |   ”  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   X  |   V  |   L  |   C  |   W  |   K  |   H  |   G  |   F  |   Q  |Enter |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  L3  |   U  |   I  |   A  |   E  |   O  |   S  |   N  |   R  |   T  |   D  |  Y   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Ü  |   Ö  |   Ä  |   P  |   Z  |   B  |   M  |   -  |   .  |   J  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |  L4  |    Space    |  L3  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_L1] = LAYOUT_preonic_grid(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_X,    KC_V,    KC_L,    TD(CT_C),    KC_W,    KC_K,    KC_H,    KC_G,    KC_F,    KC_Q,    KC_ENT,
  L3,      KC_U,    KC_I,    KC_A,    TD(CT_E),    TD(CT_O),    KC_S,    KC_N,    KC_R,    KC_T,    KC_D,    KC_Y,
  KC_LSFT, UP(UE_small, UE_capital),   UP(OE_small,OE_capital),   UP(AE_small,AE_capital),   KC_P,    KC_Z,    KC_B,    KC_M,    KC_COMM, KC_DOT,  KC_J,    KC_RSFT,
  ADJUST, KC_LCTL, KC_LALT, KC_LGUI, L4,   KC_SPC,  KC_SPC,  L3MOUSE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),


// [_SHIFTED] = LAYOUT_preonic_grid(
//   KC_GRV,  UM(Emoji_Smile),    UM(Emoji_Grin),  UM(Emoji_Blush),   UM(Emoji_Wink),     UM(Emoji_SmileSweat),     KC_DLR,    UM(EUR_Sgn),    UM(Quote_Low_99),    UM(Quote_High_66),    UM(Quote_High_99),    KC_BSPC,
//   KC_TAB,  S(KC_X),    S(KC_V),    S(KC_L),    S(KC_C),    S(KC_W),    S(KC_K),    S(KC_H),    S(KC_G),    S(KC_F),    S(KC_Q),    KC_ENT,
//   KC_ESC,  S(KC_U),    S(KC_I),    S(KC_A),    S(KC_E),    S(KC_O),    S(KC_S),    S(KC_N),    S(KC_R),    S(KC_T),    S(KC_D),    S(KC_Y),
//   KC_TRNS, UM(UE_capital),   UM(OE_capital),   UM(AE_capital),   S(KC_P),    S(KC_Z),    S(KC_B),    S(KC_M),    KC_MINS, UM(Bullet_Point),  S(KC_J),    KC_TRNS,
//   KC_TRNS, KC_LCTL, KC_LALT, KC_LGUI, L4,   KC_SPC,  KC_SPC,  L3,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
// ),


/* Neo2 Layer 3
 * ,-----------------------------------------------------------------------------------.
 * |   ˇ  |   ¹  |   ²  |   ³  |   »  |   «  |   ›  |   ‹  |   ‚  |   ‘  |   ’  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   …  |   _  |   [  |   ]  |   ^  |   !  |   <  |   >  |   =  |   &  |Enter |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   \  |   /  |   {  |   }  |   *  |   ?  |   (  |   )  |   -  |   :  |  @   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   #  |   $  |   |  |   ~  |   `  |   +  |   %  |   "  |   '  |   ;  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |  L4  |    Space    |  L3  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */


[_L3] = LAYOUT_preonic_grid(
  KC_GRV,  UM(Superscript_1),    UM(Superscript_2),   UM(Superscript_3),     UM(Quote_angle_left),    UM(Quote_angle_right),    UM(SQuote_angle_left),    UM(SQuote_angle_right),    UM(Single_Low_9),    UM(Single_High_6),    UM(Single_High_9),    KC_BSPC,
  KC_TAB,  UM(Ellipsis), S(KC_MINS),      KC_LBRC,    KC_RBRC,    S(KC_6),    KC_EXLM,    KC_LT,    KC_GT,    KC_EQL,    KC_AMPR,    KC_ENT,
  KC_ESC,  KC_BSLS,    KC_SLSH,    KC_LCBR,    KC_RCBR,    KC_ASTR,      S(KC_SLSH),    KC_LPRN,    KC_RPRN,    KC_MINS,    KC_COLN,    KC_AT,
  KC_TRNS, KC_HASH,   KC_DLR,   KC_PIPE,   KC_TILD,    KC_GRV,    KC_PLUS,    KC_PERC,    KC_DQUO, KC_QUOT,  KC_SCLN,    KC_TRNS,
  KC_TRNS, KC_LCTL, KC_LALT, KC_LGUI, L4,   KC_SPC,  KC_SPC,  L3MOUSE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Neo2 Layer 3 with RHS as mouse keys
 * ,-----------------------------------------------------------------------------------.
 * |   ˇ  |   ¹  |   ²  |   ³  |   »  |   «  |   ›  |   ‹  |   ‚  |   ‘  |   ’  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   …  |   _  |   [  |   ]  |   ^  |   !  |  MWU |  MUP |  MWD |   &  |Enter |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   \  |   /  |   {  |   }  |   *  |  MLC |  ML  |  MD  |  MR  |  MRC |  @   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   #  |   $  |   |  |   ~  |   `  |   +  |  MWL |   "  |  MWR |   ;  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |  L4  |    Space    |  L3  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */


[_L3MOUSE] = LAYOUT_preonic_grid(
  KC_GRV,  UM(Superscript_1),    UM(Superscript_2),   UM(Superscript_3),     UM(Quote_angle_left),    UM(Quote_angle_right),    UM(SQuote_angle_left),    UM(SQuote_angle_right),    UM(Single_Low_9),    UM(Single_High_6),    UM(Single_High_9),    KC_BSPC,
  KC_TAB,  UM(Ellipsis), S(KC_MINS),      KC_LBRC,    KC_RBRC,    S(KC_6),    KC_EXLM,    KC_WH_U,    KC_MS_U,    KC_WH_D,    KC_AMPR,    KC_ENT,
  KC_ESC,  KC_BSLS,    KC_SLSH,    KC_LCBR,    KC_RCBR,    KC_ASTR,      KC_BTN1,    KC_MS_L,    KC_MS_D,    KC_MS_R,    KC_BTN2,    KC_AT,
  KC_TRNS, KC_HASH,   KC_DLR,   KC_PIPE,   KC_TILD,    KC_GRV,    KC_PLUS,    KC_WH_L,    KC_DQUO, KC_WH_R,  KC_SCLN,    KC_TRNS,
  KC_TRNS, KC_LCTL, KC_LALT, KC_LGUI, L4,   KC_SPC,  KC_SPC,  L3MOUSE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),


/* Neo2 Layer 4
 * ,-----------------------------------------------------------------------------------.
 * |   ˇ  |   °  |   ª  |   º  |   »  |   «  |      |   -  |   –  |   —  |   ―  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  | PGUp | Bksp |  Up  |  Del |PGDwn |   ¡  |   7  |   8  |   9  |   /  |Enter |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  | Home | Left | Down | Right| End  |   ¿  |   4  |   5  |   6  |   +  |  -   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|  Esc | Tab  |Insert|Enter |Return|   0  |   1  |   2  |   3  |   *  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |  L4  |    Space    |  L3  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */


[_L4] = LAYOUT_preonic_grid(
  KC_GRV,  UM(Degree_Sign),    UM(Feminine_Ordinal),   UM(Masculine_Ordinal),    UM(Quote_angle_left),    UM(Quote_angle_right),    UM(Null),    KC_MINS,    UM(En_Dash),    UM(Em_Dash),    UM(Horizontal_Bar),    KC_BSPC,
  KC_TAB,  KC_PGUP,    KC_BSPC,     KC_UP,      KC_DEL,     KC_PGDN,     UM(Inverted_EXM),  KC_P7,    KC_P8,    KC_P9,    KC_PSLS,    KC_ENT,
  KC_ESC,  C(KC_A),    KC_LEFT,     KC_DOWN,    KC_RGHT,    C(KC_E),     UM(Inverted_QM),   KC_P4,    KC_P5,    KC_P6,    KC_PPLS,    KC_PMNS,
  KC_LSFT, KC_ESC,     KC_TAB,      KC_INS,     KC_ENT,     KC_RETURN,   KC_P0,            KC_P1,    KC_P2,    KC_P3,    KC_PAST,    KC_RSFT,
  KC_TRNS, KC_LCTL,    KC_LALT,     KC_LGUI,    L4,         KC_SPC,      KC_SPC,           L3MOUSE,       KC_LEFT,  KC_DOWN,  KC_UP,      KC_RGHT
),

/* Neo2 Layer 5 (L3 + L4)
 * ,-----------------------------------------------------------------------------------.
 * |   ˇ  |   ₁  |   ₂  |   ₃  |   ♀  |   ♂  |   ⚥  |   ϰ  |   ⟨  |   ⟩  |   ₀  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   ξ  |   ς  |   λ  |   χ  |   ω  |   κ  |   ψ  |   γ  |   φ  |   ϕ  |Enter |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |  --- |   ι  |   α  |   ε  |   ο  |   σ  |   ν  |   ρ  |   τ  |   δ  |  υ   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|  --- |   ϵ  |   η  |   π  |   ζ  |   β  |   μ  |   ϱ  |   ϑ  |   θ  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |  L4  |    Space    |  L3  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

// position of Stigma ς changed

/* Neo2 Layer 6 = 5 Shifted
 * ,-----------------------------------------------------------------------------------.
 * |      |   †  |   ∨  |   ∧  |   ⊤  |   ∡  |   ∥  |   →  |   ∞  |   ∝  |   ∅  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Ξ  |   √  |   Λ  |   ℂ  |   Ω  |   ×  |   Ψ  |   Γ  |   Φ  |   ℚ  |Enter |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   ⊂  |   ∫  |   ∀  |   ∃  |   ∈  |   Σ  |   ℕ  |   ℝ  |   ∂  |   Δ  |  ∇   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ∪  |   ∩  |   ℵ  |   Π  |   ℤ  |   ⇐  |   ⇔  |   ⇒  |   ↦  |   Θ  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |  L4  |    Space    |  L3  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */



[_L5] = LAYOUT_preonic_grid(
  KC_GRV,  UP(Subscript_1,Dagger),    UP(Subscript_2,Or),   UP(Subscript_3,And),    UP(Female_Sign,Not_Sign),    UP(Trans_Inter_Sign,Angle),    UP(Male_Sign,ParallelTo),    UP(Var_kappa,Rightwards),    UP(Left_angle_bracket,Infinity),    UP(Right_angle_bracket,PropTo),    UP(Subscript_0,EmptySet),    KC_BSPC,
  KC_TAB,  UP(Xi_small,Xi_capital),    UP(Stigma_small,Radix),     UP(Lambda_small,Lambda_capital),   UP(Chi_small,ComplexNumbers),  UP(Omega_small,Omega_capital),      UP(Kappa_small,Times),    UP(Psi_small,Psi_capital),     UP(Gamma_small,Gamma_capital),  UP(Curly_Phi,Phi_capital),    UP(Phi_small,RationalNumbers),   KC_ENT,
  KC_ESC,  UP(Null,Subset),    UP(Iota_small,Integral),     UP(Alpha_small,ForAll),    UP(Curly_Epsilon,Exists),    UP(Omicron_small,ElementOf),      UP(Sigma_small,Sigma_capital),   UP(Nu_small,NaturalNumbers),    UP(Rho_small,RealNumbers),    UP(Tau_small,Partial),    UP(Delta_small, Delta_capital),    UP(Upsilon_small,Nabla),
  KC_RSFT, UP(Null,Union),    UP(Epsilon_small,Intersection),      UP(Eta_small,Alef),     UP(Pi_small,Pi_capital),     UP(Zeta_small,Integers),   UP(Beta_small,Leftarrow),    UP(Mu_small,Leftrightarrow),    UP(Rho_Symbol,Rightarrow),    UP(Curly_Theta,Mapsto),    UP(Theta_small,Theta_capital),    KC_RSFT,
  KC_TRNS, KC_LCTL,    KC_LALT,     KC_LGUI,    L4,         KC_SPC,      KC_SPC,           L3MOUSE,       KC_LEFT,  KC_DOWN,  KC_UP,      KC_RGHT
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|      |  L1  |QWERTY|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |Mus on|MusOff|      |      |      |Brigh+|Brigh-|Sleep |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Play/Pause  | Prev | Next | Vol- | Vol+ | Mute |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, RESET,   DB_TOGG,   _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
  _______, _______, MU_NEXT,  AU_ON,   AU_OFF,  _______, L1,      QWERTY,  _______, _______, _______, _______,
  _______, _______, _______,  MU_ON,   MU_OFF, _______, _______, _______, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_SYSTEM_SLEEP, _______,
  _______, _______, _______, _______, KC_MSTP, KC_MPLY, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE
),

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
  L3,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, L4,      KC_SPC,  KC_SPC,  L3MOUSE,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),



};
uint8_t mod_state;

// macro for cmd+e for end and cmd+a beginning of line
// tap dance for e, ee é, è, ê, ẽ, ě, … and other letters, need œ, …?



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Store the current modifier state in the variable for later reference
  mod_state = get_mods();
  // if console is enabled print layer_state
  #ifdef CONSOLE_ENABLE
    uprintf("Default layer state: %d with current active layers L1: %d, L3: %d, L4: %d, L5: %d, ADJUST: %d, QWERTY: %d\n", default_layer_state, IS_LAYER_ON(_L1),IS_LAYER_ON(_L3), IS_LAYER_ON(_L4), IS_LAYER_ON(_L5), IS_LAYER_ON(_ADJUST), IS_LAYER_ON(_QWERTY));
  #endif
  switch (keycode) {
        case L1:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_L1);
          }
          return false;
          break;
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case L3:
          if (record->event.pressed) {
            layer_on(_L3);
          } else {
            layer_off(_L3);
          }
          return false;
          break;
        case L3MOUSE:
          if (record->event.pressed) {
            layer_on(_L3MOUSE);
            update_tri_layer(_L3MOUSE, _L4, _L5);
          } else {
            layer_off(_L3MOUSE);
            update_tri_layer(_L3MOUSE, _L4, _L5);
          }
          return false;
          break;
        case L4:
          if (record->event.pressed) {
            layer_on(_L4);
            update_tri_layer(_L3MOUSE, _L4, _L5);
          } else {
            layer_off(_L4);
            update_tri_layer(_L3MOUSE, _L4, _L5);
          }
          return false;
          break;
          case ADJUST:
          if (record->event.pressed) {
            layer_on(_ADJUST);
          } else {
            layer_off(_ADJUST);
          }
          return false;
          break;
// Modified example from https://beta.docs.qmk.fm/using-qmk/simple-keycodes/feature_advanced_keycodes
// for shifted number row in Neo 2
//  |  ˇ  |  🙂  |  😀 |  😊  |   😉 |   😅 |   $  |   €  |   „  |   “  |   ”  | Bksp |
        case KC_1:
        {
        // Initialize a boolean variable that keeps track
        // of the custom shift key status: registered or not?
        static bool shiftedkey_registered; //e.g. unicode symbol
        if (record->event.pressed) {
            // Detect the activation of either shift keys and if the correct default layer L1 is active
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("D83D+DE42"));
                // Update the boolean variable to reflect the status of KC_DLR
                shiftedkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_1 keycode as usual outside of shift
        return true;
    }
        case KC_2:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("D83D+DE01"));
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
       }
        case KC_3:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("D83D+DE0A"));
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
        return true;
       }
        case KC_4:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("D83D+DE09"));
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
        return true;
       }
       case KC_5:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("D83D+DE05"));
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
        return true;
       }
       case KC_6:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("0024"));
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
        return true;
       }
       case KC_7:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("20AC"));
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
        return true;
       }
       case KC_8:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("201E"));
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
        return true;
    }
     case KC_9:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("201C"));
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
        return true;
    }
     case KC_0:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("201D"));
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
        return true;
    }
// shifted versions of KC_COMM, KC_DOT on Neo
    case KC_COMM:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_MINS);
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                unregister_code(KC_MINS);
                shiftedkey_registered = false;
                return false;
            }
        }
        return true;
        }
    case KC_DOT:
        {
        static bool shiftedkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT && (default_layer_state == 2)) {
                del_mods(MOD_MASK_SHIFT);
                SEND_STRING(SS_LALT("2022"));
                shiftedkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (shiftedkey_registered) {
                shiftedkey_registered = false;
                return false;
            }
        }
        return true;
        }
  }
    return true;
};


/// COMBOS ///
// combo key for ß with s+z

enum combo_events {
  SZ_COMBO,
};

const uint16_t PROGMEM sz_combo[] = {KC_S, KC_Z, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [SZ_COMBO] = COMBO_ACTION(sz_combo),
};


void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case SZ_COMBO:
      if (pressed) {
        SEND_STRING(SS_LALT("00DF"));
      }
      break;
  }
}
/// END of COMBOS ///

#include "form1.h"

using namespace xtd::forms;
using namespace tictactoe;

static const xtd::drawing::size WINDOW_SIZE = { 640, 480 };
static const xtd::drawing::size BUTTON_SIZE = { 80, 80 };

static const std::array<xtd::drawing::point, 9> BUTTON_LOCATIONS =
{
  xtd::drawing::point(100 + BUTTON_SIZE.width(),     100),
  xtd::drawing::point(100 + BUTTON_SIZE.width() * 2, 100),
  xtd::drawing::point(100 + BUTTON_SIZE.width() * 3, 100),

  xtd::drawing::point(100 + BUTTON_SIZE.width(),     100 + BUTTON_SIZE.height()),
  xtd::drawing::point(100 + BUTTON_SIZE.width() * 2, 100 + BUTTON_SIZE.height()),
  xtd::drawing::point(100 + BUTTON_SIZE.width() * 3, 100 + BUTTON_SIZE.height()),

  xtd::drawing::point(100 + BUTTON_SIZE.width(),     100 + BUTTON_SIZE.height() * 2),
  xtd::drawing::point(100 + BUTTON_SIZE.width() * 2, 100 + BUTTON_SIZE.height() * 2),
  xtd::drawing::point(100 + BUTTON_SIZE.width() * 3, 100 + BUTTON_SIZE.height() * 2)
};

form1::form1() {
  text("TicTacToe");
  client_size(WINDOW_SIZE);
  minimum_size(WINDOW_SIZE);
  maximum_size(WINDOW_SIZE);
  
  // Buttons
  for(std::size_t i{0u}; i < m_buttons.size(); ++i)
  {
    m_buttons[i].reset(new xtd::forms::button()); 
    m_buttons[i]->parent(*this)
      .text(xtd::ustring::empty_string())
      .font(xtd::drawing::font(xtd::drawing::font_family::generic_sans_serif(), 24, xtd::drawing::font_style::bold))
      .location(BUTTON_LOCATIONS[i])
      .size(BUTTON_SIZE)
      .back_color(xtd::drawing::color::light_gray)
      .fore_color(xtd::drawing::color::black)
      .click += xtd::event_handler(*this, &form1::on_button_click);
  }
 
  // Labels
  m_player_x_score_label.reset(new xtd::forms::label());
  m_player_x_score_label->parent(*this)
    .text(xtd::ustring::format("Player X: {}", m_player_x_score))
    .auto_size(true)
    .location({ 5, 5 })
    .font(xtd::drawing::font(xtd::drawing::font_family::generic_sans_serif(), 12))
    .fore_color(xtd::drawing::color::orange);
  
  m_player_o_score_label.reset(new xtd::forms::label());
  m_player_o_score_label->parent(*this)
    .text(xtd::ustring::format("Player O: {}", m_player_o_score))
    .auto_size(true)
    .location({ size().width() - m_player_o_score_label->size().width()*2, 5 })
    .font(xtd::drawing::font(xtd::drawing::font_family::generic_sans_serif(), 12))
    .fore_color(xtd::drawing::color::orange);
}

bool form1::there_is_a_winner()
{
  // | A1 | A2 | A3 |
  // |----|----|----|
  // | B1 | B2 | B3 |
  // |----|----|----|
  // | C1 | C2 | C3 |

  const xtd::forms::button& A1 = *m_buttons[0];
  const xtd::forms::button& A2 = *m_buttons[1];
  const xtd::forms::button& A3 = *m_buttons[2];
  
  const xtd::forms::button& B1 = *m_buttons[3];
  const xtd::forms::button& B2 = *m_buttons[4];
  const xtd::forms::button& B3 = *m_buttons[5];
  
  const xtd::forms::button& C1 = *m_buttons[6];
  const xtd::forms::button& C2 = *m_buttons[7];
  const xtd::forms::button& C3 = *m_buttons[8];

  // Check state where all buttons are empty (start or restart of the game)
  if (A1.text().empty() && A2.text().empty() && A3.text().empty() &&
      B1.text().empty() && B2.text().empty() && B3.text().empty() &&
      C1.text().empty() && C2.text().empty() && C3.text().empty())
    return false;

  // Horizontal A1 == A2 == A3
  if (A1.text() == A2.text() && A2.text() == A3.text() && !A1.text().empty())
    return true;
  // Horizontal row B1 == B2 == B3
  if (B1.text() == B2.text() && B2.text() == B3.text() && !B1.text().empty())
    return true;
  // Horizontal row C1 == C2 == C3
  if (C1.text() == C2.text() && C2.text() == C3.text() && !C1.text().empty())
    return true;

  // Vertical A1 == B1 == C1
  if (A1.text() == B1.text() && B1.text() == C1.text() && !A1.text().empty())
    return true;
  // Vertical A2 == B2 == C2
  if (A2.text() == B2.text() && B2.text() == C2.text() && !A2.text().empty())
    return true;
  // Vertical A3 == B3 == C3
  if (A3.text() == B3.text() && B3.text() == C3.text() && !A3.text().empty())
    return true;

  // Diagonal \ A1 == B2 == C3
  if (A1.text() == B2.text() && B2.text() == C3.text() && !A1.text().empty())
    return true;
  // Diagonal / A3 == B2 == C1
  if (A3.text() == B2.text() && B2.text() == C1.text() && !A3.text().empty())
    return true;

  return false;
}

bool form1::is_a_tie()
{
  // | A1 | A2 | A3 |
  // |----|----|----|
  // | B1 | B2 | B3 |
  // |----|----|----|
  // | C1 | C2 | C3 |

  const xtd::forms::button& A1 = *m_buttons[0];
  const xtd::forms::button& A2 = *m_buttons[1];
  const xtd::forms::button& A3 = *m_buttons[2];

  const xtd::forms::button& B1 = *m_buttons[3];
  const xtd::forms::button& B2 = *m_buttons[4];
  const xtd::forms::button& B3 = *m_buttons[5];

  const xtd::forms::button& C1 = *m_buttons[6];
  const xtd::forms::button& C2 = *m_buttons[7];
  const xtd::forms::button& C3 = *m_buttons[8];

  return (!A1.text().empty() && !A2.text().empty() && !A3.text().empty() &&
          !B1.text().empty() && !B2.text().empty() && !B3.text().empty() &&
          !C1.text().empty() && !C2.text().empty() && !C3.text().empty());
}

void form1::toggle_all_buttons(bool enable)
{
  for (auto& btn : m_buttons)
    btn->enabled(enable);
}

void form1::reset()
{
  for (auto& btn : m_buttons)  btn->text("");
  toggle_all_buttons(true);
  m_XTurn = true;
}

void form1::on_button_click(xtd::object& sender, const xtd::event_args&)
{
  xtd::forms::button& button = static_cast<xtd::forms::button&>(sender);
  // Ignore interactions with disabled buttons (already have X or O in them)
  if (!button.enabled()) return;

  // Perform turn and disable button
  button.text(m_XTurn ? "X" : "O");
  button.enabled(false);
 
  // Check for a winner
  if (there_is_a_winner())
  {
    if (m_XTurn)
      m_player_x_score_label->text(xtd::ustring::format("Player X: {}", ++m_player_x_score));
    else
      m_player_o_score_label->text(xtd::ustring::format("Player O: {}", ++m_player_o_score));
    toggle_all_buttons(false);
    auto res = message_box::show(*this, xtd::ustring::format("Player {} is the WINNER!\nDo you want to play again ?", m_XTurn ? 'X' : 'O'), "Winner!", xtd::forms::message_box_buttons::yes_no);
    if(res == dialog_result::yes) {
      reset();
    }
    else {
      form::close();
    }
    return;
  }
  else if(is_a_tie()) // draw, no winner
  {
    auto res = message_box::show(*this, "No Winner!", "Tie!", xtd::forms::message_box_buttons::yes_no);
    if (res == dialog_result::yes) {
      reset();
    }
    else {
      form::close();
    }
  }

  // Switch turns
  m_XTurn = !m_XTurn;
}


void form1::main() {
  application::run(form1());
}


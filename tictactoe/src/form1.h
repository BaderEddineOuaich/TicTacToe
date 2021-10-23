/// @file
/// @brief Contains form1 class.
#pragma once
#include <xtd/xtd.forms>

/// @brief Represents the namespace that contains application objects.
namespace tictactoe {
  /// @brief Represents the main form.
  class form1 : public xtd::forms::form {
  public:
    /// @brief Initializes a new instance of the form1 class.
    form1();

    /// @brief The main entry point for the application.
    static void main();

    /// @brief Handles all buttons click event
    void on_button_click(xtd::object& sender, [[maybe_unused]] const xtd::event_args&);

    /// @brief Checks if there is a winner
    bool there_is_a_winner();

    /// @brief Checks if its a tie/draw, no winner.
    bool is_a_tie();

    /// @brief Disables or enables all buttons
    void toggle_all_buttons(bool enable);

    /// @brief Resets game buttons (enables buttons and sets text to "") IT DOES NOT RESET SCORES;
    void reset();

  private:
    bool m_XTurn = true;
    std::array<std::unique_ptr<xtd::forms::button>, 9> m_buttons;
    std::int32_t m_player_x_score{0}, m_player_o_score{0};
    std::unique_ptr<xtd::forms::label> m_status_label, m_player_x_score_label, m_player_o_score_label;
  };
}

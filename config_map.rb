class ConfigMap
  MAP = {
    "F1" => "1000000000000000",
    "F2" => "0100000000000000",
    "F3" => "0010000000000000",
    "F4" => "0001000000000000",
    "A1" => "0000000000000010",
    "A2" => "0000000000000100",
    "A3" => "0000000000000001",
    "A4" => "0000000000001000",
    "S1" => "0000100000000000",
    "S2" => "0000001000000000",
    "S3" => "0000010000000000",
    "S4" => "0000000100000000",
    "select" => "0000000010000000",
    "start" => "0000000001000000",
    "C1" => "0000000000100000",
    "C2" => "0000000000010000"
  }

  KEYS = {}

    %w{a b c d e f g h i j k l m n o p q r s t u v w x y z}.each do |char|
      KEYS[char] = ["XK_#{char}"]
    end
    sym = {
      "shift" => %w{XK_Shift_L},
      "semi_colon" => %w{XK_semicolon},
      "colon" => %w{XK_Shift_L XK_colon},
      "slash" => %w{XK_slash},
      "escape" => %w{XK_Escape},
      "comma" => %w{XK_comma},
      "dot" => %w{XK_period},
      "minus" => %w{XK_minus},
      "plus" => %w{XK_Shift_L XK_plus},
      "left_parenthesis" => %w{XK_parenleft},
      "right_parenthesis" => %w{XK_parenright},
      "right_square_bracket" => %w{XK_bracketleft},
      "left_square_bracket" => %w{XK_bracketright},
      "left_curly_bracket" => %w{XK_Shift_L XK_braceleft},
      "right_curly_bracket" => %w{XK_Shift_L XK_braceright},
      "exclamation" => %w{XK_Shift_L XK_exclam},
      "at" => %w{XK_Shift_L XK_at},
      "sharp" => %w{XK_Shift_L XK_numbersign},
      "dollar" => %w{XK_Shift_L XK_dollar},
      "percent" => %w{XK_Shift_L XK_percent},
      "question_mark" => %w{XK_Shift_L XK_question},
      "pipe" => %w{XK_Shift_L XK_bar},
      "asterisk" => %w{XK_Shift_L XK_asterisk},
      "underscore" => %w{XK_Shift_L XK_underscore},
      "double_quote" => %w{XK_Shift_L XK_quotedbl},
      "single_quote" => %w{XK_quotedbl},
      "ampersand" => %w{XK_Shift_L XK_ampersand},
      "equal" => %w{XK_equal},
      "less" => %w{XK_Shift_L XK_less},
      "greater" => %w{XK_Shift_L XK_greater},
      "space" => %w{XK_space},
      "enter" => %w{XK_Return},
      "backspace" => %w{XK_BackSpace},
      "page_up" => %w{XK_Page_Up},
      "end" => %w{XK_End},
      "page_down" => %w{XK_Page_Down},
      "home" => %w{XK_Home},
      "arrow_up" => %w{XK_Up},
      "arrow_right" => %w{XK_Right},
      "arrow_down" => %w{XK_Down},
      "arrow_left" => %w{XK_Left},
      "one" => %w{XK_1},
      "two" => %w{XK_2},
      "three" => %w{XK_3},
      "four" => %w{XK_4},
      "five" => %w{XK_5},
      "six" => %w{XK_6},
      "seven" => %w{XK_7},
      "eight" => %w{XK_8},
      "nine" => %w{XK_9},
      "zero" => %w{XK_0},
      "tab" => %w{XK_Tab},
      "ctrl" => %w{XK_Control_L},
      "super" => %w{XK_Super_L}
    }
    KEYS.merge!(sym)

  def self.merge(a, b)
    result = []
    a.split("").each_with_index do |el,i|
      result[i.to_i] = ((a[i] == "1") || (b[i] == "1")) ? "1" : "0"
    end
    result.join
  end

  def self.translate(config_text)
    result_lines = []
    config_text.each_line do |line|
      codes = []
      if line.split("\n").any?
        signifier = line.split(":").first
        signified = line.split(":").last.gsub("\n","")

        signified.split("+").each do |p|
          raise "#{p} not mapped." if KEYS[p].nil?
          if KEYS[p].count == 1
          codes << KEYS[p].first
          else
            codes << KEYS[p]
          end
        end

        codes.flatten!
        codes += [0,0] if codes.count == 1
        codes += [0] if codes.count == 2

        binaries = signifier.split("+").map do |sig|
          unless sig == "\n"
            MAP[sig]
          end
        end.compact

        merged = "0000000000000000"
        binaries.each do |bin|
          merged = merge(bin, merged)
        end
        result_lines << "{{#{merged.split("").join(",")}},#{codes.join(",")}},\n"
      end
    end
    result_lines.join
  end
end


// playregex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace nana;
using namespace nana::paint;
using namespace nana::API;
using namespace std;

class playregex : public form {
  place place_{*this};
  labelbox input_{*this, "Input", "Input parsed text here", true, true, true};
  labelbox regex_{*this, "Regex", "Input regex here", true, true, true};
  labelbox result_{*this, "Result", "", false};
  textbox console_{*this};

  string div_ =
      R"(	margin=10 vertical
				<weight=32% vertical
					<input>
					<regex>
					<result>
				>
				<weight=62% margin=5 <console>>
			
		)";

  ostringstream os_;
  string input_str_;
  string regex_str_;
  string result_str_;

  void setup() {
    logger() << "setup():enter" << std::endl;

    console_.multi_lines(true);
    console_.line_wrapped(true);
    console_.editable(false);
    console_.text_align(nana::align::left);

    logger() << "setup():leave" << std::endl;
  }

  void layout(string const& title = {}, image const& sicon = {},
              image const& bicon = {}) {
    logger() << "layout():enter" << std::endl;

    place_.div(div_.c_str());
    place_["input"] << input_;
    place_["regex"] << regex_;
    place_["result"] << result_;
    place_["console"] << console_;
    place_.collocate();

    window_caption(*this, title);
    window_icon(*this, sicon, bicon);
    fullscreen(*this, false);

    logger() << "layout():leave" << std::endl;
  }

  void result(string const& str = "non matched") { result_.text(str); }

  bool is_valid_regex_string(const std::string& rgx_str) {
    bool bResult = true;
    try {
      std::regex tmp(rgx_str);
    } catch (const std::regex_error& e) {
      (e);
      bResult = false;
    }
    return bResult;
  }

  void match() {
    logger() << "match():enter" << std::endl;

    if (input_str_.empty() || regex_str_.empty()) {
      logger() << "match():leave <empty>" << std::endl;
      result();
      return;
    }

    auto check_regex_string = [this]() -> bool {
      bool ret = true;
      try {
        regex r{this->regex_str_.c_str()};
      } catch (const std::regex_error&) {
        ret = false;
      }
      return ret;
    };

    if (!check_regex_string()) {
      logger() << "match():leave <invalid regex string>" << std::endl;
      result();
      return;
    }

    string s{input_str_};
    regex e{regex_str_.c_str()};
    smatch sm;

    if (!regex_match(s, sm, e)) {
      logger() << "match():leave <non-match>" << std::endl;
      result();
      return;
    }

    result(sm.str());
  }

  void normalize_regex(string& s) {
    for (auto it = std::find(s.begin(), s.end(), '\\'); it != s.end();
         it = std::find(it, s.end(), '\\')) {
      it = s.erase(it);

      size_t rest(std::distance(it, s.end()));
      if (rest < 2)
        std::advance(it, rest);
      else
        std::advance(it, 2);
    }
  }

  void connect() {
    logger() << "connect():enter" << std::endl;

    // connect update input text
    input_.connect([this](arg_textbox const& arg) {
      logger() << "input: " << arg.widget.caption() << endl;

      input_str_ = arg.widget.caption();
      match();
    });

    // connect update regex text
    regex_.connect([this](arg_textbox const& arg) {
      logger() << "regex: " << arg.widget.caption() << endl;

      regex_str_ = arg.widget.caption();
      //normalize_regex(regex_str_);
      match();
    });

    // connect update result text
    result_.connect([this](arg_textbox const& arg) {
      logger() << "result: " << arg.widget.caption() << endl;
    });

    // exit program
    this->events().unload([this](arg_unload const& arg) {
      logger() << "events().unload():enter" << std::endl;

      msgbox mb(*this, ("Warning"), msgbox::yes_no);
      mb.icon(mb.icon_question)
          << ("Are you sure you want to exit the program?");
      arg.cancel = (mb() == mb.pick_no);

      logger() << "events().unload():leave" << std::endl;
    });

    logger() << "connect():leave" << std::endl;
  }

 public:
  using default_appear =
      typename form::appear::decorate<appear::maximize, appear::minimize,
                                      appear::taskbar>;

  playregex(string const& title = {},
            rectangle const& rect = make_center(600, 600),
            image const& sicon = {}, image const& bicon = {},
            appearance const& appr = default_appear())
      : form{rect, appr} {
    setup();
    layout(title, sicon, bicon);
    connect();
  }

  typedef std::ostream& (*ostream_manipulator)(std::ostream&);

  playregex& logger() { return *this; }

  playregex& operator<<(ostream_manipulator manip) {
    os_ << manip;
    return *this;
  }

  template <class T>
  playregex& operator<<(T const& ch) {
    os_ << ch;
    console_.append(os_.str(), false);
    os_.clear();
    os_.str("");
    return *this;
  }
};

int main() {
  playregex theapp("playregex");

  theapp.show();

  exec();
}

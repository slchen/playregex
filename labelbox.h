#ifndef LABELBOX_H
#define LABELBOX_H

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>

class labelbox : public nana::panel<false> {
  nana::place place_{*this};
  nana::label label_{*this};
  nana::textbox textbox_{*this};

  std::string div_ = R"(	<margin=10 gap=10
								<weight=15% label><textbox>
							>)";

  std::function<void(nana::arg_textbox const& arg)> report_text_changed_{};

  void report_text_changed(nana::arg_textbox const& arg) {
    if (!report_text_changed_) return;

    report_text_changed_(arg);
  }

  void setup(std::string const& label, std::string const& tip, bool editable,
             bool line_wrapped, bool multi_lines) {
    label_.caption(label);
	label_.text_align(nana::align::left, nana::align_v::center);

    textbox_.editable(editable);
    textbox_.line_wrapped(line_wrapped);
    textbox_.multi_lines(multi_lines);
    textbox_.tip_string(tip);
	textbox_.text_align(nana::align::left);
  }

  void connect() {
    textbox_.events().text_changed(
        [this](nana::arg_textbox const& arg) { report_text_changed(arg); });
  }

  void layout() {
    place_.div(div_.c_str());
    place_["label"] << label_;
    place_["textbox"] << textbox_;
    place_.collocate();
  }

 public:
  labelbox(nana::window wd, std::string const& label,
               std::string const& tip = {}, bool editable = true,
               bool line_wrapped = false, bool multi_lines = false)
      : nana::panel<false>(wd) {
    setup(label, tip, editable, line_wrapped, multi_lines);
    layout();
	connect();
  }

  void connect(
      std::function<void(nana::arg_textbox const& arg)> report_text_changed) {
    report_text_changed_ = report_text_changed;
  }

  std::string text() const { return textbox_.caption(); }
  void text(std::string const& str) { textbox_.caption(str); }
};

#endif  // LABELBOX_H

#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class OutputFormat { MARK_DOWN, HTML };

struct ListStategy {
  virtual void start(ostringstream& oss) {};
  virtual void add_list_item(ostringstream& oss, const string& item) {}
  virtual void end(ostringstream& oss) {};
};

struct HtmlListStrategy : ListStategy {
  void start(ostringstream& oss) { oss << "<ul>" << endl; };
  void add_list_item(ostringstream& oss, const string& item) {
    oss << "<li> " << item << " </li>" << endl;
  }
  void end(ostringstream& oss) { oss << "</ul>" << endl; };
};

struct MarkdownListStrategy : ListStategy {
  void start(ostringstream& oss) {};
  void add_list_item(ostringstream& oss, const string& item) {
    oss << "* " << item << endl;
  }
  void end(ostringstream& oss) {};
};

namespace DynamicStrategy {

struct TextProcessor {
  void append_lists(const vector<string> items) {
    list_strategy->start(oss);
    for (auto& item : items) list_strategy->add_list_item(oss, item);
    list_strategy->end(oss);
  }
  void set_output_format(const OutputFormat format) {
    switch (format) {
      case OutputFormat::MARK_DOWN:
        list_strategy = make_unique<MarkdownListStrategy>();
        break;
      case OutputFormat::HTML:
        list_strategy = make_unique<HtmlListStrategy>();
        break;
    }
  }
  string str() const { return oss.str(); }
  void clear() {
    oss.str("");
    oss.clear();
  }

 private:
  ostringstream oss;
  unique_ptr<ListStategy> list_strategy;
};

void main() {
  cout << "[DynamicStrategy]" << endl;
  TextProcessor tp;
  tp.set_output_format(OutputFormat::MARK_DOWN);
  tp.append_lists({"foo", "bar", "baz"});
  cout << tp.str() << endl;
  tp.clear();
  cout << "========================= " << endl;
  tp.set_output_format(OutputFormat::HTML);
  tp.append_lists({"foo", "bar", "baz"});
  cout << tp.str() << endl;
  tp.clear();

  cout << endl;
}
};  // namespace DynamicStrategy

namespace StaticStrategy {

template <typename LS>
struct TextProcessor {
  void append_lists(const vector<string> items) {
    list_strategy.start(oss);
    for (auto& item : items) list_strategy.add_list_item(oss, item);
    list_strategy.end(oss);
  }
  string str() const { return oss.str(); }
  void clear() {
    oss.str("");
    oss.clear();
  }

 private:
  ostringstream oss;
  LS list_strategy;
};

void main() {
  cout << "[StaticStrategy]" << endl;

  TextProcessor<MarkdownListStrategy> tpm;
  tpm.append_lists({"foo", "bar", "baz"});
  cout << tpm.str() << endl;
  tpm.clear();
  cout << "========================= " << endl;
  TextProcessor<HtmlListStrategy> tph;
  tph.append_lists({"foo", "bar", "baz"});
  cout << tph.str() << endl;
  tph.clear();
  cout << endl;
}
};  // namespace StaticStrategy

int main(void) {
  DynamicStrategy::main();
  StaticStrategy::main();

  return 0;
}
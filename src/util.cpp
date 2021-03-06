#include "util.h"
#include "token.h"
#include <map>
#include <utility>

std::string uc::show_token_to_alcino(std::vector<Token> const& container) {
  std::map<unsigned, std::map<unsigned, std::string>> m_map;

  for (auto& token : container) {
    auto position                          = token.get_position();
    m_map[position.first][position.second] = token.to_string();
  }

  std::string out = "";
  for (auto& i : m_map) {
    for (auto& j : i.second) {
      out += j.second + " ";
    }
    out += "\n";
  }

  return out;
}

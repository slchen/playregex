#ifndef STDEXT_H
#define STDEXT_H

#include <iostream>

namespace std {
inline namespace acu {
inline namespace io {
inline namespace v1 {
// std::expact
template <char _Ch>
std::istream& expect(std::istream& _Is) {
  if ((_Is >> std::ws).peek() == _Ch) {
    _Is.ignore();
  } else {
    _Is.setstate(std::ios_base::failbit);
  }
  return _Is;
}
}  // namespace v1
}  // namespace io
}  // namespace acu
}  // namespace std

#endif  // STDEXT_H

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>

template <typename T, typename E>
struct Result {
  enum {
    Ok,
    Err
  } ty;
  T ok_value;
  E err_value;
};

namespace FailedReason {
  enum FailedReason{
    NotFound
  };
}

template <typename T>
Result<typename T::iterator, FailedReason::FailedReason> easyfind(T& container, int value) {
  Result<typename T::iterator, FailedReason::FailedReason> result;
  typename T::iterator it = std::find(container.begin(), container.end(), value);

  if (it != container.end()) {
    result.ty = Result<typename T::iterator, FailedReason::FailedReason>::Ok;
    result.ok_value = it;
  } else {
    result.ty = Result<typename T::iterator, FailedReason::FailedReason>::Err;
    result.err_value = FailedReason::NotFound;
  }
  return result;
}

#endif

#include "DummyService.h"

namespace Services {
  Result<std::string> DummyService::Init() {
    Result<std::string> result;
    result.SetStatus(StatusType::SUCCESS);
    return result;
  }
} //namespace Services
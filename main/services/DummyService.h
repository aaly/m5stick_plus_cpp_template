#ifndef _DUMMY_SERVICE
#define _DUMMY_SERVICE

#include "Service.h"
#include <string>

namespace Services {

    class DummyService : public Service{
        public:
            Result<std::string> Init() override;
    };

} //namespace Services

#endif //_DUMMY_SERVICE

#ifndef _BLUETOOTH_SERVICE
#define _BLUETOOTH_SERVICE

#include "Service.h"
#include <vector>
#include <string>

namespace Services {

    struct Connection {
        public:
            std::string name;
    };

    class BluetoothService : public Service{
        public:
            Result<std::string> Init() override;
            static Result<std::vector<Connection>> Scan();
    };

} //namespace Services

#endif //_BLUETOOTH_SERVICE

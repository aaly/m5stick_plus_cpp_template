#ifndef _SERVICEMANAGER_H_
#define _SERVICEMANAGER_H_

#include "Service.h"
#include "DummyService.h"
#include <memory>
#include <map>
#include <string>

namespace Services {
    class ServiceRegistery {
        public:

            /**
             * @brief get a singleton reference to ServiceRegistery
             * @return a reference to the singleton instance
             */
            static ServiceRegistery& GetInstance()
            {
                static ServiceRegistery instance; // Guaranteed to be destroyed.
                return instance;
            };

            /**
             * @brief register a service
             * @return Result with a status string in case of error
             */
            template<typename T>
            Result<std::string> RegisterService(const std::string& service) {
                Result<std::string> result;
                if (!_services.count(service)) {
                    _services[service] = std::shared_ptr<T>(new T);
                    _services[service]->SetName(service);
                    result = _services[service]->Init();
                }
                else {
                    result.SetData(std::string("Service name already exists"));
                }
                return result;
            };

            /**
             * @brief retrievev a service
             */
            Service& operator[](const std::string& service) {
                Service& result =  *_services["dummy"].get();
                if (_services.count(service)) {
                    result = *_services[service].get();
                }
                return result;
            };

        private:
            ServiceRegistery() {RegisterService<Services::DummyService>("dummy");};
            ServiceRegistery(ServiceRegistery const&);
            void operator=(ServiceRegistery const&);

            std::map<std::string, std::shared_ptr<Service>> _services;
    };
} //namespace Services

#endif //#ifndef _SERVICEMANAGER_H_
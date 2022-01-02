#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "../common.h"
#include <string>
#include <map>
#include <functional>
#include "cJSON.h"
#include <M5StickCPlus.h>

namespace Services {
    class Service {

        public:

            /**
             * @brief set the service name for debugging purposes...
             */
            void SetName(const std::string& name) {
                _name = name;
            };

            /**
             * @brief Initilization of the service
             * @return Result with a status string in case of error
             */
            virtual Result<std::string> Init() = 0;

            /**
             * @brief rerieve a callback function
             * a callback will be registered by the service, and it does send and receive json objects :s, 
             * this is not embedded anymore (or is it?)
             */
            std::function<Result<std::string>(const std::string&)> operator [](const std::string& method) {
                std::function<Result<std::string>(const std::string&)> result = [&](const std::string&) {
                    Serial.printf("Method [%s] not found for service [%s]\n", method.c_str(), _name.c_str());
                    Serial.flush();
                    return Result<std::string>();
                };

                if (_callbacks.count(method)) {
                    result = _callbacks[method];
                }
                
                return result;
            };

            /**
             * @brief add a callback to our callbacks map list
             */
            void AddCallback(const std::string& name, const std::function<Result<std::string>(const std::string&)> &f) {
                _callbacks[name] = f;
            };

        private:
            std::map<std::string, std::function<Result<std::string>(const std::string&)>> _callbacks;
            std::string _name;
    };
} //namespace Services

#endif //#ifndef
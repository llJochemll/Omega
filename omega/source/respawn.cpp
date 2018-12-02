#include "stdafx.hpp"
#include "respawn.hpp"
#include "common.hpp"
#include "global.hpp"

namespace omega {
    namespace respawn {
        std::vector<object> respawnQueue;

        void vehicles() {
            /*for (auto veh : common::allVehicles) {
                if (!bool(sqf::get_variable(veh, "omega_respawn", false))) return;
                if (std::find(respawnQueue.begin(), respawnQueue.end(), veh) != respawnQueue.end() || (sqf::alive(veh) && sqf::can_move(veh))) return;
                
                //Start respawn timer
                std::thread([=] {
                    EngineLock engineLock;
                    const auto delay = int(sqf::get_variable(veh, "omega_respawn_delay", 0));
                    const auto pos = sqf::get_variable(veh, "omega_respawn_position", vector3(0, 0, 0));
                    const auto type = sqf::type_of(veh);

                    sqf::side_chat(sqf::player(), "Delay: " + std::to_string(delay));

                    engineLock.unlock();
                    Sleep(delay * 1000);
                    engineLock.lock();

                    sqf::create_vehicle(type, pos);
                    sqf::set_variable(veh, "omega_respawn", true, true);
                    sqf::set_variable(veh, "omega_respawn_delay", delay, true);
                    sqf::set_variable(veh, "omega_respawn_position", pos, true);

                    respawnQueue.erase(respawnQueue.begin() + (std::find(respawnQueue.begin(), respawnQueue.end(), veh) - respawnQueue.begin()));
                }).detach();

                respawnQueue.push_back(veh);
                common::garbage.push_back(veh);
            }*/
        }
    }
}

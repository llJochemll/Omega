#include "stdafx.hpp"
#include "core.hpp"

bool missionRunning = false;

// Required exported function to return API version
int intercept::api_version() {
    return 1;
}

void intercept::mission_ended() {
    missionRunning = false;
}

void intercept::on_frame() {
    if (missionRunning) {
        omega::core::missionLoop();
    }
}

void intercept::post_init() {
    if (sqf::get_variable(sqf::mission_namespace(), "OmegaStart", false)) {
        omega::core::missionInit();
        missionRunning = true;
    }
}
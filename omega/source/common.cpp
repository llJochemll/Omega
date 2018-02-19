#include "stdafx.hpp"
#include "common.hpp"
#include <cmath>
#include <random>
#include "wrapper.hpp"

#define M_PI 3.14159265358979323846

namespace omega {
    namespace common {
        float distance(const vector3& pos1_, const vector3& pos2_) {
            return sqrt(pow(abs(pos1_.x - pos2_.x), 2.0f) + pow(abs(pos1_.y - pos2_.y), 2.0f));
        }

        vector3 findPos(const vector3& centre_, const vector3& radius_, const int size_, const int surfaceType_, const float objects_,
            const float maxGradient_, const int roads_) {
            vector3 pos;
            auto iter = 0;

            {
                vector3 posRad;
                auto suitable = true;

                while (iter < 10000) {
                    pos = randomPos(centre_, radius_);

                    iter++;

                    //Surface type
                    switch (surfaceType_) {
                    case 0:
                        for (size_t i = 0; i < size_; i++) {
                            suitable = true;
                            if (sqf::surface_is_water(randomPos(pos, vector3(size_, size_, 0)))) {
                                suitable = false;
                            }
                        }

                        if (!suitable) {
                            continue;
                        }
                        break;
                    case 1:
                        for (size_t i = 0; i < size_; i++) {
                            suitable = true;
                            if (!sqf::surface_is_water(randomPos(pos, vector3(size_, size_, 0)))) {
                                suitable = false;
                            }
                        }

                        if (!suitable) {
                            continue;
                        }
                        break;
                    default:
                        break;
                    }

                    if (maxGradient_ != -1) {
                        for (size_t i = 0; i < size_; i++) {
                            suitable = true;
                            auto area = vector3(size_, size_, 0);
                            if (sqf::surface_normal(randomPos(pos, area)).z < maxGradient_) {
                                suitable = false;
                            }
                        }

                        if (!suitable) {
                            continue;
                        }
                    }

                    if (roads_ != -1) {
                        auto roads = sqf::near_roads(pos, size_);
                        switch (roads_) {
                        case 0:
                            if (roads.empty()) {
                                continue;
                            }
                            break;
                        case 1:
                            if (!roads.empty()) {
                                continue;
                            }
                            break;
                        default:
                            break;
                        }
                    }

                    //Objects
                    if (wrapper::nearestObjects(pos, sqf_string_list_const_ref({}), size_, false, true).size() != 0) {
                        continue;
                    }

                    if (sqf::in_area(pos, "mrk_safezone")) {
                        continue;
                    }

                    break;
                }
            }

            return vector3(pos.x, pos.y, 0);
        }

        object nearestObject(const vector3& pos1_, const std::vector<object>& objects_, const float maxDamage_) {
            auto currentDistance = MAXINT32;
            object closest;

            for (auto& object : objects_) {
                if (sqf::damage(object) <= maxDamage_) {
                    const int dis = distance(sqf::get_pos(object), pos1_);
                    if (dis < currentDistance) {
                        currentDistance = dis;
                        closest = object;
                    }
                }
            }

            return closest;
        }

        int posRange(const vector3& pos_, const int distance_, const std::vector<vector3>& positions_) {
            auto count = 0;
            for (auto& pos : positions_) {
                if (distance(pos_, pos) <= distance_) {
                    count++;
                }
            }
            return count;
        }

        int randomInt(const int ceil_) {
            std::mt19937 rng(std::random_device{}());
            const std::uniform_int_distribution<> dist(0, ceil_);
            return dist(rng);
        }

        vector3 randomPos(const vector3& centre_, const vector3& radius_) {
            //TODO: take into account rotation (radius_.z)
            const auto dir = randomInt(359);
            auto pos = vector3((centre_.x) + (std::sin(dir) * (randomInt(static_cast<int>(radius_.x + 1)))),
                (centre_.y) + (std::cos(dir) * (randomInt(static_cast<int>(radius_.y + 1)))), 0);
            return pos;
        }

        vector3 rotate(const vector3& centre_, const vector3& pos_, const float degrees_) {
            const auto dist = distance(centre_, pos_);

            const float rotationDesiredRad = degrees_ * M_PI / 180.0f;
            auto rotationInitialRad = asin((pos_.x - centre_.x) / dist);

            if (pos_.y < centre_.y) {
                if (rotationInitialRad >= 0) {
                    rotationInitialRad = M_PI - rotationInitialRad;
                }
                else {
                    rotationInitialRad = -M_PI - rotationInitialRad;
                }
            }

            const auto rotationFinalRad = rotationInitialRad + rotationDesiredRad;

            return vector3(centre_.x + (sin(rotationFinalRad) * dist), centre_.y + (cos(rotationFinalRad) * dist), pos_.z);
        }

        vector3 worldCentre() {
            return vector3(sqf::world_size() / 2, sqf::world_size() / 2, 0);
        }

        vector3 worldSize() {
            return vector3(sqf::world_size() * 0.71, sqf::world_size() * 0.71, 0);
        }
    }
}

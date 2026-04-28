#ifndef MATERIALS_H
#define MATERIALS_H

#include <glm/fwd.hpp>
#include "glm/glm.hpp"

struct Material {
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    float shininess;
};

// 💎 Emerald
const Material emerald = {
    {0.0215f, 0.1745f, 0.0215f},
    {0.07568f, 0.61424f, 0.07568f},
    {0.633f, 0.727811f, 0.633f},
    7.68f
};

// 🔴 Ruby
const Material ruby = {
    {0.1745f, 0.01175f, 0.01175f},
    {0.61424f, 0.04136f, 0.04136f},
    {0.727811f, 0.626959f, 0.626959f},
    7.68f
};

// 🔵 Sapphire
const Material sapphire = {
    {0.0f, 0.1f, 0.2f},
    {0.0f, 0.4f, 0.8f},
    {0.9f, 0.9f, 1.0f},
    6.4f
};

// 🟡 Gold
const Material gold = {
    {0.24725f, 0.1995f, 0.0745f},
    {0.75164f, 0.60648f, 0.22648f},
    {0.628281f, 0.555802f, 0.366065f},
    5.12f
};

// ⚪ Silver
const Material silver = {
    {0.19225f, 0.19225f, 0.19225f},
    {0.50754f, 0.50754f, 0.50754f},
    {0.508273f, 0.508273f, 0.508273f},
    5.12f
};

// 🧊 Ice (very shiny, bluish)
const Material ice = {
    {0.1f, 0.1f, 0.2f},
    {0.6f, 0.7f, 0.9f},
    {0.9f, 0.95f, 1.0f},
    12.80f
};

// 🌑 Obsidian (dark glass)
const Material obsidian = {
    {0.05375f, 0.05f, 0.06625f},
    {0.18275f, 0.17f, 0.22525f},
    {0.332741f, 0.328634f, 0.346435f},
    30.84f
};

// 🧱 Plastic (red)
const Material plasticRed = {
    {0.0f, 0.0f, 0.0f},
    {0.5f, 0.0f, 0.0f},
    {0.7f, 0.6f, 0.6f},
    3.20f
};

// 🪵 Matte wood
const Material wood = {
    {0.2f, 0.1f, 0.05f},
    {0.4f, 0.2f, 0.1f},
    {0.04f, 0.04f, 0.04f},
    8.0f
};

// 🌌 Neon glow (fake bright)
const Material neonBlue = {
    {0.0f, 0.0f, 0.2f},
    {0.0f, 0.3f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    25.60f
};

const Material zero = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    0.0f
};

const Material checkFloor = {
    {0.1745f, 0.01175f, 0.01175f},
    {0.61424f, 0.04136f, 0.04136f},
    {0.727811f, 0.626959f, 0.626959f},
    0.5f
};

#endif //MATERIALS_H
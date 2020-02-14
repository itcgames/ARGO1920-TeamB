#include "Assets.h"
#include <iostream>

Assets::Assets() {}

Assets::~Assets() {
    for (auto tex : textures) {
        if (tex.second) {
            SDL_DestroyTexture(tex.second);
            tex.second = nullptr;
        }
    }
}

Assets& Assets::instance() {
    static std::unique_ptr<Assets> inst(new Assets());
    return *inst;
}

SDL_Texture* Assets::load_texture(const std::string& path, SDL_Renderer* ren) {
    auto already_loaded = textures.find(path);
    if (already_loaded != textures.end()) {
        return already_loaded->second;
    }

    auto surf = IMG_Load(path.c_str());
    if (!surf) {
        std::cerr << "ERROR: failed to load " << path << ": "
            << IMG_GetError() << "\n";
        return nullptr;
    }

    auto tex = SDL_CreateTextureFromSurface(ren, surf);
    if (!tex) {
        std::cerr << "ERROR: failed to create texture: "
            << SDL_GetError() << "\n";
    }

    textures.insert(std::pair<std::string, SDL_Texture*>(path, tex));

    return tex;
}
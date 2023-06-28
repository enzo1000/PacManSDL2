#include "Map.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include <fstream>
#include "ECS\ECS.hpp"
#include "ECS\Components.hpp"

extern Manager manager;

Map::Map(){
    
}

Map::~Map() {

}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    char tile;
    std::fstream mapFile;
    mapFile.open(path);

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            AddTile(atoi(&tile), x * 31, y * 31);
            mapFile.ignore();
        }
    }

    mapFile.ignore();

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            if (tile == '1')
            {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("wall", x * 31, y * 31, 31);
                tcol.addGroup(Game::groupColliders);
            }
            mapFile.ignore();
        }
    }

    mapFile.close();
}

void Map::AddTile(int id, int x, int y) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 31, 31, id);
    tile.addGroup(Game::groupMap);
}
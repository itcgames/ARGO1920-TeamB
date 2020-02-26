#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <SDL.h>
#include <iostream>
#include <map>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include "Assets.h"
typedef int gid;

// Stores information about an individual tile to be
// displayed.
struct tile {
    SDL_Texture* sheet;
    // x coordinate in the world
    int x;
    // y coordinate in the world
    int y;
    // the x coordinate on the sprite sheet
    int tx;
    // the y coordinate on the sprite sheet
    int ty;
    int width;
    int height;
    bool m_alive;

	bool alive = true;	
	tile();
    tile(SDL_Texture* tset, int x = 0, int y = 0,
        int tx = 0, int ty = 0, int w = 0, int h = 0,bool alive=true);
    void draw(SDL_Renderer* ren);
};

struct MazeWallObject : public tile
{
	int x;
	int y;
	int width;
	int height;
	bool alive;
	MazeWallObject(float x = 0, float y = 0, float width = 0, float height = 0,bool alive=true);
};
struct TeleportObject : public tile
{
	int x;
	int y;
	int width;
	int height;

	TeleportObject(float x = 0, float y = 0, float width = 0, float height = 0);
};
struct Breakable : public tile {
	int x;
	int y;
	int width;
	int height;
	bool alive;
	Breakable(float x = 0, float y = 0, float width = 0, float height = 0, bool alive = true);

};

struct Point {
	int x;
	int y;

	Point(float x = 0, float y = 0);

};
class Level
{
public:
    Level(const std::string& name);
    void load(const std::string& path, SDL_Renderer* ren);
    void draw(SDL_Renderer* ren);
	std::vector<tile> tiles;
	std::vector<tile> wallRubbleTiles;
	std::vector<MazeWallObject> m_mazeWalls;
	std::vector<MazeWallObject> m_outerBorders;
	std::vector<TeleportObject> m_teleport;
	std::vector<Point> m_cheese;
	std::vector<Point> m_bomb;
	std::vector<Point> m_player;
	std::vector<Point>m_spike;
private:
    std::string name;
    // Think of the dimensions as a 2D array (after all, that's what our
    // Tiled map is)
    // The rows variable is the number of tiles from top to bottom (Y axis).
    int rows;
    // The cols variable is the number of tiles from left to right (X axis).
    int cols;
    int tile_width;
    int tile_height;
    // All of the tiles we will draw to the screen.

    // All of the tilesets used by our Tiled map.
    std::map<gid, SDL_Texture*> tilesets;
};
#endif // !LEVEL_H


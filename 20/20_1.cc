#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define INPUT "input"

struct mapTile {
    int id;
    char mapData[10][10];
    bool connected;
    mapTile *n, *s, *e, *w;
};

void loadInput(std::set<mapTile*> &map) {
    std::fstream file;
    file.open(INPUT);

    std::string line;
    while (std::getline(file, line)) {
        int id;
        std::smatch sm;
        mapTile *tile = new mapTile;
        std::regex e("Tile (\\d+):");
        std::regex_match(line, sm, e);
        id = std::stoi(sm[1]);
        tile->id = id;
        for (int i = 0; i < 10; ++i) {
            std::getline(file, line);
            std::strncpy(tile->mapData[i], line.c_str(), 10);
        }
        tile->connected = false;
        tile->n = nullptr;
        tile->s = nullptr;
        tile->w = nullptr;
        tile->e = nullptr;
        map.insert(tile);
        // Blank line between map tiles.
        std::getline(file, line);
    }

    file.close();
}

void swap(char &a, char &b) {
    char temp = a;
    a = b;
    b = temp;
}

void flipHoriz(mapTile *tile) {
    for (int i = 0; i < 10; ++i) {
        int l = 0;
        int r = 9;
        while (l < r) {
            swap(tile->mapData[i][r], tile->mapData[i][l]);
            ++l;
            --r;
        }
    }
}

void flipVert(mapTile *tile) {
    for (int i = 0; i < 10; ++i) {
        int l = 0;
        int r = 9;
        while (l < r) {
            swap(tile->mapData[r][i], tile->mapData[l][i]);
            ++l;
            --r;
        }
    }

}

void rotate(mapTile *tile) {
    // First transpose
    for(int i = 0; i < 10; ++i) {
        for (int j = i; j < 10; ++j) {
            swap(tile->mapData[i][j], tile->mapData[j][i]);
        }
    }

    // Now flip horizontally
    flipHoriz(tile);
}

std::string getEdge(mapTile *tile, int e) {
    std::stringstream ss;
    switch(e) {
        case 0:
            for (int i = 0; i < 10; ++i) {
                ss << tile->mapData[0][i];
            }
            break;
        case 1:
            for (int i = 0; i < 10; ++i) {
                ss << tile->mapData[i][9];
            }
            break;
        case 2:
            for (int i = 0; i < 10; ++i) {
                ss << tile->mapData[9][i];
            }
            break;
        case 3:
            for (int i = 0; i < 10; ++i) {
                ss << tile->mapData[i][0];
            }
            break;
    }
    return ss.str();
}

mapTile* connectTile(mapTile *tile, const std::set<mapTile*> &map, \
        std::string edge, int e) {
    int ce;
    switch(e) {
        case 0:
            ce = 2;
            break;
        case 1:
            ce = 3;
            break;
        case 2:
            ce = 0;
            break;
        case 3:
            ce = 1;
            break;
    }

    for (auto const &t : map) {
        if (t->id == tile->id) {
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            if (getEdge(t, ce) == edge) {
                return t;
            }
            if (t->connected) {
                break;
            }
            flipHoriz(t);
            if (getEdge(t, ce) == edge) {
                return t;
            }
            flipHoriz(t);
            flipVert(t);
            if (getEdge(t, ce) == edge) {
                return t;
            }
            flipVert(t);
            rotate(t);
        }

    }

    return nullptr;
}

void buildMap(mapTile *tile, const std::set<mapTile*> &map, \
        std::vector<mapTile*> &cornerTiles) {
    if (tile->connected) {
        return;
    }
    tile->connected = true;

    int connections = 0;
    tile->n = connectTile(tile, map, getEdge(tile, 0), 0);
    if (tile->n != nullptr) {
        buildMap(tile->n, map, cornerTiles);
        ++connections;
    }
    tile->e = connectTile(tile, map, getEdge(tile, 1), 1);
    if (tile->e != nullptr) {
        buildMap(tile->e, map, cornerTiles);
        ++connections;
    }
    tile->s = connectTile(tile, map, getEdge(tile, 2), 2);
    if (tile->s != nullptr) {
        buildMap(tile->s, map, cornerTiles);
        ++connections;
    }
    tile->w = connectTile(tile, map, getEdge(tile, 3), 3);
    if (tile->w != nullptr) {
        buildMap(tile->w, map, cornerTiles);
        ++connections;
    }
    if (connections == 2) {
        cornerTiles.push_back(tile);
    }
}

int main() {
    std::set<mapTile*> map;
    std::vector<mapTile*> cornerTiles;
    
    loadInput(map);
   
    buildMap(*map.begin(), map, cornerTiles);

    long res = cornerTiles[0]->id;
    for (int i = 1; i < cornerTiles.size(); ++i) {
        res *= cornerTiles[i]->id;
    }
    std::cout << "Result: " << res << std::endl;

    for (auto const& tile : map) {
        delete tile;
    }

    return 0;
}

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

void buildImage(mapTile *tile, std::vector<std::vector<char> > &image) {
    // Find top left corner
    while (tile->n != nullptr) {
        tile = tile->n;
    }
    while (tile->w != nullptr) {
        tile = tile->w;
    }
    int curV = 0;
    while (tile != nullptr) {
        mapTile *cur = tile;

        for (int i = 0; i < 8; ++i) {
            image.push_back(std::vector<char>());
        }

        while (cur != nullptr) {
            for (int i = 1; i < 9; ++i) {
                for (int j = 1; j < 9; ++j) {
                    image[curV + i - 1].push_back(cur->mapData[i][j]);
                }
            }
            cur = cur->e;
        }
        curV += 8;
        tile = tile->s;
    }
}

void flipHoriz(std::vector<std::vector<char> > &image) {
    for (int i = 0; i < image.size(); ++i) {
        int l = 0;
        int r = image[0].size() - 1;
        while (l < r) {
            swap(image[i][r], image[i][l]);
            ++l;
            --r;
        }
    }
}

void flipVert(std::vector<std::vector<char> > &image) {
    for (int i = 0; i < image.size(); ++i) {
        int l = 0;
        int r = image[0].size() - 1;
        while (l < r) {
            swap(image[r][i], image[l][i]);
            ++l;
            --r;
        }
    }
}

void rotate(std::vector<std::vector<char> > &image) {
    // First transpose
    for(int i = 0; i < image.size(); ++i) {
        for (int j = i; j < image[0].size(); ++j) {
            swap(image[i][j], image[j][i]);
        }
    }
    // Now flip horizontally
    flipHoriz(image);
}

bool findMonster(std::vector<std::vector<char> > &image, \
        std::vector<std::vector<int> > monster) {
    bool found = false;
    for (int i = 0; i < image.size() - monster.size(); ++i) {
        for (int j = 0; j < image[0].size() - monster[0].size(); ++j) {
            for (int mi = 0; mi < monster.size(); ++mi) {
                for (int mj = 0; mj < monster[0].size(); ++mj) {
                    if (monster[mi][mj] == 1 && image[i + mi][j + mj] != '#') {
                        // I know...
                        goto notFound;
                    }
                }
            }
            // Found monster
            found = true;
            for (int mi = 0; mi < monster.size(); ++mi) {
                for (int mj = 0; mj < monster[0].size(); ++mj) {
                    if (monster[mi][mj] == 1) {
                         image[i + mi][j + mj] = 'O';
                    }
                }
            }
            notFound:
                continue;
        }
    }
    return found;
}

void transformImage(std::vector<std::vector<char> > &image, \
        std::vector<std::vector<int> > monster) {
    for (int i = 0; i < 4; ++i) {
        if (findMonster(image, monster)) {
            return;
        }
        flipHoriz(image);
        if (findMonster(image, monster)) {
            return;
        }
        flipHoriz(image);
        flipVert(image);
        if (findMonster(image, monster)) {
            return;
        }
        flipVert(image);
        rotate(image);
    }
}

void markMonsters(std::vector<std::vector<char> > &image) {
    /* 
     * Monster:
     * |                  # |
     * |#    ##    ##    ###|
     * | #  #  #  #  #  #   |
     */
    // Hard code monster mask
    std::vector<std::vector<int> > monster;
    monster.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0});
    monster.push_back({1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1});
    monster.push_back({0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0});

    transformImage(image, monster);
     
}

int countRoughWater(const std::vector<std::vector<char> > &image) {
    int c = 0;
    for (int i = 0; i < image.size(); ++i) {
        for (int j = 0; j < image[0].size(); ++j) {
            if (image[i][j] == '#') {
                ++c;
            }
        }
    }
    return c;
}

int main() {
    std::set<mapTile*> map;
    std::vector<mapTile*> cornerTiles;
    
    loadInput(map);
   
    buildMap(*map.begin(), map, cornerTiles);

    std::vector<std::vector<char> > image;
    buildImage(*map.begin(), image);
    markMonsters(image);

    int res = countRoughWater(image);
    std::cout << "Water roughness: " << res << std::endl;

    for (auto const& tile : map) {
        delete tile;
    }

    return 0;
}

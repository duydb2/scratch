/*
   Copyright (C) 2014 Preet Desai (preet.desai@gmail.com)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef SCRATCH_TILESET_LL_BYPIXELAREA_H
#define SCRATCH_TILESET_LL_BYPIXELAREA_H

#include <TileSetLL.h>

class TileSetLLByPixelArea : public TileSetLL
{
public:

    struct Options
    {
        // Initialize to sane defaults
        Options() :
            max_tiles(96),
            tile_sz_px(256),
            min_level(0),
            max_level(18),
            fix_level(1),
            preload_eval_level(2),
            max_adj_offset_dist2_m(1000000.0*1000000.0),
            min_eval_angle_degs(360.0/16.0)

        {}

        size_t max_tiles;
        size_t tile_sz_px;
        size_t min_level;
        size_t max_level;
        size_t fix_level;
        size_t preload_eval_level;
        double max_adj_offset_dist2_m;
        double min_eval_angle_degs;
    };

    TileSetLLByPixelArea(double view_width,
                         double view_height,
                         Options const &opts,
                         std::vector<RootTileDesc> const &list_root_tiles);

    ~TileSetLLByPixelArea();

    void UpdateTileSet(osg::Camera const * cam,
                       std::vector<uint64_t> &list_tiles_add,
                       std::vector<uint64_t> &list_tiles_upd,
                       std::vector<uint64_t> &list_tiles_rem);

    Tile const * GetTile(uint64_t tile_id) const;

private:

    struct Eval
    {
        Eval(Tile const * tile, double min_angle_degs);

        // Evaluation geometry
        // * to approximate pixel area taken up by tile
        std::vector<osg::Vec3d> list_vx;
        std::vector<uint16_t>   list_ix;
        std::vector<osg::Vec3d> list_tri_nx;
        std::vector<osg::Vec3d> list_quad_nx;
    };

    void buildTileSet(std::unique_ptr<Tile> &tile,
                      size_t &tile_count);

    void buildTileSetList(std::unique_ptr<Tile> const &tile,
                          std::map<uint64_t,Tile const *> &list_tiles);

    bool tilePxlAreaExceedsRes(Tile const * tile);
    double calcTileNDCArea(Eval const &evaldata) const;
    double calcTileNDCAreaQuad(Eval const &eval) const;

    // options
    Options const m_opts;
    double const m_tile_px_area;

    // view data
    double const m_view_width;
    double const m_view_height;
    osg::Matrixd m_mvp;
    osg::Vec3d m_view_dirn;

    // tiles
    std::vector<std::unique_ptr<Tile>> m_list_root_tiles;
    std::map<uint64_t,Tile const *> m_list_tileset;
    std::map<uint64_t,Eval> m_list_tile_eval;
    size_t m_tile_count;
};

#endif // SCRATCH_TILESET_LL_BYPIXELAREA_H

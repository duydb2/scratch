#include <DataSetTilesLL.h>
#include <TileImageSourceLL.h>
#include <TileVisibilityLLPixelsPerMeter.h>

#include <OSGUtils.h>
#include <osg/Texture2D>

namespace scratch
{
    DataSetTilesLL::DataSetTilesLL(osg::Group * gp_tiles) :
        m_gp_tiles(gp_tiles)
    {
        // TileDataSource

        // Create the TileLL::Id -> Image file path
        // generator function
        std::function<std::string(TileLL::Id)> image_path_gen =
                [](TileLL::Id id) -> std::string {

            uint8_t level;
            uint32_t x,y;
            TileLL::GetLevelXYFromId(id,level,x,y);

            std::string path =
                    "/home/preet/Dev/misc/tile_test/" +
                    std::to_string(level)+
                    ".png";

            return path;
        };

        std::unique_ptr<TileImageSourceLL> tile_data_source(
                    new TileImageSourceLL(
                        GeoBounds(-180,180,-90,90),
                        18,
                        1,
                        1,
                        image_path_gen,
                        2));


        // TileVisibility
        std::unique_ptr<TileVisibilityLLPixelsPerMeter> tile_visibility(
                    new TileVisibilityLLPixelsPerMeter(
                        640,
                        480,
                        256));


        // TileSet
        TileSetLL::Options options;
//        options.max_tile_data = 64;
        m_tileset.reset(new TileSetLL(std::move(tile_data_source),
                                      std::move(tile_visibility),
                                      options));

        // poly mode for wireframe tiles
        m_poly_mode = new osg::PolygonMode;
        m_poly_mode->setMode(osg::PolygonMode::FRONT_AND_BACK,
                             osg::PolygonMode::LINE);
    }

    DataSetTilesLL::~DataSetTilesLL()
    {

    }

    void DataSetTilesLL::Update(osg::Camera const * cam)
    {
        std::vector<TileLL::Id> list_tiles_add;
        std::vector<TileLL::Id> list_tiles_upd;
        std::vector<TileLL::Id> list_tiles_rem;
        m_tileset->UpdateTileSet(cam,
                                 list_tiles_add,
                                 list_tiles_upd,
                                 list_tiles_rem);

        // remove
        for(auto const tile_id : list_tiles_rem) {
            // Remove this tile from the scene and lookup
            auto it = m_lkup_sg_tiles.find(tile_id);
            assert(it != m_lkup_sg_tiles.end());

            m_gp_tiles->removeChild(it->second);
            m_lkup_sg_tiles.erase(tile_id);
        }

        // add
        for(auto tile_id : list_tiles_add) {
            // Add this tile to the scene and lookup
            auto it = m_lkup_sg_tiles.find(tile_id);
            assert(it == m_lkup_sg_tiles.end());

            // Get the tile
            TileSetLL::TileItem const * tile_item =
                    m_tileset->GetTile(tile_id);

            assert(tile_item);

            // Create scene graph data
            osg::ref_ptr<osg::Group> gp = createTileGm(tile_item);
//            applyTileTx(tile_item,gp.get());

            m_lkup_sg_tiles.insert(std::make_pair(tile_item->id,gp));
            m_gp_tiles->addChild(gp);
        }

    }

    osg::ref_ptr<osg::Group>
    DataSetTilesLL::createTileGm(TileSetLL::TileItem const * tile_item)
    {
        TileLL const * tile = tile_item->tile;

    //    uint32_t surf_divs = 256/K_LIST_TWO_EXP[tile->level];
    //    surf_divs = std::min(surf_divs,static_cast<uint32_t>(32));

    //    uint32_t const lon_segments =
    //            std::max(static_cast<uint32_t>(surf_divs),
    //                     static_cast<uint32_t>(1));

    //    uint32_t const lat_segments =
    //            std::max(static_cast<uint32_t>(lon_segments/2),
    //                     static_cast<uint32_t>(1));

        double const min_angle_degs = 360.0/32.0;
        uint32_t lon_segments = std::max((tile->bounds.maxLon-tile->bounds.minLon)/min_angle_degs,1.0);
        uint32_t lat_segments = std::max((tile->bounds.maxLat-tile->bounds.minLat)/min_angle_degs,1.0);

        std::vector<osg::Vec3d> list_vx;
        std::vector<osg::Vec2d> list_tx;
        std::vector<uint16_t> list_ix;
        BuildEarthSurface(tile->bounds.minLon,
                          tile->bounds.maxLon,
                          tile->bounds.minLat,
                          tile->bounds.maxLat,
                          lon_segments,
                          lat_segments,
                          list_vx,
                          list_tx,
                          list_ix);

        osg::ref_ptr<osg::Vec3dArray> vx_array = new osg::Vec3dArray;
        vx_array->reserve(list_vx.size());
        for(auto const &vx : list_vx) {
            vx_array->push_back(vx);
        }

        osg::ref_ptr<osg::Vec2dArray> tx_array = new osg::Vec2dArray;
        tx_array->reserve(list_tx.size());
        for(auto const &tx : list_tx) {
            tx_array->push_back(tx);
        }

        osg::ref_ptr<osg::Vec4Array>  cx_array = new osg::Vec4Array;
        cx_array->push_back(K_COLOR_TABLE[tile->level]);

        osg::ref_ptr<osg::DrawElementsUShort> ix_array =
                new osg::DrawElementsUShort(GL_TRIANGLES);
        ix_array->reserve(list_ix.size());
        for(auto ix : list_ix) {
            ix_array->push_back(ix);
        }

        osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;
        gm->setVertexArray(vx_array);
        gm->setTexCoordArray(0,tx_array,osg::Array::BIND_PER_VERTEX);
        gm->setTexCoordArray(1,tx_array,osg::Array::BIND_PER_VERTEX);
        gm->setColorArray(cx_array,osg::Array::BIND_OVERALL);
        gm->addPrimitiveSet(ix_array);

        osg::ref_ptr<osg::Geode> gd = new osg::Geode;
        gd->addDrawable(gm);
        gd->getOrCreateStateSet()->setRenderBinDetails(
                    -101+tile->level,"RenderBin");
        gd->getOrCreateStateSet()->setMode(
                    GL_CULL_FACE,
                    osg::StateAttribute::ON |
                    osg::StateAttribute::OVERRIDE);

        // polygon mode
        gd->getOrCreateStateSet()->setAttributeAndModes(
                    m_poly_mode,
                    osg::StateAttribute::ON);

        osg::ref_ptr<osg::Group> gp = new osg::Group;
        gp->addChild(gd);

        return gp;
    }

    void DataSetTilesLL::applyTileTx(TileSetLL::TileItem const * tile_item,
                                     osg::Group * gp)
    {
        // TileLL const * tile = tile_item->tile;

        TileImageSourceLL::ImageData const * data =
                static_cast<TileImageSourceLL::ImageData const*>(
                    tile_item->data);

        // create the texture
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
        texture->setImage(data->image);

        texture->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::LINEAR);
        texture->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::LINEAR);
        texture->setWrap(osg::Texture2D::WRAP_S,osg::Texture2D::CLAMP_TO_EDGE);
        texture->setWrap(osg::Texture2D::WRAP_T,osg::Texture2D::CLAMP_TO_EDGE);

        // create the texture coordinates (expect that
        // we have two sets of texture coordinates, and
        // the tex coords for unit 1 contain the 'full'
        // unsampled 1:1 coordinates for the tile)

        // TODO set sampled coordinates

        // get the geometry and apply the texture
        osg::Geode * gd = static_cast<osg::Geode*>(gp->getChild(0));
        gd->getOrCreateStateSet()->setTextureAttributeAndModes(0,texture);

        // osg::Geometry * gm = static_cast<osg::Geometry*>(gd->getDrawable(0));
    }
}

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

#include <thread>

#include <TileImageSourceLL.h>

#include <osgDB/ReadFile>

namespace scratch
{
    TileImageSourceLL::ImageData::~ImageData()
    {
        // empty
    }

    // ============================================================= //

    TileImageSourceLL::ImageRequest::ImageRequest(TileLL::Id id, std::string path) :
        TileDataSourceLL::Request(id),
        m_path(path)
    {
        // empty
    }

    TileImageSourceLL::ImageRequest::~ImageRequest()
    {
        // empty
        Cancel();
        Wait();
    }

    void TileImageSourceLL::ImageRequest::Cancel()
    {
        this->onCanceled();
    }

    void TileImageSourceLL::ImageRequest::process()
    {
        if(!this->IsCanceled()) {
            this->onStarted();
            m_data = std::make_shared<ImageData>();
            m_data->image = osgDB::readImageFile(m_path);
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            this->onFinished();
        }

        this->onEnded();
    }

    bool TileImageSourceLL::CanBeSampled() const
    {
        return true;
    }

    std::shared_ptr<TileDataSourceLL::Data>
    TileImageSourceLL::ImageRequest::GetData() const
    {
        return m_data;
    }

    // ============================================================= //

    TileImageSourceLL::TileImageSourceLL(GeoBounds const &bounds,
                                         uint8_t max_level,
                                         uint8_t num_root_tiles_x,
                                         uint8_t num_root_tiles_y,
                                         std::function<std::string(TileLL::Id)> path_gen,
                                         uint8_t num_threads) :
        TileDataSourceLL(bounds,
                         max_level,
                         num_root_tiles_x,
                         num_root_tiles_y),
        m_path_gen(std::move(path_gen)),
        m_thread_pool(num_threads)
    {
        // empty
    }

    TileImageSourceLL::~TileImageSourceLL()
    {
        // empty
    }

    void TileImageSourceLL::StartRequestBlock()
    {
        m_list_requests.clear();
    }

    void TileImageSourceLL::EndRequestBlock()
    {
        // TODO

        // PushFront(...) may load certain tiles out
        // of order (ie further away), but loads tiles
        // requested recently first. For slow load times,
        // PushFront is better

        // PushBack(...) loads tiles in the order they
        // are requested. As the number of requests accumulate,
        // the time taken to load the mostly recently requested
        // tiles increases substantially. However this method
        // doesn't load tiles out of order. For fast load times,
        // PushBack is better

        // We need to provide an option to choose
        m_thread_pool.PushFront(m_list_requests);
//        std::cout << "task_count: "
//                  << m_thread_pool.GetTaskCount() << std::endl;

//        std::string slist;
//        for(auto &req : m_list_requests) {
//            uint8_t level; uint32_t x; uint32_t y;
//            TileLL::GetLevelXYFromId(req->GetId(),level,x,y);
//            slist.append(std::to_string(level));
//            slist.append(" ");
//        }
//        std::cout << "#: req: " << slist << std::endl;
//        slist.clear();


//        auto list_ids = m_thread_pool.GetTaskIdList();
//        for(auto id : list_ids) {
//            uint8_t level; uint32_t x; uint32_t y;
//            TileLL::GetLevelXYFromId(id,level,x,y);
//            slist.append(std::to_string(level));
//            slist.append(" ");
//        }
//        std::cout << "#: tsk: " << slist << std::endl;


        m_list_requests.clear();
    }

    std::shared_ptr<TileDataSourceLL::Request>
    TileImageSourceLL::RequestData(TileLL::Id id)
    {
        std::shared_ptr<ImageRequest> request =
                std::make_shared<ImageRequest>(
                    id,m_path_gen(id));

        m_list_requests.push_back(request);
        return request;
    }



} // scratch

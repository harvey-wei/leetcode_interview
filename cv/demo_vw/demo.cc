#include <iostream>
#include <stack>
#include <vector>
#include <queue>


class Sensor
{
    public:
        Sensor(double _ts = 0.0) : ts(_ts) {}
        double ts;

};

class LiDAR : public Sensor
{
    public:
        LiDAR(double _ts = 0.0){ ts = _ts; }
};

class Camera : public Sensor
{
};

class MultiSensorMsg
{
    public:
        std::vector<Sensor*> fuse_sensor(std::vector<std::vector<Sensor>> multi_sensors)
        {
            std::vector<Sensor*> fuse;

            std::vector<Sensor*> curr_sensors(multi_sensors.size(), nullptr);

            /* Sensor* curr_lidar = nullptr; */
            /* Sensor* curr_camera = nullptr; */

            /* while (!lidar_queue.empty() && !camera_queue.empty()) */
            while (true)
            {
                bool is_all_empty = true;
                for (const auto& sensor_queue : multi_sensors)
                {
                    if (!sensor_queue.empty()) is_all_empty = false;
                }

                if (is_all_empty) break;

                for (int i = 0; i < multi_sensors.size(); ++i)
                {

                }

                curr_lidar = lidar_queue.front();
                curr_camera = camera_queue.front();

                if (curr_lidar->ts < curr_camera->ts)
                {
                    fuse.push_back(curr_lidar);
                    lidar_queue.pop();
                }
                else
                {
                    fuse.push_back(curr_camera);
                    camera_queue.pop();
                }
            }


            // Push remaining lidar XOR camera msg
            /* while (!lidar_queue.empty()) */
            /* { */
            /*     curr_lidar = lidar_queue.front(); */
            /*     lidar_queue.pop(); */
            /**/
            /*     fuse.push_back(curr_lidar); */
            /* } */
            /**/
            /* while (!camera_queue.empty()) */
            /* { */
            /*     curr_camera = camera_queue.front(); */
            /*     camera_queue.pop(); */
            /*     fuse.push_back(curr_camera); */
            /* } */

            // reverse ?

            return fuse;
        }
        std::vector<Sensor*> fuse_sensor(std::queue<LiDAR*>& lidar_queue, std::queue<Camera*>&
                camera_queue)
        {
            std::vector<Sensor*> fuse;

            Sensor* curr_lidar = nullptr;
            Sensor* curr_camera = nullptr;

            while (!lidar_queue.empty() && !camera_queue.empty())
            {
                curr_lidar = lidar_queue.front();
                curr_camera = camera_queue.front();

                if (curr_lidar->ts < curr_camera->ts)
                {
                    fuse.push_back(curr_lidar);
                    lidar_queue.pop();
                }
                else
                {
                    fuse.push_back(curr_camera);
                    camera_queue.pop();
                }
            }


            // Push remaining lidar XOR camera msg
            while (!lidar_queue.empty())
            {
                curr_lidar = lidar_queue.front();
                lidar_queue.pop();

                fuse.push_back(curr_lidar);
            }

            while (!camera_queue.empty())
            {
                curr_camera = camera_queue.front();
                camera_queue.pop();
                fuse.push_back(curr_camera);
            }

            // reverse ?

            return fuse;
        }

    private:
        /* std::queue<LiDAR*> lidar_queue; */
        /* std::queue<Camera*> camera_queue; */
};


int main()
{
    std::queue<LiDAR*> lidar_queue;
    std::queue<Camera*> camera_queue;

    LiDAR* l1 = new LiDAR;
    LiDAR* l2 = new LiDAR;
    LiDAR* l3 = new LiDAR;
    LiDAR* l4 = new LiDAR(0.1);
    l1->ts = 0.1;
    l2->ts = 0.2;
    l3->ts = 0.3;
    l4->ts = 0.4;


    Camera* c1 = new Camera;
    c1->ts = 0.19;


    lidar_queue.push(l1);
    lidar_queue.push(l2);
    lidar_queue.push(l3);
    lidar_queue.push(l4);

    camera_queue.push(c1);


    MultiSensorMsg msm = MultiSensorMsg();

    std::vector<Sensor*> fuse = msm.fuse_sensor(lidar_queue, camera_queue);



    delete l1;
    delete l2;
    delete l3;
    delete l4;

    delete c1;

    return 0;
}

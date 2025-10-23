#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

class TurtleWriter : public rclcpp::Node
{
public:
    TurtleWriter() : Node("turtle_writer")
    {
        teleporter_ = this->create_client<turtlesim::srv::TeleportAbsolute>("/turtle1/teleport_absolute");
        pen_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");

        // Lalu mulai menulis
        draw_name();
    }

    void draw_name()
    {
        int cnt=1;
        while(cnt<=6){
            set_pen(false);  // matikan pena saat pindah ke posisi awal

            switch (cnt)
            {
            case 1:
                RCLCPP_INFO(this->get_logger(), "Menulis huruf R...");

                move_to(2.0, 2.0, 0.0);
                set_pen(true);  // aktifkan pena dengan warna putih

                move_to(2.0, 6.0, 0.0); // garis vertikal
                move_to(4.0, 6.0, 0.0); // atas
                move_to(4.0, 4.0, 0.0); // ke bawah
                move_to(2.0, 4.0, 0.0); // kiri
                move_to(4.0, 2.0, 0.0); // diagonal
                set_pen(false);

                RCLCPP_INFO(this->get_logger(), "Huruf R selesai!");
                break;
            case 2:
                RCLCPP_INFO(this->get_logger(), "Menulis huruf E...");
                move_to(5.0, 2.0, 0.0);
                set_pen(true);  // aktifkan pena dengan warna putih

                move_to(5.0, 6.0, 0.0); // garis vertikal
                move_to(7.0, 6.0, 0.0); // kanan
                set_pen(false);
                move_to(5.0, 4.0, 0.0); // pindah tengah
                set_pen(true);
                move_to(7.0, 4.0, 0.0); // kanan
                set_pen(false);
                move_to(5.0, 2.0, 0.0); // pindah bawah
                set_pen(true);
                move_to(7.0, 2.0, 0.0); // kanan
                set_pen(false);

                RCLCPP_INFO(this->get_logger(), "Huruf E selesai!");
                break;
            case 3:
                RCLCPP_INFO(this->get_logger(), "Menulis huruf N...");
                move_to(8.0, 2.0, 0.0);
                set_pen(true);  // aktifkan pena dengan warna putih

                move_to(8.0, 6.0, 0.0); // garis vertikal
                move_to(10.0, 2.0, 0.0); // diagonal bawah
                move_to(10.0, 6.0, 0.0); // vertikal
                set_pen(false);

                RCLCPP_INFO(this->get_logger(), "Huruf N selesai!");
                break;
            case 4:
                RCLCPP_INFO(this->get_logger(), "Menulis huruf D...");
                move_to(11.0, 2.0, 0.0);
                set_pen(true);  // aktifkan pena dengan warna putih

                move_to(11.0, 6.0, 0.0); // garis vertikal
                move_to(13.0, 5.0, 0.0); // diagonal bawah kanan
                move_to(13.0, 3.0, 0.0); // diagonal bawah
                move_to(11.0, 2.0, 0.0); // diagonal bawah kiri
                set_pen(false);

                RCLCPP_INFO(this->get_logger(), "Huruf D selesai!");
                break;
            case 5:
                RCLCPP_INFO(this->get_logger(), "Menulis huruf R...");
                move_to(14.0, 2.0, 0.0);
                set_pen(true);  // aktifkan pena dengan warna putih

                move_to(14.0, 6.0, 0.0); // garis vertikal
                move_to(16.0, 6.0, 0.0); // atas
                move_to(16.0, 4.0, 0.0); // ke bawah
                move_to(14.0, 4.0, 0.0); // kiri
                move_to(16.0, 2.0, 0.0); // diagonal
                set_pen(false);

                RCLCPP_INFO(this->get_logger(), "Huruf R selesai!");
                break;
            case 6:
                RCLCPP_INFO(this->get_logger(), "Menulis huruf A...");
                move_to(17.0, 2.0, 0.0);
                set_pen(true);  // aktifkan pena dengan warna putih

                move_to(17.0, 6.0, 0.0); // garis vertikal
                move_to(19.0, 6.0, 0.0); // kanan
                move_to(19.0, 4.0, 0.0); // ke bawah
                move_to(17.0, 4.0, 0.0); // kiri
                set_pen(false);
                move_to(19.0, 4.0, 0.0); // balik ke tengah
                set_pen(true);
                move_to(19.0, 2.0, 0.0); // bawah

                RCLCPP_INFO(this->get_logger(), "Huruf A selesai!");
                break;
            default:
                break;
            }
            
            cnt++;
        }
        set_pen(false);  // matikan pena saat pindah ke posisi awal
    }

private:
    void move_to(float x, float y, float theta)
    {
        const int scale = 2;
        auto req = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();
        req->x = x/scale;
        req->y = y/scale;
        req->theta = theta/scale;

        teleporter_->wait_for_service();
        teleporter_->async_send_request(req);
        std::this_thread::sleep_for(300ms);
    }

    void set_pen(bool on)
    {
        auto req = std::make_shared<turtlesim::srv::SetPen::Request>();
        if (on)
        {
            req->r = 255;  // merah penuh
            req->g = 255;  // hijau penuh
            req->b = 255;  // biru penuh
            req->width = 3;
            req->off = 0;  // aktifkan pena
        }
        else
        {
            req->off = 1;  // matikan pena
        }

        pen_->wait_for_service();
        pen_->async_send_request(req);
    }

    rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr teleporter_;
    rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr pen_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TurtleWriter>());
    rclcpp::shutdown();
    return 0;
}

#include <cmath>
#include <opencv2/opencv.hpp>
#include "nodes/graphics/scene.h"
using namespace cv;

class ShadowScene : public Scene
{
public:
    QString name() { return "Shadow"; }
    Rect pos;
    Image imageShadow;
    Color backColor;

    int blur_size;
    int erosion_size;
    int dilation_size;

    bool is_self_shadow;
    Color self_shadow_color;

    bool is_move_shadow;
    Color move_shadow_color;
    int inclination_deg;
    int move_max_moving;
    int move_self_threshold;
    int move_max_threshold;
    int move_turn_threshold;
    int move_merge_threshold;

    double move_speed;
    double move_inclination_speed;

    int move_turning_time;

    float _move_shadow_dx;
    float _move_shadow_speed;
    int _move_turn_time_start;
    bool _move_is_reverse;
    bool _move_is_turning;


    ShadowScene()
    {
        addControlGroup("Main");
        addControl(backColor=Color(1, 1, 1, 0.2f), "Background");

        addControlGroup("Shadow");
        addControl(blur_size=7, "Blur size", 0, 50);
        addControl(erosion_size=1, "Erosion size", 0, 50);
        addControl(dilation_size=1, "Dilation size", 0, 50);

        addControlGroup("Self Shadow");
        addControl(is_self_shadow=true, "On");
        addControl(self_shadow_color = Color(0, 0, 0, 1), "Color");

        addControlGroup("Move Shadow");
        addControl(is_move_shadow=true, "On");
        addControl(move_shadow_color = Color(0, 0, 0, 1), "Color Self");
        addControl(inclination_deg=15, "Min Inclination", 0, 90);
        addControl(move_max_moving=100, "Max moving", 0, 1000);
        addControl(move_self_threshold=5, "Self threshold", 0, 100);
        addControl(move_max_threshold=5, "Max threshold", 0, 100);
        addControl(move_turn_threshold=10, "Turn threshold", 0, 100);
        addControl(move_merge_threshold=5, "Merge threshold", 0, 100);

        addControl(move_speed=3, "Move speed", 0, 1000, 2);
        addControl(move_inclination_speed=5, "Move inclination speed", 0, 1000, 2);

        addControl(move_turning_time=500, "Turning time", 1, 10000);

        _move_shadow_dx = 0;
        _move_shadow_speed = 0;
        _move_turn_time_start = 0;
        _move_is_reverse = false;
        _move_is_turning = false;
    }

    virtual void paint()
    {
        if (input("hit")->mat.empty())
            return;

        prepareShadow();

        size(320, 240);
        background(backColor);

        if (is_self_shadow)
            selfShadow();
        if (is_move_shadow)
            moveShadow();
    }

    void prepareShadow() {
        Mat &hit = input("hit")->mat;
        Mat erode_element =
                cv::getStructuringElement(cv::MORPH_RECT,
                                          Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                          Point( erosion_size, erosion_size ));
        Mat dilate_element =
                cv::getStructuringElement(cv::MORPH_RECT,
                                          Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                          Point( dilation_size, dilation_size ));

        Mat depth_erode;
        Mat depth_dilate;
        Mat depth_big;
        cv::erode(hit, depth_erode, erode_element);
        cv::dilate(depth_erode, depth_dilate, dilate_element);
        cv::resize(depth_dilate, depth_big, Size(960, 720), 0, 0, INTER_CUBIC);
        if (blur_size > 0) {
            Mat depth_blur;
            cv::blur(depth_big, depth_blur, cv::Size(blur_size, blur_size));
            imageShadow.set(depth_blur);
        }
        else {
            imageShadow.set(depth_big);
        }
    }

    void drawShadow(float x, float y, bool reverse=false) {
        Rect pos = input("rect")->rect;
        if (reverse)
            imageShadow.setReverse(ReverseType::Horizontal);
        else
            imageShadow.setReverse(ReverseType::None);

        draw(&imageShadow, pos.x + x, pos.y + y, pos.width, pos.height);
    }

    void selfShadow() {
        color(self_shadow_color);
        drawShadow(0, 0);
    }

    void moveShadow() {
        Human &human = input("human1")->human;

        float a = angle(human.spine.x, human.spine.y,
                        human.shoulderCenter.x, human.shoulderCenter.y) * 180 / pi() - 90;
        float ca = abs(a) / 90.0f;
        float dx = 0;
        float dx_abs = abs(_move_shadow_dx);

        float x_max = move_max_moving;
        float t_self = move_self_threshold*x_max/100.0f;
        float t_max = x_max - move_max_threshold*x_max/100.0f;
        float t_turn = move_turn_threshold*x_max/100.0f;
        float t_merge = move_merge_threshold*x_max/100.0f;

        int direction = 0;


        bool isInclination = false;
        if (a > inclination_deg) {
            direction = -1;
            isInclination = true;
        }
        else if (a < -inclination_deg) {
            direction = +1;
            isInclination = true;
        }
        else {
            if (_move_shadow_dx > 0)
                direction = +1;
            else if (_move_shadow_dx < 0)
                direction = -1;

            if (dx_abs < t_merge) {
                direction = -direction;
                dx += move_speed / 2;
            }
        }

        if (isInclination) {
            if (dx_abs < t_self) {
                float s = abs(_move_shadow_dx);
                float cs = s / t_self;
                float v_max = move_speed;
                dx += cs * cs * v_max;
            }
            else if (dx_abs > t_max) {
                float s = x_max - abs(_move_shadow_dx);
                float cs = s / t_max;
                float v = move_speed + move_inclination_speed;
                dx += cs * cs * v;
            }
            else {
                dx += move_speed;
            }

            dx += ca*move_inclination_speed;
        }

        _move_shadow_dx += dx*direction;

        if (_move_shadow_dx > x_max)
            _move_shadow_dx = x_max;
        else if (_move_shadow_dx < -x_max)
            _move_shadow_dx = -x_max;

        if (dx_abs > t_turn && !_move_is_reverse) {
            _move_is_reverse = true;

            if (!_move_is_turning) {
                _move_is_turning = true;
                _move_turn_time_start = time();
            }
        }
        else if (dx_abs < t_turn && _move_is_reverse && !isInclination) {
            _move_is_reverse = false;
            if (!_move_is_turning) {
                _move_is_turning = true;
                _move_turn_time_start = time();
            }
        }

        if (_move_is_turning && _move_turn_time_start + move_turning_time < time()) {
            _move_is_turning = false;
        }

        if (_move_is_turning) {
            float dt = float(time() - _move_turn_time_start) / float(move_turning_time);

            float dt_no_rev = 1 - dt;
            float dt_rev = dt;
            if (_move_is_reverse) {
                dt_no_rev = 1 - dt;
                dt_rev = dt;
            }
            color(move_shadow_color.r, move_shadow_color.g, move_shadow_color.b, dt_no_rev);
            drawShadow(_move_shadow_dx, 0, !_move_is_reverse);

            color(move_shadow_color.r, move_shadow_color.g, move_shadow_color.b, dt_rev);
            drawShadow(_move_shadow_dx, 0, _move_is_reverse);
        }
        else {
            color(move_shadow_color);
            drawShadow(_move_shadow_dx, 0, _move_is_reverse);
        }
    }

};

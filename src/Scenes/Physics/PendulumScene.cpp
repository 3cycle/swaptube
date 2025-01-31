#pragma once
#include "../../DataObjects/Pendulum.cpp"
#include "../Scene.cpp"

class PendulumScene : public Scene {
public:
    PendulumScene(PendulumState s, const double width = 1, const double height = 1) : Scene(width, height), start_state(s), pend(s), path_background(get_width(), get_height()) { }

    const StateQuery populate_state_query() const override {
        return StateQuery{"angles_opacity", "path_opacity", "t", "physics_multiplier", "rk4_step_size", "pendulum_opacity", "background_opacity"};
    }

    void on_end_transition() override {}
    void mark_data_unchanged() override { pend.mark_unchanged(); }
    void change_data() override { pend.iterate_physics(state["physics_multiplier"], state["rk4_step_size"]); }
    bool check_if_data_changed() const override { return pend.has_been_updated_since_last_scene_query(); }
    unordered_map<string, double> stage_publish_to_global() const override {
        return unordered_map<string, double> {
            {"pendulum_theta1", pend.state.theta1},
            {"pendulum_theta2", pend.state.theta2},
        };
    }

    void draw() override {
        double w = get_width(); double h = get_height();
        double line_thickness = h/80;
        double posx = w/2; double posy = h/2;
        vector<double> thetas = {pend.state.theta1, pend.state.theta2};
        int pendulum_count = 2;
        int color = YUVtoRGB(map_to_torus(thetas[0], thetas[1]));
        if(state["background_opacity"] > 0.01)
            pix.fill(colorlerp(TRANSPARENT_BLACK, color, state["background_opacity"]));

        bool positive;
        if(state["pendulum_opacity"] > 0.01) {
            int pendulum_color = colorlerp(TRANSPARENT_BLACK, color, state["pendulum_opacity"]);
            for (int i = 0; i < pendulum_count; i++) {
                double theta = thetas[i];
                double length = h/(pendulum_count * 2 + 1.);
                double dx = sin(theta) * length; double dy = cos(theta) * length;
                pix.fill_circle(posx, posy, line_thickness * 2, pendulum_color);
                pix.bresenham(posx, posy, posx + dx, posy + dy, pendulum_color, 1, line_thickness);
                double ao = state["angles_opacity"];
                if(ao > 0.01){
                    double theta_modified = theta+199*M_PI;
                    theta_modified -= static_cast<int>(theta_modified/(2*M_PI))*2*M_PI + M_PI;
                    pix.bresenham(posx, posy, posx, posy + length, OPAQUE_WHITE, ao, .5*line_thickness);
                    for(double angle = 0; angle < 1; angle+=.01) {
                        pix.overlay_pixel(posx + sin(angle*theta_modified)*length*.5, posy + cos(angle*theta_modified)*length*.5, OPAQUE_WHITE, ao);
                    }
                }
                posx += dx; posy += dy;
            }
            positive = posx > w / 2.;
            pix.fill_circle(posx, posy, line_thickness*2, pendulum_color);
        }
        if(positive != last_positive) generate_beep(0.2);
        last_positive = positive;
        if(state["path_opacity"] > 0.01 && (last_posx != 0 || last_posy != 0)) {
            path_background.bresenham(last_posx, last_posy, posx, posy, OPAQUE_WHITE, state["path_opacity"], line_thickness/4.);
            pix.underlay(path_background, 0, 0);
        }
        last_posx = posx; last_posy = posy;
        for(int x = 0; x < path_background.w; x++) {
            for(int y = 0; y < path_background.h; y++) {
                int alpha = geta(path_background.get_pixel(x, y));
                alpha = alpha==0?0:alpha-1;
                path_background.set_pixel(x, y, argb_to_col(alpha, 255, 255, 255));
            }
        }
    }

    void generate_beep(double duration){
        vector<float> left;
        vector<float> right;
        int total_samples = duration*44100;
        for(int i = 0; i < duration*44100; i++){
            double pct_complete = i/static_cast<double>(total_samples);
            float val = .03*sin(i*2200./44100.);// + .08*sin(i*1800./44100.);
            val *= pow(.5, 4*pct_complete);
            left.push_back(val);
            right.push_back(val);
        }
        WRITER.add_sfx(left, right, state["t"]);
    }

    void generate_audio(double duration, vector<float>& left, vector<float>& right){
        PendulumState ps = start_state;
        for(int i = 0; i < duration*44100; i++){
            for(int j = 0; j < 10; j++) {
                ps = rk4Step(ps, 0.003);
            }
            left.push_back(.1*sin(ps.theta1));
            right.push_back(.1*sin(ps.theta2));
        }
    }

private:
    double last_posx; double last_posy;
    PendulumState start_state;
    Pendulum pend;
    bool last_positive = true;
    Pixels path_background;
};

using namespace std;
#include <string>
const string project_name = "Orbits";
#include "../io/PathManager.cpp"
const int width_base = 640;
const int height_base = 360;
const int mult = 1;

// PROJECT GLOBALS
const int VIDEO_WIDTH = width_base * mult;
const int VIDEO_HEIGHT = height_base * mult;
const int VIDEO_FRAMERATE = 30;

#include "../io/writer.cpp"

#include "../Scenes/Physics/OrbitScene2D.cpp"
#include "../Scenes/Media/DagLatexScene.cpp"
#include "../Scenes/Common/CompositeScene.cpp"
#include "../misc/Timer.cpp"
#include "../misc/ColorScheme.cpp"

extern void run_cuda_test();

void render_video() {
    ColorScheme cs = get_color_schemes()[6];
    OrbitSim sim;
    OrbitScene2D scene(&sim);
    CompositeScene comp;
    comp.add_scene(&scene, "orbit2d_s", 0, 0, 1, 1, true); 

    sim.add_fixed_object(cs.get_color(), 1, "planet1");
    scene.state_manager->add_equations(unordered_map<string, string>{
        {"planet1.x", "-.3"},
        {"planet1.y", "-.3"},
        {"planet1.z", "0"}
    });
    sim.add_fixed_object(cs.get_color(), 1, "planet2");
    scene.state_manager->add_equations(unordered_map<string, string>{
        {"planet2.x", "0.3171"},
        {"planet2.y", "0.3"},
        {"planet2.z", "0"}
    });
    /*
    sim.add_fixed_object(cs.get_color(), 1, "planet3");
    scene.state_manager->add_equations(unordered_map<string, string>{
        {"planet3.x", "-.4"},
        {"planet3.y", "0.3"},
        {"planet3.z", "0"}
    });
    */

    scene.state_manager->add_equations(unordered_map<string, string>{
        {"force_constant", "0.000001"},
        {"collision_threshold", "0.055"},
        {"drag", "0.9997"},
        {"drag_display", "1 <drag> -"},
        {"zoom", "0.5"},
        {"screen_center_x", "0"},
        {"screen_center_y", "0"},
        {"screen_center_z", "0"},
    });

    int latex_col = cs.get_color();
    DagLatexScene fc  ("force_constant"     , "Force" , latex_col);
    DagLatexScene drag("drag_display"       , "Drag"  , latex_col);
    comp.add_scene(&fc,     "fc_s", 0, .9, 1, .1, true); 
    comp.add_scene(&drag, "drag_s", 0, .8, 1, .1, true); 
    scene.physics_multiplier = 1;

    /*
    scene.inject_audio_and_render(AudioSegment(.1));
    sim.mobile_interactions = false;
    double delta = 0.02;
    int bounds = 2;
    for(double x = -bounds; x < bounds; x+=delta) for(double y = -bounds; y < bounds; y+=delta){
        glm::vec3 pos(x,y,0);
        int color = sim.predict_fate_of_object(pos, scene.state_manager);
        sim.add_mobile_object(pos, color, 1);
    }
    */
    /*
    scene.state_manager.add_transitions(unordered_map<string, string>{
        {"planet2.x", "0.3"},
        {"planet2.y", "-.3"},
        {"planet2.z", "0"}
    });
    */

    scene.state_manager->add_transitions(unordered_map<string, string>{
        {"drag", "0.9998"},
        {"screen_center_y", ".6"},
    });
    comp.inject_audio_and_render(AudioSegment(3));
    scene.state_manager->add_transitions(unordered_map<string, string>{
        {"screen_center_x", "<t> cos 40 /"},
        {"screen_center_y", "<t> sin 40 / .6 +"},
        {"zoom", "20"}
    });
    comp.inject_audio_and_render(AudioSegment(3));
    comp.inject_audio_and_render(AudioSegment(3));
}
int main() {
    Timer timer;
    render_video();
    timer.stop_timer();
    return 0;
}
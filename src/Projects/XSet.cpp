using namespace std;
#include <string>
const string project_name = "XSet";
const int width_base = 640;
const int height_base = 360;
const float mult = 2;

// PROJECT GLOBALS
const int VIDEO_WIDTH = width_base * mult;
const int VIDEO_HEIGHT = height_base * mult;
const int VIDEO_FRAMERATE = 30;

#include "../io/writer.cpp"
#include "../misc/Timer.cpp"

#include "../Scenes/Common/CompositeScene.cpp"
#include "../Scenes/Media/StateSliderScene.cpp"
#include "../Scenes/Media/LatexScene.cpp"
#include "../Scenes/Media/PngScene.cpp"
#include "../Scenes/Math/MandelbrotScene.cpp"
#include "../Scenes/Common/TwoswapScene.cpp"
#include "../Scenes/Common/ExposedPixelsScene.cpp"

void intro() {
    FOR_REAL = false;
    CompositeScene cs;
    MandelbrotScene ms;
    cs.add_scene(&ms, "ms");
    unordered_map<string,string> init = {
        {"zoom_r", "2 <zoom_exp> ^"},
        {"zoom_exp", "0"},
        {"zoom_i", "0"},
        {"max_iterations", "50"},//TODO change to 600
        {"seed_z_r", "0"},
        {"seed_z_i", "0"},
        {"seed_x_r", "2"},
        {"seed_x_i", "0"},
        {"seed_c_r", "0"},
        {"seed_c_i", "0"},
        {"pixel_param_z", "0"},
        {"pixel_param_x", "0"},
        {"pixel_param_c", "1"},
        {"side_panel", "0"},
        {"point_path_r", "0"},
        {"point_path_i", "0"},
        {"point_path_length", "0"},
    };
    ms.state_manager.set(unordered_map<string,string>{
        {"zoom_r", "[zoom_r]"},
        {"zoom_i", "[zoom_i]"},
        {"max_iterations", "[max_iterations]"},//TODO change to 600
        {"seed_z_r", "[seed_z_r]"},
        {"seed_z_i", "[seed_z_i]"},
        {"seed_x_r", "[seed_x_r]"},
        {"seed_x_i", "[seed_x_i]"},
        {"seed_c_r", "[seed_c_r]"},
        {"seed_c_i", "[seed_c_i]"},
        {"pixel_param_z", "[pixel_param_z]"},
        {"pixel_param_x", "[pixel_param_x]"},
        {"pixel_param_c", "[pixel_param_c]"},
        {"side_panel", "[side_panel]"},
        {"point_path_length", "[point_path_length]"},
        {"point_path_r", "[point_path_r]"},
        {"point_path_i", "[point_path_i]"},
    });
    cs.state_manager.set(init);

    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_c_r", "-.4621603"},
        {"seed_c_i", "-.5823998"},
    });
    cs.inject_audio_and_render(AudioSegment("This is the mandelbrot set."));
    // Zoom in on an interesting spot with a minibrot
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"zoom_exp", "-9"},
    });
    cs.inject_audio_and_render(AudioSegment("Known for its beauty at all resolutions and scales,"));
    cs.inject_audio_and_render(AudioSegment("and stunning self-similarity,"));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"zoom_exp", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("it is the cornerstone example of a fractal."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"pixel_param_z", "1"},
        {"pixel_param_x", "0"},
        {"pixel_param_c", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("What's more, if we just change our perspective, or, rather, spin our viewpanel through the fourth dimension,"));
    cs.inject_audio_and_render(AudioSegment("we get a similar fractal called a Julia set."));
    cs.inject_audio_and_render(AudioSegment("The Mandelbrot sets and the Julia sets are in planes orthogonal to each other in a certain 4d-space."));
    cs.inject_audio_and_render(AudioSegment("This much is well-documented. And don't worry, I'll explain how all of that works in a sec."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"pixel_param_z", "0"},
        {"pixel_param_x", "1"},
        {"pixel_param_c", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("But before that, I wanna twist our perspective once more, into yet another orthogonal 2d-plane."));
    cs.inject_audio_and_render(AudioSegment("This is another natural extension of the Mandelbrot Set which I found."));
    cs.state_manager.microblock_transition(init);
    cs.inject_audio_and_render(AudioSegment("But, let's take it from the start."));
    cs.inject_audio_and_render(AudioSegment("This is the mandelbrot set."));
    cs.state_manager.set(unordered_map<string,string>{
        {"ms.opacity", "1"},
    });
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"ms.opacity", ".2"},
    });
    PngScene comp_axes("complex_axes");
    cs.add_scene_fade_in(&comp_axes, "comp_axes");
    cs.inject_audio_and_render(AudioSegment("It lives in the complex plane."));
    LatexScene eqn("z_{" + latex_text("next") + "} = z^2 + c", 0.7, 1, .5);
    cs.add_scene_fade_in(&eqn, "eqn");
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"comp_axes.opacity", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("The equation which generates it is surprisingly simple."));
    cs.inject_audio_and_render(AudioSegment("Here it is."));
    eqn.begin_latex_transition(latex_color(0xffff0000, "z_{next}") + " = " + latex_color(0xffff0000, "z") + "^2 + c");
    cs.inject_audio_and_render(AudioSegment("It's telling us the way to update this variable Z."));
    cs.inject_audio(AudioSegment("Let's let this variable C be 1 just for now. We'll try other values in a sec."), 4);
    eqn.begin_latex_transition("z^2 + " + latex_color(0xff008888, "c"));
    cs.render();
    eqn.begin_latex_transition("z^2 + 1");
    cs.render();
    cs.render();
    cs.render();
    eqn.begin_latex_transition("0^2 + 1");
    cs.inject_audio_and_render(AudioSegment("And let's let Z start at 0."));
    eqn.begin_latex_transition("0 + 1");
    cs.inject_audio_and_render(AudioSegment("We do some arithmetic,"));
    eqn.begin_latex_transition("1");
    cs.inject_audio_and_render(AudioSegment("and we find the updated value of Z."));
    cs.inject_audio_and_render(AudioSegment("We then take that updated value,"));
    eqn.begin_latex_transition("1^2 + 1");
    cs.inject_audio_and_render(AudioSegment("plug it into the equation,"));
    eqn.begin_latex_transition("2");
    cs.inject_audio_and_render(AudioSegment("and do the math again."));
    eqn.begin_latex_transition("2^2 + 1");
    cs.inject_audio(AudioSegment("We want to keep repeating this over and over."), 2);
    cs.render();
    eqn.begin_latex_transition("4 + 1");
    cs.render();
    eqn.begin_latex_transition("5");
    cs.inject_audio_and_render(AudioSegment("Just square, and add one."));
    eqn.begin_latex_transition("5^2 + 1");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("25 + 1");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("26");
    cs.inject_audio_and_render(AudioSegment("Square, and add one."));
    eqn.begin_latex_transition("26^2 + 1");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("676 + 1");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("677");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("677^2 + 1");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("458229 + 1");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("458330");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("458330^2 + 1");
    cs.inject_audio_and_render(AudioSegment(1));
    cs.inject_audio_and_render(AudioSegment("In our case, Z is blowing up towards infinity."));
    eqn.begin_latex_transition("z^2 + c");
    cs.inject_audio_and_render(AudioSegment("Let's try that again."));
    eqn.begin_latex_transition("z^2 - 1");
    cs.inject_audio_and_render(AudioSegment("This time, let's let C be negative 1 instead of positive 1."));
    eqn.begin_latex_transition("0^2 - 1");
    cs.inject_audio_and_render(AudioSegment("Plug in 0 to start off Z,"));
    eqn.begin_latex_transition("0 - 1");
    cs.inject_audio_and_render(AudioSegment("iterate,"));
    eqn.begin_latex_transition("-1");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("(-1)^2 - 1");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("1 - 1");
    cs.inject_audio_and_render(AudioSegment(1));
    eqn.begin_latex_transition("0");
    cs.inject_audio_and_render(AudioSegment(1));
    cs.inject_audio(AudioSegment("and this time, we fall into a cyclic trap."), 4);
    eqn.begin_latex_transition("0^2 - 1");
    cs.render();
    eqn.begin_latex_transition("-1");
    cs.render();
    eqn.begin_latex_transition("(-1)^2 - 1");
    cs.render();
    eqn.begin_latex_transition("0");
    cs.render();
    eqn.begin_latex_transition("z^2 + c");
    cs.inject_audio_and_render(AudioSegment(1));
    cs.inject_audio_and_render(AudioSegment("Remember, we're working with Complex numbers here, not just real numbers."));
    eqn.begin_latex_transition("z^2 + i");
    cs.inject_audio_and_render(AudioSegment("C can be a number like i."));
    cs.inject_audio(AudioSegment("Running our simulation again, in this case it ends up stuck as well."), 8);
    eqn.begin_latex_transition("0^2 + i");
    cs.render();
    eqn.begin_latex_transition("i");
    cs.render();
    eqn.begin_latex_transition("i^2 + i");
    cs.render();
    eqn.begin_latex_transition("-1+i");
    cs.render();
    eqn.begin_latex_transition("(-1+i)^2 + i");
    cs.render();
    eqn.begin_latex_transition("i");
    cs.render();
    eqn.begin_latex_transition("i^2 + i");
    cs.render();
    eqn.begin_latex_transition("-1+i");
    cs.render();
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"eqn.opacity", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("The differences in behavior here are the key."));
    LatexScene table("\\begin{tabular}{p{4cm}|p{4cm}} \\textbf{z stays bounded} & \\textbf{z explodes} \\end{tabular}", 0.7, 1, 1);
    cs.add_scene_fade_in(&table, "table");
    cs.inject_audio(AudioSegment("Depending on what value of C we choose, sometimes Z will stay close to zero,"), 2);
    table.begin_latex_transition("\\begin{tabular}{p{4cm}|p{4cm}} \\textbf{z stays bounded} & \\textbf{z explodes} \\\\\\\\ \\hline -1 & \\\\\\\\ \\end{tabular}");
    cs.render();
    table.begin_latex_transition("\\begin{tabular}{p{4cm}|p{4cm}} \\textbf{z stays bounded} & \\textbf{z explodes} \\\\\\\\ \\hline -1 & 1 \\\\\\\\ \\end{tabular}");
    cs.render();
    table.begin_latex_transition("\\begin{tabular}{p{4cm}|p{4cm}} \\textbf{z stays bounded} & \\textbf{z explodes} \\\\\\\\ \\hline -1 & 1 \\\\\\\\ i & \\\\\\\\ \\end{tabular}");
    cs.inject_audio_and_render(AudioSegment("and sometimes it won't."));
    cs.fade_out_all_scenes();
    cs.inject_audio_and_render(AudioSegment("That is the difference between a point inside the mandelbrot set, and outside it."));
    cs.remove_all_scenes();
    ExposedPixelsScene eps;
    int gray = 0xff444444;
    eps.exposed_pixels.fill(gray);
    cs.add_scene(&eps, "eps");
    cs.add_scene(&comp_axes, "comp_axes");
    cs.state_manager.set(unordered_map<string,string>{
        {"eps.opacity", "0"},
        {"comp_axes.opacity", "0"},
    });
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"eps.opacity", "1"},
        {"comp_axes.opacity", "1"},
    });
    cs.inject_audio_and_render(AudioSegment("If we make a plot of the complex plane,"));
    cs.inject_audio_and_render(AudioSegment("and for each value of C, we run this little simulation,"));
    double r = VIDEO_WIDTH/500.;
    eps.exposed_pixels.fill_circle(VIDEO_WIDTH/2.+VIDEO_HEIGHT/4., VIDEO_HEIGHT/2., 2*r, OPAQUE_BLACK);
    cs.inject_audio_and_render(AudioSegment("we'll paint points black if they blow up,"));
    eps.exposed_pixels.fill_circle(VIDEO_WIDTH/2., VIDEO_HEIGHT/4., 2*r, OPAQUE_WHITE);
    eps.exposed_pixels.fill_circle(VIDEO_WIDTH/2.-VIDEO_HEIGHT/4., VIDEO_HEIGHT/2., 2*r, OPAQUE_WHITE);
    cs.inject_audio_and_render(AudioSegment("and white if they don't."));
    int num_microblocks = 1000;
    cs.add_scene(&ms, "ms");
    cs.state_manager.set(unordered_map<string,string>{
        {"ms.opacity", "0"},
    });
    Pixels* queried = nullptr;
    ms.query(queried);
    cs.inject_audio(AudioSegment("Do that for all the points..."), num_microblocks);
    for(int i = 0; i < num_microblocks; i++) {
        for(int j = 0; j < 50; j++){
            int point = rand()%(VIDEO_WIDTH*VIDEO_HEIGHT);
            while(eps.exposed_pixels.get_pixel(point%VIDEO_WIDTH, point/VIDEO_WIDTH) != gray){
                point = (point+7841)%(VIDEO_WIDTH*VIDEO_HEIGHT); // 7841 is an arbitrary prime
            }
            int x = point%VIDEO_WIDTH;
            int y = point/VIDEO_WIDTH;
            int col = queried->get_pixel(x, y);
            eps.exposed_pixels.fill_circle(x, y, r, col==OPAQUE_WHITE?OPAQUE_WHITE:OPAQUE_BLACK);
        }
        cs.render();
    }

    cs.inject_audio_and_render(AudioSegment("That gives us the characteristic shape of the Mandelbrot set."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"ms.opacity", "1"},
    });
    cs.inject_audio_and_render(AudioSegment("We can additionally add color to show how long it takes for the number to blow up."));
    cs.remove_scene(&eps);
    cs.remove_scene(&comp_axes);
    eqn.begin_latex_transition("z_{" + latex_text("next") + "} = z^2 + c");
    eqn.end_transition();
    cs.inject_audio_and_render(AudioSegment("And that's how you get these pretty pictures."));
    cs.add_scene_fade_in(&eqn, "eqn");
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"ms.opacity", "0.2"},
    });
    cs.inject_audio_and_render(AudioSegment("But let's look back at our equation."));
    eqn.begin_latex_transition("z_{" + latex_text("next") + "} = z^2 + ?");
    cs.inject_audio_and_render(AudioSegment("We not only had the free choice of what C can be, which is what we're plotting on screen,"));
    eqn.begin_latex_transition("z_{" + latex_text("next") + "} = ?^2 + ?");
    StateSliderScene sszr("[seed_z_r]", "Z_r", -1, 1, .4, .1);
    StateSliderScene sszi("[seed_z_i]", "Z_i", -1, 1, .4, .1);
    cs.add_scene_fade_in(&sszr, "sszr", 0.25, 0.8, true); 
    cs.add_scene_fade_in(&sszi, "sszi", 0.25, 0.9, true); 
    cs.inject_audio_and_render(AudioSegment("but also the option to choose a starting value of Z."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_c_r", "-.5"},
        {"ms.opacity", "1"},
        {"eqn.opacity", "0"},
        {"sszr.opacity", "1 <pixel_param_z> <pixel_param_z> 0.8 * * -"},
        {"sszi.opacity", "<sszr.opacity>"},
    });
    cs.inject_audio_and_render(AudioSegment("Let's change that starting Z from 0 to 1 and see what happens."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"zoom_exp", "-1"},
        {"seed_z_r", "1"},
    });
    cs.inject_audio_and_render(AudioSegment("Woah! That's a totally different set."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_z_r", "<t> sin 2 /"},
        {"seed_z_i", "<t> cos 2 /"},
    });
    cs.inject_audio_and_render(AudioSegment("We can play around with different values of Z all day, just like with C."));
    cs.inject_audio_and_render(AudioSegment("Which makes you think..."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"zoom_exp", "0"},
        {"seed_z_r", "0"},
        {"seed_z_i", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("we started by fixing Z at zero,"));
    cs.inject_audio_and_render(AudioSegment("and making C vary as a function of the pixel we are plotting."));
    PngScene parameterized("parameterized", 0.5, 0.3);
    cs.add_scene(&parameterized, "parameterized", 0.25, 1.2); 
    StateSliderScene sscr("[seed_c_r]", "C_r", -1, 1, .4, .1);
    StateSliderScene ssci("[seed_c_i]", "C_i", -1, 1, .4, .1);
    cs.add_scene(&sscr, "sscr", 0.75, 0.8); 
    cs.add_scene(&ssci, "ssci", 0.75, 0.9); 
    cs.state_manager.set(unordered_map<string,string>{
        {"sscr.opacity", "0"},
        {"ssci.opacity", "<sscr.opacity>"},
    });
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"sscr.opacity", "1 <pixel_param_c> <pixel_param_c> 0.8 * * -"},
        {"parameterized.y", ".85"},
    });
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"pixel_param_z", "1"},
        {"pixel_param_x", "0"},
        {"pixel_param_c", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("What if we fix C, and make Z start where the pixel is?"));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_c_r", "<t> sin .75 *"},
        {"seed_c_i", "<t> cos .75 *"},
    });
    cs.inject_audio_and_render(AudioSegment("We get a Julia set!"));
    cs.inject_audio_and_render(AudioSegment("So, we have 2 variables which we use to seed the iterated procedure."));
    cs.inject_audio_and_render(AudioSegment("We get to choose C, and what Z should start at."));
    cs.inject_audio_and_render(AudioSegment("Since each of these has a real and imaginary component, that's 4 degrees of choice- a 4D shape."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_c_r", "-1"},
        {"seed_c_i", "-.1"},
        {"parameterized.x", ".75 <pixel_param_c> * .25 <pixel_param_z> * +"},
        {"pixel_param_z", "0"},
        {"pixel_param_x", "0"},
        {"pixel_param_c", "1"},
    });
    cs.inject_audio_and_render(AudioSegment("Parameterizing the pixels of the screen as Z yields a Julia set,"));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"pixel_param_z", "1"},
        {"pixel_param_x", "0"},
        {"pixel_param_c", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("whereas parameterizing C yields a Mandelbrot set."));
    cs.inject_audio_and_render(AudioSegment("Now, since we are looking at the space of Z right now, we can also watch what happens when to Z over time throughout our simulation."));
    cs.state_manager.set(unordered_map<string,string>{
        {"point_path_length", "0.5"},
        {"point_path_r", "0.25"},
        {"point_path_i", "0.6"},
    });
    cs.inject_audio_and_render(AudioSegment("Let's let this be our starting point."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"point_path_length", "1.5"},
    });
    cs.inject_audio_and_render(AudioSegment("Iterate the function once, and we get this new point."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"point_path_length", "15"},
    });
    cs.inject_audio_and_render(AudioSegment("Iterate again, and again, and again..."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"point_path_length", "150"},
    });
    cs.inject_audio_and_render(AudioSegment("We can see how Z changes across iterations."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"point_path_r", "<t> sin .75 *"},
        {"point_path_i", "<t> cos .75 *"},
    });
    cs.inject_audio_and_render(AudioSegment("Moving the point around a little,"));
    cs.inject_audio_and_render(AudioSegment(2));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"point_path_r", "1.1"},
        {"point_path_i", ".05"},
    });
    cs.inject_audio(AudioSegment("you can tell the difference between when it converges inside the set,"), 2);
    cs.render();
    cs.render();
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"point_path_r", ".7"},
        {"point_path_i", ".3"},
    });
    cs.inject_audio(AudioSegment("and when it explodes off to infinity."), 2);
    cs.render();
    cs.render();
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"point_path_r", "-.15"},
        {"point_path_i", "-.6"},
    });
    eqn.begin_latex_transition("z_{" + latex_text("next") + "} = z^2 + c");
    cs.inject_audio_and_render(AudioSegment("When you are near the border, it dances around for a bit and then decides to explode."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"ms.opacity", "0.2"},
        {"eqn.opacity", "1"},
    });
    cs.state_manager.set(unordered_map<string,string>{
        {"point_path_length", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("Looking back at the original equation, there's a knob we've left unturned."));
    eqn.begin_latex_transition("z_{" + latex_text("next") + "} = z^3 + c");
    cs.inject_audio_and_render(AudioSegment("This exponent- what if, instead of squaring Z, we cube it?"));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_x_r", "3"},
        {"ms.opacity", "1"},
        {"eqn.opacity", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("Here's what we get."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_c_r", "-.3"},
        {"seed_c_i", "-.4"},
    });
    cs.inject_audio_and_render(AudioSegment("This is a third-degree Julia set!"));
    FOR_REAL = true;
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"pixel_param_z", "0"},
        {"pixel_param_x", "0"},
        {"pixel_param_c", "1"},
        {"seed_c_r", "0"},
        {"seed_c_i", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("We can look at its mandelbrot counterpart too."));
    sszr.state_manager.add_microblock_transition("w", to_string(0.3 * VIDEO_WIDTH));
    sszi.state_manager.add_microblock_transition("w", to_string(0.3 * VIDEO_WIDTH));
    sscr.state_manager.add_microblock_transition("w", to_string(0.3 * VIDEO_WIDTH));
    ssci.state_manager.add_microblock_transition("w", to_string(0.3 * VIDEO_WIDTH));
    StateSliderScene ssxr("[seed_x_r]", "X_r", 0, 4, .3, .1);
    StateSliderScene ssxi("[seed_x_i]", "X_i", 0, 4, .3, .1);
    cs.add_scene_fade_in(&ssxr, "ssxr", 0.5, 0.8); 
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"sszr.x", ".1666"},
        {"sszi.x", ".1666"},
        {"sscr.x", ".8333"},
        {"ssci.x", ".8333"},
        {"parameterized.x", ".8333 <pixel_param_c> * .1666 <pixel_param_z> * .5 <pixel_param_x> * + +"},
    });
    cs.inject_audio_and_render(AudioSegment("We can experiment with the exponent all day."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_x_r", "4"},
    });
    cs.inject_audio_and_render(AudioSegment("Here's an exponent of 4."));
    cs.inject_audio_and_render(AudioSegment(1));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_x_r", "3.5"},
    });
    cs.inject_audio_and_render(AudioSegment("We can even make it a non-integer."));
    cs.inject_audio_and_render(AudioSegment(1));
    cs.add_scene_fade_in(&ssxi, "ssxi", 0.5, 0.9); 
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_x_r", "2"},
        {"seed_x_i", ".1"},
    });
    cs.inject_audio_and_render(AudioSegment("Heck, we can even make it be a complex number too!"));
    cs.inject_audio_and_render(AudioSegment(1));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"seed_x_r", "2"},
        {"seed_x_i", "1"},
    });
    cs.inject_audio_and_render(AudioSegment(1));
    cs.inject_audio_and_render(AudioSegment(1));
    cs.inject_audio_and_render(AudioSegment("So, in some sense, I guess we really had 3 knobs to turn!"));
    cs.inject_audio_and_render(AudioSegment("And that, to me, raises another question."));
    cs.state_manager.microblock_transition(unordered_map<string,string>{
        {"pixel_param_z", "0"},
        {"pixel_param_x", "1"},
        {"pixel_param_c", "0"},
    });
    cs.inject_audio_and_render(AudioSegment("What if we now change the pixel to represent the exponent?"));
    cs.inject_audio_and_render(AudioSegment("So, this is the third orthogonal plane in a six-dimensional shape."));
    return;
    cs.inject_audio_and_render(AudioSegment("We are now fixing Z and C, and letting X vary with the pixel."));
    cs.inject_audio_and_render(AudioSegment("I'll add panels on the right which parameterize each of the 3 variables, and we'll move the origin around in 3-space."));
    cs.inject_audio_and_render(AudioSegment("Wild!"));
    cs.inject_audio_and_render(AudioSegment("This has been 2swap."));
}

int main() {
    Timer timer;
    FOR_REAL = true;
    PRINT_TO_TERMINAL = true;
    intro();
    return 0;
}


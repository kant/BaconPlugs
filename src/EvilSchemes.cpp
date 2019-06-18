#include "BaconPlugs.hpp"
#include "rack.hpp"

struct EvilSchemes : rack::Module {
    enum ParamIds {
        NUM_PARAMS
    };

    enum InputIds {
        NUM_INPUTS
    };

    enum OutputIds {
        NUM_OUTPUTS
    };

    enum LightIds {
        NUM_LIGHTS
    };

    EvilSchemes() : Module() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
    }
};


struct EvilSchemesWidget : rack::ModuleWidget {
    typedef EvilSchemes M;
    EvilSchemesWidget( M *module );
};

EvilSchemesWidget::EvilSchemesWidget(M *module)
{
    setModule(module);
    box.size = Vec(SCREW_WIDTH * 11, RACK_HEIGHT);

    BaconBackground *bg = new BaconBackground(box.size, "EvilSchemes");
    addChild(bg->wrappedInFramebuffer());
}

Model *modelEvilSchemes = createModel<EvilSchemes, EvilSchemesWidget>("EvilSchemes");

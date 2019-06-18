#include "BaconPlugs.hpp"
#include "rack.hpp"
#include "scheme-private.h"
#include "scheme.h"

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

    scheme *sc;
    EvilSchemes() : Module() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

        if (!( sc = scheme_init_new()))
        {
            rack::WARN( "Could not initialize scheme" );
        }
        auto initFile = rack::asset::plugin(pluginInstance, "libs/tinyscheme-1.41/init.scm");
        rack::INFO( "About to load initFile '%s'", initFile.c_str());
        FILE *fin = fopen(initFile.c_str(), "r" );
        if( !fin )
        {
            rack::WARN( "Could not open init file" );
        }
        else
        {
            scheme_load_named_file( sc, fin, initFile.c_str() );
        }

        scheme_load_string( sc, "(+ 1 2)" );
        pointer retv = sc->value;
        rack::INFO( "INFO: is_integer=%d is_real=%d is_list=%d",
                    sc->vptr->is_integer(retv),
                    sc->vptr->is_real(retv),
                    sc->vptr->is_list(sc,retv));
        if( sc->vptr->is_integer(retv) )
        {
            rack::INFO( "Evaluated to %d", sc->vptr->ivalue(retv) );
        }
    }

    ~EvilSchemes() {
        scheme_deinit(sc);
        free(sc);
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

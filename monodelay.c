#include <math.h>
#include <stdlib.h>
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>

#define PLUGIN_URI "http://lv2plug.in/plugins/monodelay"

// gain in dB to coefficient converter
#define DB_CO(g) ((g) > -90.0f ? powf(10.0f, (g) * 0.05f) : 0.0f)

typedef struct {
    float* input_port;
    float* output_port;
    float* wet_port;
    float* delay_buffer;
    uint32_t buffer_size;
    uint32_t write_index;
    uint32_t delay_time;
} Delay;

static LV2_Handle instantiate(const LV2_Descriptor* descriptor, 
                              double sample_rate, const char* bundle_path, 
                              const LV2_Feature* const* features) {
    Delay* delay = (Delay*)malloc(sizeof(Delay));
    delay->buffer_size = (uint32_t)((sample_rate * 0.03) * 2);
    delay->write_index = 0;
    delay->delay_time = (uint32_t)(sample_rate * 0.03);
    delay->delay_buffer = (float*)calloc(delay->buffer_size, sizeof(float));
    return (LV2_Handle)delay;
}

static void connect_port(LV2_Handle instance, uint32_t port, void* data) {
    Delay* delay = (Delay*)instance;
    switch (port) {
        case 0:
            delay->input_port = (float*)data;
            break;
        case 1:
            delay->output_port = (float*)data;
            break;
        case 2:
            delay->wet_port = (float*)data;
            break;
    }
}

static void activate(LV2_Handle instance) {}

static void deactivate(LV2_Handle instance) {}

static void cleanup(LV2_Handle instance) {
    Delay* delay = (Delay*)instance;
    free(delay->delay_buffer);
    free(delay);
}

static void run(LV2_Handle instance, uint32_t n_samples) {
    Delay* delay = (Delay*)instance;
    float* in = delay->input_port;
    float* out = delay->output_port;
    float* buffer = delay->delay_buffer;
    float wet = *delay->wet_port;
    float coef_wet = DB_CO(wet);
    uint32_t delay_time = delay->delay_time;
    uint32_t write_index = delay->write_index;
    uint32_t buffer_size = delay->buffer_size;

    for (uint32_t i = 0; i < n_samples; ++i) {
        float dry = in[i];
        float delayed = buffer[(write_index + delay_time) % buffer_size];
        buffer[write_index] = dry;
        out[i] = dry + delayed * coef_wet;
        write_index = (write_index + 1) % buffer_size;
    }

    delay->write_index = write_index;
}

static const void* extension_data(const char* uri) {
    return NULL;
}

static const LV2_Descriptor descriptor = {
    PLUGIN_URI,
    instantiate,
    connect_port,
    activate,
    run,
    deactivate,
    cleanup,
    extension_data
};


LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
	switch (index) {
	case 0:  return &descriptor;
	default: return NULL;
	}
}

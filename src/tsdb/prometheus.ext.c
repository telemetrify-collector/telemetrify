
#include "prw.pb-c.h"

void tsdbQ_prometheusQ___ext_init__() {
   // NOP
}

B_bytes tsdbQ_prometheusQ_pack(B_list metric_data) {
    WriteRequest write_request;
    write_request__init(&write_request);

    TimeSeries **time_series = calloc(metric_data->length, sizeof(TimeSeries*));
    for (int i = 0; i < metric_data->length; ++i) {
        B_tuple metric_series = (B_tuple)metric_data->data[i];
        TimeSeries *new_series = malloc(sizeof(TimeSeries));
	time_series__init(new_series);

	B_list labels = (B_list)metric_series->components[0];
        new_series->n_labels = labels->length;
	Label **labels_pb = calloc(labels->length, sizeof(Label*));
	for (int j = 0; j < labels->length; ++j) {
            Label* new_label = malloc(sizeof(Label));
	    label__init(new_label);
            B_tuple label = (B_tuple)labels->data[j];

	    // Hopefully no encoding weirdness but in theory bytes are bytes
	    new_label->name = (char*)((B_str)label->components[0])->str;
	    new_label->value = (char*)((B_str)label->components[1])->str;

	    labels_pb[j] = new_label;
	}
	new_series->labels = labels_pb;

	B_list samples = (B_list)metric_series->components[1];
        new_series->n_samples = samples->length;
	Sample **samples_pb = calloc(samples->length, sizeof(Sample*));
	for (int j = 0; j < samples->length; ++j) {
            Sample* new_sample = malloc(sizeof(Sample));
	    sample__init(new_sample);
            B_tuple sample = (B_tuple)samples->data[j];

	    new_sample->value = ((B_float)sample->components[0])->val;
	    new_sample->timestamp = from$int((B_int)sample->components[1]);

	    samples_pb[j] = new_sample;
	}
	new_series->samples = samples_pb;

	time_series[i] = new_series;
    }

    write_request.timeseries = time_series;

    size_t buffer_size = write_request__get_packed_size(&write_request);
    uint8_t *buffer = malloc(buffer_size);
    write_request__pack(&write_request, buffer);

    B_bytes ret = to$bytesD_len((char*)buffer, buffer_size);

    return ret;
}

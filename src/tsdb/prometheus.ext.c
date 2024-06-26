
//#include <stdio.h>
#include "prw.pb-c.c"

void tsdbQ_prometheusQ___ext_init__() {
   // NOP
}

B_bytes tsdbQ_prometheusQ_pack(B_list metric_data) {
    WriteRequest write_request;
    write_request__init(&write_request);

    TimeSeries **time_series = acton_calloc(metric_data->length, sizeof(TimeSeries*));
    write_request.n_timeseries = metric_data->length;
    for (int i = 0; i < metric_data->length; ++i) {
        B_tuple metric_series = (B_tuple)metric_data->data[i];
        TimeSeries *new_series = acton_malloc(sizeof(TimeSeries));
        time_series__init(new_series);

        B_list labels = (B_list)metric_series->components[0];
        new_series->n_labels = labels->length;
        Label **labels_pb = acton_calloc(labels->length, sizeof(Label*));
        for (int j = 0; j < labels->length; ++j) {
            Label* new_label = acton_malloc(sizeof(Label));
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
        Sample **samples_pb = acton_calloc(samples->length, sizeof(Sample*));
        for (int j = 0; j < samples->length; ++j) {
            Sample* new_sample = acton_malloc(sizeof(Sample));
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

    //printf("write_request.timeseries[0]->samples[0]->value: %f\n", write_request.timeseries[0]->samples[0]->value);
    //printf("write_request.timeseries[0]->samples[0]->timestamp: %d\n", write_request.timeseries[0]->samples[0]->timestamp);

    size_t buffer_size = write_request__get_packed_size(&write_request);
    //printf("buffer_size: %zu\n", buffer_size);
    uint8_t *buffer = acton_malloc(buffer_size);
    write_request__pack(&write_request, buffer);

    B_bytes ret = to$bytesD_len((char*)buffer, buffer_size);

    return ret;
}

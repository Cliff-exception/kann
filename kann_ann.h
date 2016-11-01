#ifndef KANN_ANN_H
#define KANN_ANN_H

#define KAD_LABEL_IN        1
#define KAD_LABEL_OUT_PRE   2
#define KAD_LABEL_OUT_TRUTH 3

#include <stdint.h>
#include "kautodiff.h"

typedef struct {
	float lr; // learning rate
	float fv; // fraction of validation data
	int mb_size; // size of a mini batch
	int epoch_lazy;
	int max_epoch;

	float decay;
} kann_mopt_t;

typedef struct {
	kad_rng_t rng; // for kautodiff, as it is independent of kann_rand
	int n;
	kad_node_t **v;
	kad_node_t *out_pre, *out_truth, *in;
	float *t, *g;
} kann_t;

#ifdef __cplusplus
extern "C" {
#endif

kann_t *kann_init(uint64_t seed);
void kann_destroy(kann_t *a);
void kann_sync(kann_t *a);
int kann_n_in(kann_t *a);
int kann_n_out(kann_t *a);
int kann_n_par(kann_t *a);

void kann_mopt_init(kann_mopt_t *mo);
void kann_RMSprop(int n, float h0, const float *h, float decay, const float *g, float *t, float *r);
void kann_set_batch_size(int B, int n_node, kad_node_t **node);

#ifdef __cplusplus
}
#endif

#endif

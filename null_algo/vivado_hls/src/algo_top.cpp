#include "algo_top_parameters.h"
#include "algo_top.h"

using namespace std;
using namespace algo;
	
void algo_top( hls::stream<axiword> link_in[N_INPUT_LINKS], 
               hls::stream<axiword> link_out[N_OUTPUT_LINKS]) {

#pragma HLS INTERFACE axis port=link_in
#pragma HLS INTERFACE axis port=link_out
#pragma HLS PIPELINE II=N_WORDS_PER_FRAME
#pragma HLS ARRAY_PARTITION variable=link_in complete dim=0
#pragma HLS ARRAY_PARTITION variable=link_out complete dim=0


	// Algo passthrough (for testing)
	for (size_t i = 0; i < N_WORDS_PER_FRAME; i++) {
		axiword r[N_INPUT_LINKS];

		// Read all inputs
		for (size_t l = 0; l < N_INPUT_LINKS; l++)
			r[l] = link_in[l].read();

		// Write inputs to outputs
		for (size_t l = 0; l < N_OUTPUT_LINKS; l++) {
			if (l >= N_INPUT_LINKS) {
				link_out[l].write(r[N_INPUT_LINKS-1]);
			} else {
				link_out[l].write(r[l]);
			}
		}
	}
}

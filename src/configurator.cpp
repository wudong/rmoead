/*
 * configurator.cpp
 *
 *  Created on: 21 Aug 2009
 *      Author: wudong
 */

#include "global.h"
#include "configurator.h"

int load_parameters(std::string configfile) {
	cfg_opt_t problem_opts[] = { CFG_STR("name", "UF1", CFGF_NONE),
			CFG_INT("objdim", 2, CFGF_NONE), CFG_INT("pardim", 2, CFGF_NONE),
			CFG_END() };

	cfg_opt_t
			opts[] = { CFG_SEC("problem", problem_opts, CFGF_MULTI),
					CFG_INT("total_runs", 30, CFGF_NONE),
					CFG_INT("random_seed", 0, CFGF_NONE),
					CFG_INT("population_size_2", 600,CFGF_NONE),
					CFG_INT("neighbour_size_2", 60, CFGF_NONE),
					CFG_INT("population_size_3", 1000, CFGF_NONE),
					CFG_INT("neighbour_size_3", 100, CFGF_NONE),
					CFG_INT("total_evaluations", 300000, CFGF_NONE),
					CFG_INT("update_limit", 5, CFGF_NONE),
					CFG_INT("weight_adjust_size", 10, CFGF_NONE),
					CFG_FLOAT("update_neighbour_probablity", 0.9, CFGF_NONE),
					CFG_FLOAT("de_f", 0.5, CFGF_NONE),
					CFG_FLOAT("de_cr", 1, CFGF_NONE),
					CFG_INT("compute_utility", 1, CFGF_NONE),
					CFG_STR("scalarization_method", "ws", CFGF_NONE),
					CFG_STR_LIST("problem_to_test", "{}", CFGF_NONE),
					CFG_INT("tournament_size", 2, CFGF_NONE),
					CFG_INT("selection_size", 120, CFGF_NONE),
					CFG_INT("utilcomp_gen", 30, CFGF_NONE),
					CFG_STR("select_method", "tour", CFGF_NONE),
					CFG_FLOAT("sort_probablity", 0.99, CFGF_NONE),
					CFG_FLOAT("decay_rate", 0.95, CFGF_NONE),
					CFG_FLOAT("decay_delta", 0.001, CFGF_NONE),
					CFG_STR("evolve_method","de", CFGF_NONE),
					CFG_BOOL("use_reactive",cfg_false, CFGF_NONE),
					CFG_BOOL("use_weight_adjust",cfg_false, CFGF_NONE),
					CFG_FLOAT("de_weight", 0.95, CFGF_NONE),
					CFG_FLOAT("mutation_rate", 1.0, CFGF_NONE),
					CFG_FLOAT("reactive_probablity", 0.9, CFGF_NONE), CFG_END() };

	configurator = cfg_init(opts, CFGF_NONE);
	if (cfg_parse(configurator, configfile.c_str()) == CFG_PARSE_ERROR)
		return 1;
	else
		return 0;
}

int getNumberofTestInstance() {
	return cfg_size(configurator, "problem");
}

int getPopulationSize() {
	if (nobj == 2) {
		return cfg_getint(configurator, "population_size_2");
	} else if (nobj == 3) {
		return cfg_getint(configurator, "population_size_3");
	} else
		assert(false);
}

int getNeighbourSize() {
	if (nobj == 2) {
		return cfg_getint(configurator, "neighbour_size_2");
	} else if (nobj == 3) {
		return cfg_getint(configurator, "neighbour_size_3");
	} else
		assert(false);
}

int getTotalNumberofRun() {
	return cfg_getint(configurator, "total_runs");
}

void getTestInstance(Problem& p, int i) {
	cfg_t * cfg_problem = cfg_getnsec(configurator, "problem", i);
	char* name = cfg_getstr(cfg_problem, "name");
	int nvar = cfg_getint(cfg_problem, "pardim");
	int nobj = cfg_getint(cfg_problem, "objdim");

	strcpy(p.name, name);
	p.nobj = nobj;
	p.nvar = nvar;
}

int getNumberofProblemToTest() {
	return cfg_size(configurator, "problem_to_test");
}

char* getProblemToTest(int i) {
	return cfg_getnstr(configurator, "problem_to_test", i);
}

int getTournamentSize() {
	return cfg_getint(configurator, "tournament_size");
}

float getSortProb() {
	return cfg_getfloat(configurator, "sort_probablity");
}

float getDecayRate() {
	return cfg_getfloat(configurator, "decay_rate");
}

char* getSelectionMethod() {
	return cfg_getstr(configurator, "select_method");
}

int getSelectionSize() {
	return cfg_getint(configurator, "selection_size");
}

char* getScalarizationMethod() {
	return cfg_getstr(configurator, "scalarization_method");
}

int getUtilityComputationGen() {
	return cfg_getint(configurator, "utilcomp_gen");
}

float getMutationRate() {
	return cfg_getfloat(configurator, "mutation_rate");
}

char* getEvolveMethod() {
	return cfg_getstr(configurator, "evolve_method");
}

bool ifUseReactive() {
	return cfg_getbool(configurator, "use_reactive");
}

bool ifUseWeightAdjust() {
	return ifUseReactive() && cfg_getbool(configurator, "use_weight_adjust");
}

float getReactiveProb() {
	return cfg_getfloat(configurator, "reactive_probablity");
}

float getDEWeight() {
	return cfg_getfloat(configurator, "de_weight");
}

float getDecayDelta() {
	return cfg_getfloat(configurator, "decay_delta");
}

float getDEf() {
	return cfg_getfloat(configurator, "de_f");
}

float getDEcr() {
	return cfg_getfloat(configurator, "de_cr");
}

float getUpdateLimit() {
	return cfg_getint(configurator, "update_limit");
}

float getUpdateNeighbourProb() {
	return cfg_getfloat(configurator, "update_neighbour_probablity");
}

int getRandomSeed() {
	return cfg_getint(configurator, "random_seed");
}

int getWeightAdjustSize(){
	return cfg_getint(configurator, "weight_adjust_size");
}


void setRandomSeed(int seed) {
	cfg_setint(configurator, "random_seed", seed);
}

void printAllParameters(FILE* output) {
	//output the random seed.
	cfg_opt_print_indent(cfg_getopt(configurator, "random_seed"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "population_size_2"), output,
			2);
	cfg_opt_print_indent(cfg_getopt(configurator, "neighbour_size_2"), output,
			2);
	cfg_opt_print_indent(cfg_getopt(configurator, "selection_size"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "update_limit"), output, 2);
	cfg_opt_print_indent(
			cfg_getopt(configurator, "update_neighbour_probablity"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "sort_probablity"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "decay_rate"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "utilcomp_gen"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "scalarization_method"),
			output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "evolve_method"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "use_reactive"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "reactive_probablity"),
			output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "use_weight_adjust"), output,
			2);
	cfg_opt_print_indent(cfg_getopt(configurator, "weight_adjust_size"), output,
				2);
	cfg_opt_print_indent(cfg_getopt(configurator, "decay_delta"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "mutation_rate"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "de_f"), output, 2);
	cfg_opt_print_indent(cfg_getopt(configurator, "de_cr"), output, 2);
}

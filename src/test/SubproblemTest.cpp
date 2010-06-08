#ifdef UNIT_TEST
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE SubproblemTest

#include "../Subproblem.h"
#include "../RMOEAD.h"
#include <boost/test/unit_test.hpp>

struct Massive {
	Massive() {

		if (load_parameters("rmoead.conf") != 0) {
			std::cerr << "error: reading the parameter file";
			exit(1);
		}

		input_dir = "/home/wudong/workspace/huimoea";
		output_dir = ".";
		strTestInstance = "UF1";
		nobj = 2;
		nvar = 3;
		rand_T = gsl_rng_default;
		rand_generator = gsl_rng_alloc(rand_T);
		gsl_rng_set(rand_generator, 0);
		gsl_rng_env_setup();
	}

	~Massive() {
		gsl_rng_free(rand_generator);
		cfg_free(configurator);
	}
};

BOOST_FIXTURE_TEST_SUITE(Physics, Massive)

BOOST_AUTO_TEST_CASE( subproblem_dominance )
{

	Subproblem sub1;
	Subproblem sub2;
	sub1.indiv.y_obj[0] = 1;
	sub1.indiv.y_obj[1] = 0;

	sub2.indiv.y_obj[0] = 1;
	sub2.indiv.y_obj[1] = 0;

	BOOST_CHECK(!sub1.dominate(sub2));
	BOOST_CHECK(!sub2.dominate(sub1));

	sub2.indiv.y_obj[0] = 1;
	sub2.indiv.y_obj[1] = 1;

	BOOST_CHECK(sub1.dominate(sub2));
	BOOST_CHECK(!sub2.dominate(sub1));

	sub2.indiv.y_obj[0] = 2;
	sub2.indiv.y_obj[1] = 0;

	BOOST_CHECK(sub1.dominate(sub2));
	BOOST_CHECK(!sub2.dominate(sub1));

	sub2.indiv.y_obj[0] = 0;
	sub2.indiv.y_obj[1] = 1;

	BOOST_CHECK(!sub1.dominate(sub2));
	BOOST_CHECK(!sub2.dominate(sub1));
}

BOOST_AUTO_TEST_CASE( subproblem_dominance_selection1 )
{
	vector<SubproblemPtr> pops;

	for (int i=0;i<10;i++) {
		SubproblemPtr sub1 = new Subproblem();
		sub1->indiv.y_obj[0] = i;
		sub1->indiv.y_obj[1] = -i;
		pops.push_back(sub1);
	}

	vector<SubproblemPtr> selected;
	vector<SubproblemPtr> dominated;
	Subproblem::nondom_select(selected,dominated, pops);

	BOOST_CHECK(10==selected.size());
	BOOST_CHECK(0==dominated.size());
	std::cout<<"non-domination size: "<<selected.size()<<std::endl;

	selected.clear();
	dominated.clear();
	pops.clear();
	for (int i=0;i<10;i++) {
		SubproblemPtr sub1 = new Subproblem();
		sub1->indiv.y_obj[0] = i;
		sub1->indiv.y_obj[1] = i;
		pops.push_back(sub1);
	}

	Subproblem::nondom_select(selected, dominated, pops);
	BOOST_CHECK(1==selected.size());
	BOOST_CHECK(9==dominated.size());
	BOOST_CHECK(0==selected[0]->indiv.y_obj[0]);
	BOOST_CHECK(0==selected[0]->indiv.y_obj[1]);

	selected.clear();
	dominated.clear();
	pops.clear();

	SubproblemPtr sub1 = new Subproblem();
	sub1->indiv.y_obj[0] = 1;
	sub1->indiv.y_obj[1] = 3;
	pops.push_back(sub1);

	sub1 = new Subproblem();
	sub1->indiv.y_obj[0] = 1;
	sub1->indiv.y_obj[1] = 2;
	pops.push_back(sub1);

	sub1 = new Subproblem();
	sub1->indiv.y_obj[0] = 1;
	sub1->indiv.y_obj[1] = 1;
	pops.push_back(sub1);

	sub1 = new Subproblem();
	sub1->indiv.y_obj[0] = 2;
	sub1->indiv.y_obj[1] = 5;
	pops.push_back(sub1);

	sub1 = new Subproblem();
	sub1->indiv.y_obj[0] = 3;
	sub1->indiv.y_obj[1] = 5;
	pops.push_back(sub1);

	sub1 = new Subproblem();
	sub1->indiv.y_obj[0] = 2;
	sub1->indiv.y_obj[1] = 1;
	pops.push_back(sub1);

	sub1 = new Subproblem();
	sub1->indiv.y_obj[0] = 0;
	sub1->indiv.y_obj[1] = 5;
	pops.push_back(sub1);

	sub1 = new Subproblem();
	sub1->indiv.y_obj[0] = 5;
	sub1->indiv.y_obj[1] = 3;
	pops.push_back(sub1);

	for (int i=0;i<100;i++) {
		sub1 = new Subproblem();
		sub1->indiv.y_obj[0] = 10+i*(i/10);
		sub1->indiv.y_obj[1] = 5+i*(i/8);
		pops.push_back(sub1);
	}

	sub1 = new Subproblem();
	sub1->indiv.y_obj[0] = 2;
	sub1->indiv.y_obj[1] = 0;
	pops.push_back(sub1);

	Subproblem::nondom_select(selected, dominated, pops);
	BOOST_CHECK(3==selected.size());
	BOOST_CHECK(pops.size()==selected.size()+dominated.size());
	std::cout<<"point 1: "<<selected[0]->indiv.y_obj[0]<<", "<<selected[0]->indiv.y_obj[1]<<std::endl;
	std::cout<<"point 2: "<<selected[1]->indiv.y_obj[0]<<", "<<selected[1]->indiv.y_obj[1]<<std::endl;
	std::cout<<"point 3: "<<selected[2]->indiv.y_obj[0]<<", "<<selected[2]->indiv.y_obj[1]<<std::endl;

}

BOOST_AUTO_TEST_CASE( subproblem_dominance_selection2 )
{
	vector<SubproblemPtr> pops;

	int size = 1000;
	for (int i=0;i<size;i++) {
		SubproblemPtr sub1 = new Subproblem();
		sub1->indiv.y_obj[0] = nextRandomDouble();
		sub1->indiv.y_obj[1] = nextRandomDouble();
		pops.push_back(sub1);
	}

	vector<SubproblemPtr> selected;
	vector<SubproblemPtr> dominated;
	Subproblem::nondom_select(selected,dominated,pops);

	std::cout<<"non-domination size: "<<selected.size()<<std::endl;
	std::cout<<"domination size: "<<dominated.size()<<std::endl;

	BOOST_CHECK(size==(selected.size()+dominated.size()));

	for (int i=0;i<selected.size();i++) {
		for (int j=0;j<selected.size();j++) {
			if (i!=j) {
				BOOST_CHECK(!selected[i]->dominate(*selected[j]));
				BOOST_CHECK(!selected[j]->dominate(*selected[i]));
			}
		}
	}
}

/*
BOOST_AUTO_TEST_CASE( build_neighbour ) {
	RMOEAD rmoead;
	rmoead.init_population();
	BOOST_CHECK(600==rmoead.population.size());

	for (int i=0;i<600;i++){
		SubproblemPtr pop = rmoead.population[i];
		std::cout<<"subproblem: "<<std::endl;
		pop->show_weight();
		std::cout<<"adjacent: "<<std::endl;
		for (int j=0;j<pop->adjacent.size();j++)
			pop->adjacent[j]->show_weight();
	}
}
*/

BOOST_AUTO_TEST_SUITE_END()

#endif

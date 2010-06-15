#ifndef UNIT_TEST

#include "global.h"
#include "RMOEAD.h"
#include <tclap/CmdLine.h>
#include <stdlib.h>
#include "Cec09Function.h"

int main(int argc, char** argv) {
	//handel the command line
	std::string paramFile;
	try {
		TCLAP::CmdLine cmd("R-MOEA/D Help Message", ' ', "1.0");

		//The input directory.
		TCLAP::ValueArg<std::string> inputArg("i", "input",
				"the directory for the algorithm's input parameter files",
				false, ".", "string");
		cmd.add(inputArg);

		//The output directory.
		TCLAP::ValueArg<std::string> outputArg("o", "output",
				"the algorithm output directory", false, ".", "string");
		cmd.add(outputArg);

		//the random seed.
		TCLAP::ValueArg<long> seedArg("r", "seed",
				"the random seed for this run", false, 0, "long");
		cmd.add(seedArg);

		//the parameter file
		TCLAP::ValueArg<string> paramArg("p", "parameters",
				"the file contains the parameters", false, "rmoead.conf",
				"string");
		cmd.add(paramArg);

		cmd.parse(argc, argv);
		output_dir = outputArg.getValue();
		random_seed = seedArg.getValue();
		input_dir = inputArg.getValue();
		paramFile = paramArg.getValue();
		paramFile = input_dir + "/" + paramFile;

		std::cout << "Input Directory: " << input_dir << std::endl;
		std::cout << "Output Directory: " << output_dir << std::endl;
		std::cout << "Parameter File: " << paramFile << std::endl;
		//copy the paramFile to the output_dir;
		std::string cpcmd = "cp " + paramFile + " "+ output_dir+"/params.txt";
		system(cpcmd.c_str());
	} catch (TCLAP::ArgException &e) // catch any exceptions
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId()
				<< std::endl;
	}

	//configurator string
	if (load_parameters(paramFile) != 0) {
		std::cerr << "error: reading the parameter file";
		exit(1);
	}

	//also print the parameters to a file in the output directory.
//	std::string paramfile;
//	paramfile = output_dir + "/params.txt";
//	FILE* paramfileFILE = fopen(paramfile.c_str(), "w");
//	printAllParameters(paramfileFILE);
//	fclose(paramfileFILE);

	//set the random generator.
	rand_T = gsl_rng_default;
	rand_generator = gsl_rng_alloc(rand_T);

	int seed = getRandomSeed();
	if (seed!=0)
		random_seed=seed;

	gsl_rng_set(rand_generator, random_seed);
    setRandomSeed(random_seed);
	//std::cout << "Random Seed: " << random_seed << std::endl;
	//set it back

	//print the parameters to the std output.
	std: cout << "Parameter Used: " << std::endl;
	printAllParameters( stdout);

	//the random generator type and seed can be set in environment variable
	//GSL_RNG_TYPE and GSL_RNG_SEED
	gsl_rng_env_setup();

	int numOfInstance = getNumberofTestInstance();
	int total_run = getTotalNumberofRun();

	//printf("\n -- %d Instances are being tested ---\n\n", numOfInstance);

	for (int inst = 0; inst < numOfInstance; inst++) {
		// the parameter setting of test instance
		Problem instance;
		getTestInstance(instance, inst);

		nvar = instance.nvar;
		nobj = instance.nobj;

		bool test = false;
		int idx = getNumberofProblemToTest(), j;
		if (idx != 0) {
			for (j = 0; j < idx; j++) {
				char* prob = getProblemToTest(j);
				if (strcmp(prob, instance.name) == 0) {
					test = true;
					break;
				}
			}
		} else
			test = true;

		if (!test)
			continue;

		printf("\n -- Instance: %s, %d variables %d objectives \n\n",
				instance.name, nvar, nobj);

		clock_t start, temp, finish;
		double duration, last = 0;
		start = clock();

		//log information.
		std::fstream fout;
		char file[50];
		sprintf(file, "%s/MOEAD_%s.log", input_dir.c_str(), instance.name);
		std::string filename(output_dir);
		filename.append(file);
		fout.open(filename.c_str(), std::ios::out);

		boost::shared_ptr<std::string> funcname(new std::string(instance.name));
		FunctionPtr cec09(new Cec09Function(*funcname, instance.nvar, instance.nobj));

		fout << "Inst: " << funcname << endl;
		fout << "Time: \n\n";

		for (int i = 0; i < nobj; i++)
			idealpoint[i] = 10e+30;

		for (int run = 1; run <= total_run; run++) {
			printf("\n %s: -- %d-th run  -- \n", instance.name, run);

			RMOEAD moead;
			moead.setFunction(cec09);
			moead.setRunId(run);
			moead.evolve();

			temp = clock();
			duration = (double) (temp - start) / CLOCKS_PER_SEC;
			fout << run << ":" << duration - last << " ";
			last = duration;
			if (run % 10 == 0)
				fout << "\n";
		}

		fout << "\n\n";

		finish = clock();
		duration = (double) (finish - start) / CLOCKS_PER_SEC;

		fout << "Mean  CPU Time  " << duration / 30 << " seconds" << endl;
		fout << "Total CPU Time  " << duration << " seconds" << endl;
		fout.close();

	}
	gsl_rng_free(rand_generator);
	cfg_free(configurator);
}

#endif


void detect(Char_t *input, Char_t *output)
{
    const double ccdbDiff = 4.;

    const double err = 10.;

    const double err2 = 0.001;

    ifstream infile(input);

    ofstream outfile(output);

    std::string line;

    double T0, T0err;

    double T02, T0err2;

    double T03, T0err3;

    int sector = 0, superlayer = 0, slot = 0, cable = 0;
    
    //int id = 0;

    std::getline(infile, line);

    std::getline(infile, line);

    while (std::getline(infile, line))
    {
        std::istringstream iss(line);

        iss >> T0 >> T0err >> T02 >> T0err >> T03 >> T0err3;

        if(std::fabs(T0-(T02-5.))>ccdbDiff || T0err > err || iss.fail() || T0err < err2)
        {
            outfile << TString::Format("T0s_%i_%i_%i_%i.png\n", sector, superlayer, slot, cable);
            //outfile << id << endl;
        }

        ++cable;
        
        //++id;

        if(cable == 6)
        {
            cable = 0;
            ++slot;
        }
        if(slot == 7)
        {
            slot = 0;
            ++superlayer;
        }
        if(superlayer == 6)
        {
            superlayer = 0;
            ++sector;
        }
    }

    infile.close();

    outfile.close();

}

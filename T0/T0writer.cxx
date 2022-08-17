void T0writer(Char_t *input, Char_t *input2, Char_t *output)
{
    ifstream infile(input);

    ifstream infile2(input2);

    ofstream outfile(output);

    std::string line, line2;

    int var;

    double T0Der, T0ErrDer, T0CCDB, T0ErrCCDB, T0Erf, T0ErrErf;

    double final_T0, final_T0Err;

    std::string tofind_fine("fine");
    std::string tofind_erf("erf");
    std::string tofind_ccdb("CCDB");
    std::string tofind_hand("hand");

    size_t pos_fine;
    size_t pos_erf;
    size_t pos_ccdb;
    size_t pos_hand;

    int counter_fine = 0;
    int counter_erf = 0;
    int counter_ccdb = 0;
    int counter_hand = 0;
    int counter_default = 0;

    int wire = 0;

    std::getline(infile2, line2);

    std::getline(infile2, line2);

    while (std::getline(infile2, line2))
    {
        std::istringstream iss(line2);

        iss >> T0Der >> T0ErrDer >> T0CCDB >> T0ErrCCDB >> T0Erf >> T0ErrErf;

        pos_fine = std::string::npos;
        pos_erf = std::string::npos;
        pos_ccdb = std::string::npos;
        pos_hand = std::string::npos;

        infile.clear();

        infile.seekg(0, infile.beg);

        while (std::getline(infile, line))
        {
            std::istringstream iss2(line);
            iss2 >> var;
            if(wire == var)
            {
                pos_fine = line.find(tofind_fine);
                pos_erf = line.find(tofind_erf);
                pos_ccdb = line.find(tofind_ccdb);
                pos_hand = line.find(tofind_hand);
                break;
            }
        }

        if (pos_fine!=std::string::npos)
        {
            cout << wire << " fine" << endl;
            counter_fine++;
            final_T0 = T0Der;
            final_T0Err = T0ErrDer;
        }
        else if (pos_erf!=std::string::npos)
        {
            cout << wire << " erf" << endl;
            counter_erf++;
            final_T0 = T0Erf;
            final_T0Err = T0ErrErf;
        }
        else if (pos_ccdb!=std::string::npos)
        {
            cout << wire << " ccdb" << endl;
            counter_ccdb++;
            final_T0 = T0CCDB;
            final_T0Err = T0ErrCCDB;
        }
        else if (pos_hand!=std::string::npos)
        {
            cout << wire << " hand" << endl;
            counter_hand++;
            final_T0 = -1000;
            final_T0Err = -1000;
        }
        else
        {
            cout << wire << " default" << endl;
            counter_default++;
            final_T0 = T0Der;
            final_T0Err = T0ErrDer;
        }

        outfile << final_T0 << "\t" << final_T0Err << endl;

        ++wire;
    }

    cout << "fine: " << counter_fine << endl;
    cout << "erf: " << counter_erf << endl;
    cout << "ccdb: " << counter_ccdb << endl;
    cout << "hand: " << counter_hand << endl;
    cout << "default: " << counter_default << endl;

    infile.close();

    infile2.close();

    outfile.close();
}

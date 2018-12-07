void processGlobID(){
    std::ifstream input;
    int runnumber = 0;
    int numPARs = 0;
    ULong64_t PAR = 0;
    int lastrunnumber = 0;
    ULong64_t lastPAR = 0;
    std::vector<ULong64_t> PARvec;
    input.open("GlobID_2018.txt");
    if(!input.good()){
        //AliFatal(Form("PAR info file not accessable");
        return;
    }

    FILE* output = fopen("GlobID_2018_processed.txt", "w");

    while(input.good()){
        input >> runnumber;
        if(!input.good()){
            PARvec.push_back(lastPAR);
            numPARs++;
            fprintf(output, "%d %d", lastrunnumber, numPARs);
            for(int i =0; i< numPARs; i++){
                fprintf(output, " %llu", PARvec[i]);
            }
            fprintf(output, "\n"); 
            break;
        }
        if(lastrunnumber != runnumber){
            if(lastrunnumber !=0){
                PARvec.push_back(lastPAR);
                numPARs++;
                fprintf(output, "%d %d", lastrunnumber, numPARs);
                for(int i =0; i< numPARs; i++){
                    fprintf(output, " %llu", PARvec[i]);
                }
                fprintf(output, "\n");
                PARvec.erase(PARvec.begin(), PARvec.end());
            }
            input >> PAR;
            numPARs=0;
        }else{
            if(lastPAR !=0){
                PARvec.push_back(lastPAR);
                numPARs++;
            }
            input >> PAR;
        }
        lastPAR = PAR;
        lastrunnumber = runnumber;
    }
    input.close();
    return;
}

#include <iostream>
#include "Bohr.h"
#include "utils.h"
#include <thread>
#include <vector>

void readMarkers(Bohr& bohr){
    int i = 0;
    const std::string markerFileName = "../input/markers.csv";
    std::ifstream f(markerFileName);
    std::string str;

    if(f) {
        std::ostringstream ss;
        ss << f.rdbuf(); // reading data
        str = ss.str();
    }

    boost::locale::boundary::ssegment_index resultMap(boost::locale::boundary::word, str.begin(),
            str.end());
    resultMap.rule(boost::locale::boundary::word_any);

    for (boost::locale::boundary::ssegment_index::iterator it = resultMap.begin(), e = resultMap.end();
         it != e; it++) {
        it++;
        bohr.add_key(*it);
        i++;
        std::cout << *it <<std::endl;
        if(i == 2)
            break;
    }

    //std::string().swap(str);
}

void calculate(Bohr &b, const std::string &str, std::map<std::string, int> &res){
    b.find_all_entries(str, res);
}

int main() {
    std::map<std::string, std::string> config;
    int threadNum = 0;
    const int biggestMarkerSize = 646;
    Bohr b;
    boost::locale::generator gen;
    std::locale loc=gen("en_US.UTF-8");
    std::locale::global(loc);
    std::string genome;
    std::vector<std::thread> countingThreads;

    getConfig(config, threadNum);
    std::thread markerReader(readMarkers, std::ref(b));
    readFile(config["infile"], genome);
//    b.add_key("CATTTGTTATATTGGATACAAGC");
//    b.add_key("ATCTACATTTGGGAATGTGAGT");
    markerReader.join();
    std::vector<std::map<std::string, int>> result;
    int step = (int)genome.size() / threadNum;

    for(int i = 0; i < threadNum; i++){
        std::map<std::string, int> res;
        if(i != threadNum-1)
            countingThreads.emplace_back(calculate, std::ref(b), genome.substr(i*step, (i+1)*step + biggestMarkerSize), std::ref(res));
        else
            countingThreads.emplace_back(calculate, std::ref(b), genome.substr((threadNum - 1)*step, genome.size()), std::ref(res));

        result.emplace_back(res);
    }

    std::string().swap(genome);

    for(auto &thr : countingThreads){
        thr.join();
    }

    for(auto &ress : result){
        std::cout << ress.size();
    }

    return 0;
}
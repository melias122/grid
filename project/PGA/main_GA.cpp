#include "main.h"

#include "PGA.h"

#include <fstream>
#include <string>

bool readFile(string path, string &content)
{
    ifstream ifs(path);
    if (!ifs.is_open()) {
        println("could not open file: " + path);
        return false;
    }
    content.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    ifs.close();
    return true;
}

int main(int argc, char **argv)
{
    string dir("../project/PGA/input/");

    for (int itterations : { 10000, 50000 }) {

        // velkost populacie
        for (int popSize : { 10, 20, 50, 100 }) {

            // dlzka textu
            for (int textSize = 250; textSize <= 2000; textSize += 500) {

                // pocet textov pre dlzku
                for (int text = 1; text <= 100; text += 50) {

                    string ct, pt, ptx;

                    // nacitaj ciphertext
                    // ...
                    // a zaroven aj plaintext pre porovnanie

                    if (!readFile(dir + "ct/" + to_string(textSize) + "_" + to_string(text) + ".txt", ct)) {
                        continue;
                    }

                    if (!readFile(dir + "pt/" + to_string(textSize) + "_" + to_string(text) + ".txt", pt)) {
                        continue;
                    }

                    // vytvor schemu
                    auto scheme = Scheme{
                        itterations,
                        popSize,
                        new ShuffleGenerator(alphabet),
                        new Monoalphabetic(ct),
                        L1DistanceBigrams::fromFile(dir + "fr_2.csv")
                    };

                    for (const auto &s : schema) {

                        // pridaj operacie
                        scheme.replaceOperations(s.second(popSize));

                        // spusti geneticky algoritmus
                        auto population = GeneticAlgorithm::run(0, scheme);

                        // vyhodnot iteraciu
                        // ...
                        // vyber najlepsieho
                        Chromosome &best = population[0];

                        // desifruj ct
                        scheme.cipher->decrypt(best.genes(), ptx);

                        // match rate s pt (% kolko znakov sa zhoduje)
                        int match = 0;
                        for (int i = 0; i < ptx.size(); i++) {
                            if (ptx[i] == pt[i]) {
                                match++;
                            }
                        }

                        println(textSize << ";" << match << ";" << itterations << ";" << popSize << ";" << s.first);
                    }
                }
            }
        }
    }

    return 0;
}
// text size; match; itterations; initial population; schema ID;
// 50       ; 41   ; 10000      ; 10                ; J        ;

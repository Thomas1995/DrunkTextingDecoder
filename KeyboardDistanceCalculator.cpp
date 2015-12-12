#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const double keyboardOffset[] = {0, 0.5f, 1, 1.5f};

class KeyboardDistanceCalculator
{
    public:

        KeyboardDistanceCalculator()
        {
            GetDistanceMatrix();
            GetProbabilityMatrix();
        }

        double GetKeyboardDistance(char letter1, char letter2)
        {
            return distMatrix[letter1][letter2];
        }

        double GetProbability(char letter1, char letter2)
        {
            return probabilityMatrix[letter1][letter2];
        }

    private:

        double distMatrix[256][256];
        double probabilityMatrix[256][256];

        void GetProbabilityMatrix()
        {
            for(int i = 0; i < 256; ++i)
                if((i >= 'a' && i <= 'z') || (i >= '0' && i <= '9'))
                {
                    double probabilityTotal = 1;

                    for(int j = 0; j < 256; ++j)
                    {
                        if(distMatrix[i][j])
                            probabilityTotal += 1 / (distMatrix[i][j] + 1);
                    }

                    probabilityMatrix[i][i] = 1 / probabilityTotal;

                    for(int j = 0; j < 256; ++j)
                    {
                        if(distMatrix[i][j])
                            probabilityMatrix[i][j] = (1 / (distMatrix[i][j] + 1)) / probabilityTotal;
                    }
                }
        }

        void GetDistanceMatrix()
        {
            string keyboard[] = {"1234567890", "qwertyuiop", "asdfghjkl", "zxcvbnm"};

            double posCrtKey, posOtherKey;

            for(int i = 0; i < 4; ++i)
            {
                posCrtKey = keyboardOffset[i];
                for(auto crtKey : keyboard[i])
                {
                    for(int j = 0; j < 4; ++j)
                    {
                        posOtherKey = keyboardOffset[j];
                        for(auto otherKey : keyboard[j])
                        {
                            distMatrix[crtKey][otherKey] =
                                sqrt( ( posCrtKey - posOtherKey )* ( posCrtKey - posOtherKey )
                                     + ( i - j ) * ( i - j ) );

                            posOtherKey += 1;
                        }
                    }
                    posCrtKey += 1;
                }
            }
        }
};


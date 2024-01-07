#include <stdio.h>
#include <memory>
#include "iomanip"
#include "coordinate_system.hpp"
#include "equatorialRA.hpp"
#include "equatorialHA.hpp"

enum ECoordinateSystem{
    eEquatorialRA = 1,
    eEquatorialHA,
    eHorizontal,
    eEcliptic,
    eGalactic
};

int main()
{
    int startingSystem = 0; 
    int endSystem = 0;
    std::shared_ptr<coordinate_system> spCoordinateSystem;
    bool correctInput = true;
    
    std::setprecision(10);

    printf("\033[0;34m ---Coordinate transform reborn--- \033[0m \n");

    do 
    {
        correctInput = true;
        printf("Enter starting system: 1=Equatorial Right Ascension 2=Equatorial Hour Angle 3=Horizontal 4=Ecliptic 5=Galactic\n");
		scanf("%d", &startingSystem);
        const ECoordinateSystem eStartingSystem = static_cast<ECoordinateSystem>(startingSystem);
        switch (eStartingSystem)
        {
            case ECoordinateSystem::eEquatorialRA:
            {
                spCoordinateSystem = std::make_shared<EquatorialRA>();
                correctInput = spCoordinateSystem->Init();
                break;
            }
            case ECoordinateSystem::eEquatorialHA:
            {
                spCoordinateSystem = std::make_shared<EquatorialHA>();
                correctInput = spCoordinateSystem->Init();
                break;
            }
            default:
            {
                printf("Wrong coordinate system\n");
                correctInput = false;
                break;
            }
        }
        
        if (correctInput == false)
        {
            printf("Wrong input\n");
            continue;
        }

        printf("Enter ending system: 1=Equatorial Right Ascension 2=Equatorial Hour Angle 3=Horizontal 4=Ecliptic 5=Galactic\n");
		scanf("%d", &endSystem);
        const ECoordinateSystem eEndSystem = static_cast<ECoordinateSystem>(endSystem);
       
        switch (eEndSystem)
        {
            case ECoordinateSystem::eEquatorialRA:
                {
                    if (spCoordinateSystem->ToEquatorialRA())
                    {
                        printf("Calculation completed\n");
                    }
                    else
                    {
                        printf("Wrong system\n");
                    }
                    break;
                }
            case ECoordinateSystem::eEquatorialHA:
                {
                    if (spCoordinateSystem->ToEquatorialHA())
                    {
                        printf("Calculation completed\n");
                    }
                    else
                    {
                        printf("Wrong system\n");
                    }
                    break;
                }
            case ECoordinateSystem::eHorizontal:
                {
                    std::vector<double> inputVector;
                    if (spCoordinateSystem->ToHorizontal(inputVector))
                    {
                        printf("Calculation completed\n");
                    }
                    else
                    {
                        printf("Error\n");
                    }
                    break;
                }
            case ECoordinateSystem::eEcliptic:
                {
                    if (spCoordinateSystem->ToEcliptic())
                    {
                        printf("Calculation completed\n");
                    }
                    else
                    {
                        printf("Error\n");
                    }
                    break;
                }
            case ECoordinateSystem::eGalactic:
                {
                    if (spCoordinateSystem->ToGalactic())
                    {
                        printf("Calculation completed\n");
                    }
                    else
                    {
                        printf("Error\n");
                    }
                    break;
                }
            default:
                {
                    printf("Wrong coordinate system\n");
                    correctInput = false;
                    break;
                }
        }
        if (correctInput == false)
        {
            printf("Wrong input\n");
            continue;
        }

        printf("Continue program? (Y/n)\n");
        getchar();
    } while ( getchar() != 'n');

    return 0;
}

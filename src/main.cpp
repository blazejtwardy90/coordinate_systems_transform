#include <stdio.h>
#include <memory>
#include "coordinate_system.hpp"
#include "equatorialRA.hpp"
#include "equatorialHA.hpp"

int main()
{
    int startingSystem = 0; 
    int endSystem = 0;
    std::shared_ptr<coordinate_system> spCoordinateSystem;
    bool correctInput = true;
    
    printf("\033[0;34m ---Coordinate transform reborn--- \033[0m \n");

    do 
    {
        correctInput = true;
        printf("Enter starting system: 1=Equatorial Right Ascension 2=Equatorial Hour Angle 3=Horizontal 4=Ecliptic 5=Galaktyczny\n");
		scanf("%d", &startingSystem);
        switch (startingSystem)
        {
            case 1:
            {
                spCoordinateSystem = std::make_shared<EquatorialRA>();
                correctInput = spCoordinateSystem->Init();
                break;
            }
            case 2:
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

        printf("Enter ending system: 1=Equatorial Right Ascension 2=Equatorial Hour Angle 3=Horizontal 4=Ekliptyczny 5=Galaktyczny\n");
		scanf("%d", &endSystem);
        switch (endSystem)
        {
            case 1:
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
            case 2:
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
            case 3:
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
            case 4:
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
            case 5:
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

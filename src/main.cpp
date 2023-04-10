#include <stdio.h>
#include <memory>
#include "coordinate_system.hpp"
#include "equatorialRA.hpp"
#include "equatorialHA.hpp"

int main()
{
    int u1 = 0, u2 = 0;
    std::shared_ptr<coordinate_system> spCoordinateSystem;
    bool correctInput = true;

    do 
    {
        correctInput = true;
        printf("Podaj układ poczatkowy 1=Equatorial Right Ascension 2=Equatorial Hour Angle 3=Horyzontalny 4=Ekliptyczny 5=Galaktyczny\n");
		scanf("%d", &u1);
        switch (u1)
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

        printf("Podaj układ końcowy 1=Equatorial Right Ascension 2=Equatorial Hour Angle 3=Horyzontalny 4=Ekliptyczny 5=Galaktyczny\n");
		scanf("%d", &u2);
        switch (u2)
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
            default:
                break;
        }
        printf("Continue program? (Y/n)\n");
        getchar();
    } while ( getchar() != 'n');

    printf("Coordinate transform reborn\n");
    return 0;
}

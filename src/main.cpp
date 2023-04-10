#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include "coordinate_system.hpp"
#include "equatorialRA.hpp"
#include "equatorialHA.hpp"

int main()
{
    int u1 = 0, u2 = 0;
    std::shared_ptr<coordinate_system> spCoordinateSystem;

    while ( getchar() != 'n')
    { 
        printf("Podaj układ poczatkowy 1=Equatorial Right Ascension 2=Equatorial Hour Angle 3=Horyzontalny 4=Ekliptyczny 5=Galaktyczny\n");
		scanf("%d", &u1);

        if (u1 != 1 && u1 != 2)
        {
            printf("Wrong coordinate system\n");
        }
        else
        {
            switch (u1)
            {
                case 1:
                {
                    spCoordinateSystem = std::make_shared<EquatorialRA>();
                    break;
                }
                case 2:
                {
                    spCoordinateSystem = std::make_shared<EquatorialHA>();
                    break;
                }
                default:
                    break;
            }

            printf("Podaj układ końcowy 1=Równikowy równonocny 2=Równikowo godzinny 3=Horyzontalny 4=Ekliptyczny 5=Galaktyczny\n");
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
        }
        printf("Continue program? (Y/n)\n");
        getchar();
    }

    printf("Coordinate transform reborn\n");
    return 0;
}
